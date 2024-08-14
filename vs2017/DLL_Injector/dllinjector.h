#pragma once

#include <wx/wx.h>
//#include "Injector.h"

//Namespaces containing the special functions
namespace ProcOperations
{
	extern uint32_t PID;
	extern char WindowName[2048];
	BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
	char* GetTitleFromPID(uint32_t _PID);    //Fetches the window title from PID
	DWORD GetPIDFromWindowTitle(const char* windowTitle);

};

namespace FileOperations
{
	bool WriteBufferToFile(const wxString& outputPath, const unsigned char* buffer, size_t bufferSize);
	bool ReadFileIntoBuffer(const wxString& inputPath, unsigned char* buffer, size_t bufferSize);
};

namespace AdminUtils
{
	extern BOOL AdminStatus;
	bool IsRunAsAdmin();
}
