#include <iostream>
#include <windows.h>
#include "itemplatelib/itemplatelib.h"
#include "itemplatelib/api_exports.h"

// Define function pointers for our DLL methods
typedef EngineHandle (*CreateMathEngineFunc)(int);
typedef int (*MathEngineCalculateFunc)(EngineHandle, int);
typedef void (*DestroyMathEngineFunc)(EngineHandle);

int main() {
    std::cout << "itemplatelib Test Harness Initialized.\n";
    std::cout << "Platform/Arch: " << itemplatelib::GetPlatformInfo() << "\n";
    std::cout << "socWatch: " << itemplatelib::RunSocWatch() << "\n";
    
    // Load the DLL
    const char* dllPath = "iprovider.dll";
    HINSTANCE hLib = LoadLibraryA(dllPath);

    if (hLib == NULL) {
        std::cerr << "[Test] FAILED to load: " << dllPath << " (Error: " << GetLastError() << ")\n";
        return 1;
    }

    std::cout << "[Test] Successfully loaded " << dllPath << "\n";

    // Resolve function pointers
    CreateMathEngineFunc CreateMathEngine = (CreateMathEngineFunc)GetProcAddress(hLib, "CreateMathEngine");
    MathEngineCalculateFunc MathEngineCalculate = (MathEngineCalculateFunc)GetProcAddress(hLib, "MathEngineCalculate");
    DestroyMathEngineFunc DestroyMathEngine = (DestroyMathEngineFunc)GetProcAddress(hLib, "DestroyMathEngine");

    if (!CreateMathEngine || !MathEngineCalculate || !DestroyMathEngine) {
        std::cerr << "[Test] FAILED to resolve DLL functions.\n";
        FreeLibrary(hLib);
        return 1;
    }

    // Call the DLL functions
    std::cout << "[Test] Testing CreateMathEngine(10)\n";
    EngineHandle engine = CreateMathEngine(10);

    if (engine) {
        int input = 5;
        int result = MathEngineCalculate(engine, input);
        std::cout << "[Test] MathEngineCalculate(" << input << ") -> " << result << "\n";

        if (result != 50) {
            std::cerr << "[Test] ERROR: Expected 50, got " << result << "\n";
        } else {
            std::cout << "[Test] MathEngineCalculate verified successfully.\n";
        }


        std::cout << "[Test] Testing DestroyMathEngine\n";
        DestroyMathEngine(engine);
    } else {
        std::cerr << "[Test] CreateMathEngine returned NULL handle.\n";
    }

    // Unload the DLL
    FreeLibrary(hLib);
    std::cout << "[Test] Library freed.\n";

    return 0;
}
