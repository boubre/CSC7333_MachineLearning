// COPYRIGHT: Open source by GPL (GNU General Public License)
// Based on C5.0 GPL Edition provided by Rulequest Research Pty Ltd.
//===================================================================
//
// Platform dependet functions implementation for windows
//
//===================================================================
//  FEB 2013  Creation:                       Ramirez, GOD RECEPRION
//===================================================================


#ifdef _WIN32

#include "C5CrossPlatform.h"

#include <windows.h>
#include <direct.h>
#include <time.h>
#include <strsafe.h>

void ErrorExit(LPTSTR lpszFunction);

double GetSystemClock()
{
  static LONGLONG frequency = 0;
  LARGE_INTEGER li;
  if (frequency == 0 && QueryPerformanceFrequency(&li))
    frequency = li.QuadPart;
  if (frequency != 0 && QueryPerformanceCounter(&li))
    return (double)(((li.QuadPart * 100000) / frequency));
  return 0;
}

void SetRunTimeStackSize(int iValue_KB)
{
  unsigned long int val = iValue_KB * 1024;
  if(SetThreadStackGuarantee(&val) == 0) {
    ErrorExit(TEXT("SetThreadStackGuarantee"));
  }
}

void C5DeleteFile(const char* iFileName)
{
  DeleteFileA(iFileName);
}

void ErrorExit(LPTSTR lpszFunction)
{ 
    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    // Display the error message and exit the process

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
        (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR)); 
    StringCchPrintf((LPTSTR)lpDisplayBuf, 
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"), 
        lpszFunction, dw, lpMsgBuf); 
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK); 

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
    ExitProcess(dw); 
}

#endif
