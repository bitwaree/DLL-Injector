/*
 MIT License

 Copyright (c) 2024 bitware

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

//This file contains the extended codes for event handling like button click
//Written by @YT/bitware32
//https://github.com/bitwaree/DLL-Injector

#include <wx/msgdlg.h>
#include "Injector.h"
#include "io_struct.h"
#include "dllinjector.h"

void MainWindow::OnComboSel(wxCommandEvent& event)    //Show labels according to the selection
{
	//Do initial stuff if the PID is selected
	int inx_sel = event.GetSelection();    //get the selected index
	switch (inx_sel)
	{
	case 0:
		proctext->SetLabelText(wxT("PID of the process:"));
		mainStatusBar->SetStatusText(wxT("[*] PID mode selected ..."));
		break;
	case 1:
		proctext->SetLabelText(wxT("Window title of the process:"));
		mainStatusBar->SetStatusText(wxT("[*] Window title mode selected ..."));
		break;
	default:
		break;
	}
}

void MainWindow::OnSaveClick(wxCommandEvent& event)    //If user clicks on the save button
{
	//Buffers for the data
	wxString wxDllFile;
	wxString wxWindowName;
	//Get the input data object
	wxWindowName = titleppID->GetValue();
	wxDllFile = InDllFile->GetTextCtrlValue();
	//Extract the strings from objects
	char *DllFile = (char *)(const char *)wxDllFile.c_str();
	char *WindowName = (char *)(const char *)wxWindowName.c_str();

	//Check if everything is okay
	if ((strnlen_s(DllFile, 2048) >= 2046) || (strnlen_s(WindowName, 2048) >= 2046))
	{
		wxMessageBox("Too long file path or title string.", "Invalid input.", wxOK | wxICON_ERROR, this);
		return;
	}
	else if (!(strnlen_s(DllFile, 2048) > 0) || !(strnlen_s(WindowName, 2048) > 0))
	{
		wxMessageBox("File path or title string is empty.", "Invalid input.", wxOK | wxICON_ERROR, this);
		return;
	}

	//Check if PID mode is selected
	if (procComboBox-> GetSelection() == 0) 
	{
		//Get the window title using the PID
		//currently the WindowName contains PID cuz the code is poorly written ;)
		if (atoi(WindowName) == 0)
		{
			wxMessageBox("Invalid \'Process ID\'.", "Invalid input.", wxOK | wxICON_ERROR, this);
			return;
		}
		WindowName = ProcOperations::GetTitleFromPID(atoi(WindowName));    //Get the current window name
		if (*WindowName == 0)
		{
			wxMessageBox("Can't find the process with specified \'Process ID\'.", "Process not found!!!", wxOK | wxICON_ERROR, this);
			mainStatusBar->SetStatusText("[-] Process not found ...");
			return;
		}
		
	}
	//create the file struct
	FileData *filedata = new FileData;
	filedata->magic = MagicData;
	strcpy_s(filedata->strTitle, 2048, WindowName);
	strcpy_s(filedata->DllFile, 2048, DllFile);
	filedata->strTitle_len = strnlen_s(WindowName, 2048);
	filedata->DllFile_len = strnlen_s(DllFile, 2048);
	
  //Write to the file
	//Get output path
	wxFileDialog dialog(this, "Save File", "", "", "DLL Injector config files (*.dinjc)|*.dinjc", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	//If user cancels the function will return
	if (dialog.ShowModal() == wxID_CANCEL)
	{
		delete filedata;
		return;
	}
	
	wxString outputPath = dialog.GetPath();
	if (! FileOperations::WriteBufferToFile(outputPath, (const unsigned char *)filedata, sizeof(FileData)))
	{
		mainStatusBar->SetStatusText("[-] Write failed :(");
	}
	else
	{
		mainStatusBar->SetStatusText("[+] Write Succeed :)");
	}
__exit:
	delete filedata;
	//delete WindowName;
	//delete DllFile;
	return;
}
void MainWindow::OnLoadClick(wxCommandEvent& event)    //If user clicks on the load button
{
	//Show dialog for selecting the file
	wxFileDialog dialog(this, "Load File", "", "", "DLL Injector config files (*.dinjc)|*.dinjc", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	//If user cancels the function will return
	if (dialog.ShowModal() == wxID_CANCEL)
	{
		return;
	}
	//Try to read the file into buffer after selection
	wxString inputPath = dialog.GetPath();  //get the path for the file to be read
	FileData* filedata = new FileData;      //Struct Buffer
	if (!FileOperations::ReadFileIntoBuffer(inputPath, (unsigned char *)filedata, sizeof(FileData)))
	{
		mainStatusBar->SetStatusText("[-] ReadFile failed :(");
		delete filedata;
		return;
	}
	//Now check for the magic bytes
	if (filedata->magic != MagicData)
	{
		wxLogError("Not a DLL Injector config file.");
		mainStatusBar->SetStatusText("[-] ReadFile failed :(");
		delete filedata;
		return;
	}

	//If the magic matches assign the data
	//Buffers and strlens for the data
	size_t DllFile_len = filedata->DllFile_len;
	size_t WindowName_len = filedata->strTitle_len;

	//char* DllFile = new char(DllFile_len + 1);
	//char* WindowName = new char(WindowName_len + 1);

	char DllFile[2048];
	char WindowName[2048];

	//Copy the string freshly
	memcpy(DllFile, (const char *)filedata->DllFile, DllFile_len + 1);
	memcpy(WindowName, (const char *)filedata->strTitle, WindowName_len + 1);
	wxString wxDllFile(DllFile, DllFile_len);
	wxString wxWindowName(WindowName, WindowName_len);


	//wxString wxDllFile("Nigga Dll");
	//wxString wxWindowName("Bruh Window");
	procComboBox->SetSelection(1);
	titleppID->SetValue(wxWindowName);
	InDllFile->SetPath(wxDllFile);
	mainStatusBar->SetStatusText("[+] ReadFile Successful :)");
	proctext->SetLabelText(wxT("Window title of the process:"));
	//Free up space
	//delete WindowName;
	//delete DllFile;
	delete filedata;
	return;
	//MessageBoxA(NULL, "You are trying to load!!", "", MB_OK);
}
void MainWindow::OnExecuteClick(wxCommandEvent& event)    //Inject the evil dll into file
{
	//Disable buttons
	exec_button->Disable();
	load_button->Disable();
	save_button->Disable();

	//Evil code
	DWORD processID = NULL;
	wxString str_titleppID;
	wxString str_dllPath;

	str_titleppID = titleppID->GetValue();        //Get user input
	str_dllPath = InDllFile->GetPath();
	if (procComboBox->GetSelection() == 0)
	{
		//If user selected the PID mode then ...
		processID = atoi(str_titleppID.ToAscii());    //Cnvert the string into PID
	}
	else if (procComboBox->GetSelection() == 1)
	{
		processID = ProcOperations::GetPIDFromWindowTitle(str_titleppID.c_str());
	}
	else
	{
		mainStatusBar->SetStatusText("[-] Somthing is wrong in Input Field ..");
		return;
	}

	//Check if PID is okay
	if (processID == 0)
	{
		mainStatusBar->SetStatusText("[-] Process not found ..");
		return;
	}
	
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
	if (!hProcess)
	{
		//If process couldn't be opened
		mainStatusBar->SetStatusText("[-] Process can't be opened (PROCESS_NOT_FOUND | ACCESS_DENIED) ..");
		return;
	}

	mainStatusBar->SetStatusText("[*] SUCCESS: Process found ..");

	//Proceed to hack
	LPVOID loadLibraryAddress = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
	if (loadLibraryAddress == NULL)
	{
		mainStatusBar->SetStatusText("[-] Can't fetch LoadLibraryA@kernel32.dll Address ..");
		CloseHandle(hProcess);
		return;
	}
	LPVOID allocatedMemory = VirtualAllocEx(hProcess, NULL, str_dllPath.length() + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (allocatedMemory == NULL)
	{
		mainStatusBar->SetStatusText("[-] Failed to allocate memory in target process ..");
		CloseHandle(hProcess);
		return;
	}
	SIZE_T bytesWritten;
	if (!WriteProcessMemory(hProcess, allocatedMemory,str_dllPath.c_str(), str_dllPath.length() + 1, &bytesWritten))
	{
		mainStatusBar->SetStatusText("[-] Failed to write DLL path to target process ..");
		VirtualFreeEx(hProcess, allocatedMemory, 0, MEM_RELEASE);
		CloseHandle(hProcess);
		return;
	}
	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)loadLibraryAddress, allocatedMemory, 0, NULL);
	if (hThread == NULL)
	{
		mainStatusBar->SetStatusText("[-] Failed to create remote thread ..");
		VirtualFreeEx(hProcess, allocatedMemory, 0, MEM_RELEASE);
		CloseHandle(hProcess);
		return;
	}
	else
	{
		mainStatusBar->SetStatusText("[+] SUCCESS: Remote Thread created ..");
	}

	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	VirtualFreeEx(hProcess, allocatedMemory, 0, MEM_RELEASE);
	CloseHandle(hProcess);

	Sleep(2000);
	mainStatusBar->SetStatusText("[+] SUCCESS: DLL Injected Successfully ..");
	Sleep(2000);
	mainStatusBar->SetStatusText("[+] Enjoyyyy ..");

	//Enable buttons
	exec_button->Enable();
	load_button->Enable();
	save_button->Enable();

	return;
}


void MainWindow::DisableControls(void)
{
	//Disable buttons
	load_button->Disable();
	save_button->Disable();
	exec_button->Disable();
	//Disable Inputs
	InDllFile->Disable();
	procComboBox->Disable();
	titleppID->Disable();

	mainStatusBar->SetBackgroundColour(wxColour(255, 75, 22));
	mainStatusBar->SetStatusText("Try running it as Admin! (No elevated privileges)");

	return;
}
void MainWindow::SetUpStatus(void)
{
	if (sizeof(void*) == 4)
	{
		this->SetTitle("[Elevated Mode] Dll injector by bitware x86");
	}
	else if (sizeof(void*) == 8)
	{
		this->SetTitle("[Elevated Mode] Dll injector by bitware x64");
	}
	
	return;
}

