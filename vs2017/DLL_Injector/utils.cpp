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

#include "Injector.h"
#include "dllinjector.h"


//Special operators
namespace ProcOperations
{
	uint32_t PID;
	char WindowName[2048];
	//BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
	//char* GetTitleFromPID(uint32_t _PID);    //Fetches the window title from PID
};

//FileOPeration APIs
bool FileOperations::WriteBufferToFile(const wxString& outputPath, const unsigned char* buffer, size_t bufferSize)
{
	wxFile file(outputPath, wxFile::write);
	if (!file.IsOpened())
	{
		wxLogError("Failed to open file for writing.");
		return false;
	}

	if (file.Write(buffer, bufferSize) != bufferSize)
	{
		wxMessageBox("Failed to write into file.", "Error", wxOK | wxICON_ERROR);
		return false;
	}

	return true;
}
bool FileOperations::ReadFileIntoBuffer(const wxString& inputPath, unsigned char* buffer, size_t bufferSize)
{
	wxFile file(inputPath, wxFile::read);
	if (!file.IsOpened())
	{
		wxLogError("Failed to open file for reading.");
		return false;
	}

	wxFileOffset fileSize = file.Length();
	if (fileSize != static_cast<wxFileOffset>(bufferSize))
	{
		wxLogError("File is't of the correct size.");
		return false;
	}

	if (file.Read(buffer, fileSize) != fileSize)
	{
		wxLogError("Failed to read config data from file.");
		return false;
	}

	return true;
}

//PRocess Operation APIs
BOOL CALLBACK ProcOperations::EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	DWORD processId;
	GetWindowThreadProcessId(hwnd, &processId);
	if (processId == static_cast<DWORD>(lParam))
	{
		const int bufferSize = 2048;
		//LPSTR buffer;
		if (GetWindowTextA(hwnd, WindowName, bufferSize) > 0)
		{
			//SUCCESS: add code that needs to be executed at successful  fetch
			//Copy the buffer into the variable
			//strcpy_s(WindowName, sizeof(buffer), buffer);

		}
		return FALSE; // Stop enumeration
	}
	return TRUE; // Continue enumeration
}
char* ProcOperations::GetTitleFromPID(uint32_t _PID)    //Fetches the window title from PID
{
	if (_PID != 0)
	{
		PID = _PID;
	}
	WindowName[0] = (char)0;    //Set the value to zerobyte at the first offset initially
	EnumWindows(EnumWindowsProc, PID);
	return WindowName;
}
DWORD ProcOperations::GetPIDFromWindowTitle(const char* windowTitle)
{
	//strcpy_s(WindowName, 5, windowTitle);
	//Get window handle and then fetch the ProcessID
	HWND hwnd = FindWindowA(NULL, windowTitle);
	if (hwnd == NULL)
	{
		//Window not found
		return 0;
	}

	//DWORD processId;
	GetWindowThreadProcessId(hwnd, (LPDWORD)&PID);
	return PID;
}

//Check for admin privileges
namespace AdminUtils
{
	BOOL AdminStatus;
	//bool IsRunAsAdmin();
}

bool AdminUtils::IsRunAsAdmin()
{
	AdminStatus = false;
	HANDLE hToken = NULL;
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
	{
		TOKEN_ELEVATION elevation;
		DWORD size;
		if (GetTokenInformation(hToken, TokenElevation, &elevation, sizeof(elevation), &size))
		{
			AdminStatus = elevation.TokenIsElevated != 0;
		}
		CloseHandle(hToken);
	}
	return AdminStatus;
}
