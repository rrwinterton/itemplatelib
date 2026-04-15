#include "itemplatelib/itemplatelib.h"
#include <windows.h>
#include <iostream>

namespace itemplatelib
{

    std::string GetPlatformInfo()
    {
        std::string info = "Unknown Platform";

#if defined(_WIN32)
        info = "Windows";
#elif defined(__ANDROID__)
        info = "Android";
#elif defined(__linux__)
        info = "Linux";
#endif

        info += " - ";

#if defined(__x86_64__) || defined(_M_X64)
        info += "x64";
#elif defined(__aarch64__) || defined(_M_ARM64)
        info += "ARM64";
#elif defined(__arm__) || defined(_M_ARM)
        info += "ARM32";
#else
        info += "Unknown Arch";
#endif

        // Verify Clang compilation
#if defined(__clang__)
        info += " (Built with Clang " + std::to_string(__clang_major__) + "." +
                std::to_string(__clang_minor__) + ")";
#endif

        return info;
    }

    std::string RunSocWatch()
    {

        STARTUPINFOW si;
        PROCESS_INFORMATION pi;
        std::string info = "Starting socWatch: ";

        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));

        // Target executable (make sure to use wide strings or L"")
        WCHAR cmd[] = L"./socwatch.exe -m -f sys -t 15 -s 5 -o ireport1";

        // Create the process silently
        BOOL success = CreateProcessW(
            NULL,             // Application name (can pass NULL if command line is full path)
            cmd,              // Command line
            NULL,             // Process handle not inheritable
            NULL,             // Thread handle not inheritable
            FALSE,            // Set handle inheritance to FALSE
            CREATE_NO_WINDOW, // <-- THE MAGIC FLAG: Prevents console window
            NULL,             // Use parent's environment block
            NULL,             // Use parent's starting directory
            &si,              // Pointer to STARTUPINFO structure
            &pi               // Pointer to PROCESS_INFORMATION structure
        );

        if (success)
        {
            // Optional: Wait until child process exits
            // WaitForSingleObject(pi.hProcess, INFINITE);

            // Close process and thread handles to prevent memory leaks
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        }
        else
        {
            info += "CreateProcess failed (";
            info += std::to_string(GetLastError()) += ").";
        }

        return info;
    }

} // namespace itemplatelib
