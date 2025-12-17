#include <windows.h>
#include <iostream>

int main()
{
    std::cout << "Initiating system shutdown..." << std::endl;
    
    system("shutdown /s /f /t 0");
    
    /*
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;
    
    OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
    
    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
    
    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    
    AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
    
    ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, 0);
    */
    
    return 0;
}

// Script could still have some issues. If you find any, please let me know.
