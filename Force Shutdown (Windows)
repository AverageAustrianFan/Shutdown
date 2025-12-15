using System;
using System.Diagnostics;
using System.Runtime.InteropServices;

class ShutdownScript
{
    // Import the Windows API function
    [DllImport("advapi32.dll", SetLastError = true)]
    private static extern bool ExitWindowsEx(uint uFlags, uint dwReason);

    [DllImport("kernel32.dll", SetLastError = true)]
    private static extern IntPtr GetCurrentProcess();

    [DllImport("advapi32.dll", SetLastError = true)]
    private static extern bool OpenProcessToken(IntPtr ProcessHandle, uint DesiredAccess, out IntPtr TokenHandle);

    [DllImport("advapi32.dll", SetLastError = true)]
    private static extern bool LookupPrivilegeValue(string lpSystemName, string lpName, out long lpLuid);

    [DllImport("advapi32.dll", SetLastError = true)]
    private static extern bool AdjustTokenPrivileges(IntPtr TokenHandle, bool DisableAllPrivileges, ref TOKEN_PRIVILEGES NewState, uint BufferLength, IntPtr PreviousState, IntPtr ReturnLength);

    [StructLayout(LayoutKind.Sequential)]
    private struct TOKEN_PRIVILEGES
    {
        public uint PrivilegeCount;
        public long Luid;
        public uint Attributes;
    }

    private const uint SE_PRIVILEGE_ENABLED = 0x00000002;
    private const uint TOKEN_ADJUST_PRIVILEGES = 0x00000020;
    private const uint TOKEN_QUERY = 0x00000008;
    private const uint EWX_SHUTDOWN = 0x00000001;
    private const uint EWX_FORCE = 0x00000004;

    static void Main(string[] args)
    {
        Console.WriteLine("Initiating system shutdown...");
        
        // Method 1: Using shutdown command (simpler, works without special privileges)
        ShutdownUsingCommand();

        // Uncomment Method 2 if you want to use Windows API (requires admin)
        // ShutdownUsingAPI();
    }

    // Simpler method using shutdown.exe command
    static void ShutdownUsingCommand()
    {
        try
        {
            // /s = shutdown, /f = force close applications, /t 0 = immediate
            Process.Start(new ProcessStartInfo
            {
                FileName = "shutdown",
                Arguments = "/s /f /t 0",
                CreateNoWindow = true,
                UseShellExecute = false
            });
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error: {ex.Message}");
        }
    }

    // Advanced method using Windows API
    static void ShutdownUsingAPI()
    {
        try
        {
            // Enable shutdown privilege
            IntPtr tokenHandle;
            OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, out tokenHandle);

            TOKEN_PRIVILEGES tkp;
            tkp.PrivilegeCount = 1;
            LookupPrivilegeValue(null, "SeShutdownPrivilege", out tkp.Luid);
            tkp.Attributes = SE_PRIVILEGE_ENABLED;

            AdjustTokenPrivileges(tokenHandle, false, ref tkp, 0, IntPtr.Zero, IntPtr.Zero);

            // Shutdown
            ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, 0);
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error: {ex.Message}");
        }
    }
}
