#include <windows.h>
#include <iostream>
#include "itemplatelib/api_exports.h"
#include "itemplatelib/icomputerinfo.h"

// Define function pointer types based on api_exports.h
typedef EngineHandle (*CreateMathEngineFunc)(int);
typedef int (*MathEngine_CalculateFunc)(EngineHandle, int);
typedef void (*DestroyMathEngineFunc)(EngineHandle);

typedef EngineHandle (*CreateSocwatchEngineFunc)();
typedef const char* (*SocwatchEngine_RunFunc)(EngineHandle);
typedef void (*DestroySocwatchEngineFunc)(EngineHandle);

typedef EngineHandle (*CreateCompressEngineFunc)();
typedef bool (*CompressEngine_CompressFileMappedFunc)(EngineHandle,
                                                      const wchar_t*,
                                                      const wchar_t*,
                                                      const char*);
typedef void (*DestroyCompressEngineFunc)(EngineHandle);

typedef EngineHandle (*CreatePerfEngineFunc)();
typedef bool (*PerfEngine_StartTraceFunc)(EngineHandle, const wchar_t*, const wchar_t*);
typedef bool (*PerfEngine_StopTraceFunc)(EngineHandle, const wchar_t*);
typedef bool (*PerfEngine_IsRecordingFunc)(EngineHandle);
typedef void (*DestroyPerfEngineFunc)(EngineHandle);

int main() {
  std::cout
      << "itemplatelib Test Harness (Manual DLL Load Mode) Initialized.\n";
  std::cout << "Platform/Arch: " << icomputerinfo::GetPlatformInfo() << "\n";

  // Load the DLL
  const char* dllPath = "iprovider.dll";
  HINSTANCE hLib = LoadLibraryA(dllPath);

  if (hLib == NULL) {
    std::cerr << "[Test] FAILED to load: " << dllPath
              << " (Error: " << GetLastError() << ")\n";
    return 1;
  }
  std::cout << "[Test] Successfully loaded " << dllPath << "\n";

  // Resolve MathEngine functions
  auto pCreateMathEngine =
      (CreateMathEngineFunc)GetProcAddress(hLib, "CreateMathEngine");
  auto pMathEngine_Calculate =
      (MathEngine_CalculateFunc)GetProcAddress(hLib, "MathEngine_Calculate");
  auto pDestroyMathEngine =
      (DestroyMathEngineFunc)GetProcAddress(hLib, "DestroyMathEngine");

  // Resolve SocwatchEngine functions
  auto pCreateSocwatchEngine =
      (CreateSocwatchEngineFunc)GetProcAddress(hLib, "CreateSocwatchEngine");
  auto pSocwatchEngine_Run =
      (SocwatchEngine_RunFunc)GetProcAddress(hLib, "SocwatchEngine_Run");
  auto pDestroySocwatchEngine =
      (DestroySocwatchEngineFunc)GetProcAddress(hLib, "DestroySocwatchEngine");

  // Resolve CompressEngine functions
  auto pCreateCompressEngine =
      (CreateCompressEngineFunc)GetProcAddress(hLib, "CreateCompressEngine");
  auto pCompressEngine_CompressFileMapped =
      (CompressEngine_CompressFileMappedFunc)GetProcAddress(
          hLib, "CompressEngine_CompressFileMapped");
  auto pDestroyCompressEngine =
      (DestroyCompressEngineFunc)GetProcAddress(hLib, "DestroyCompressEngine");

  // Resolve PerfEngine functions
  auto pCreatePerfEngine =
      (CreatePerfEngineFunc)GetProcAddress(hLib, "CreatePerfEngine");
  auto pPerfEngine_StartTrace =
      (PerfEngine_StartTraceFunc)GetProcAddress(hLib, "PerfEngine_StartTrace");
  auto pPerfEngine_StopTrace =
      (PerfEngine_StopTraceFunc)GetProcAddress(hLib, "PerfEngine_StopTrace");
  auto pPerfEngine_IsRecording =
      (PerfEngine_IsRecordingFunc)GetProcAddress(hLib, "PerfEngine_IsRecording");
  auto pDestroyPerfEngine =
      (DestroyPerfEngineFunc)GetProcAddress(hLib, "DestroyPerfEngine");

  if (!pCreateMathEngine || !pMathEngine_Calculate || !pDestroyMathEngine ||
      !pCreateSocwatchEngine || !pSocwatchEngine_Run ||
      !pDestroySocwatchEngine || !pCreateCompressEngine ||
      !pCompressEngine_CompressFileMapped || !pDestroyCompressEngine ||
      !pCreatePerfEngine || !pPerfEngine_StartTrace || !pPerfEngine_StopTrace ||
      !pPerfEngine_IsRecording || !pDestroyPerfEngine) {
    std::cerr << "[Test] FAILED to resolve one or more DLL functions.\n";
    FreeLibrary(hLib);
    return 1;
  }

  // 1. MathEngine Test
  std::cout << "\n[Test] Testing MathEngine via manual load...\n";
  EngineHandle mathEngine = pCreateMathEngine(10);
  if (mathEngine) {
    int input = 5;
    int result = pMathEngine_Calculate(mathEngine, input);
    std::cout << "[Test] MathEngine_Calculate(" << input << ") -> " << result
              << "\n";
    pDestroyMathEngine(mathEngine);
  }

  // 2. SocwatchEngine Test
  std::cout << "\n[Test] Testing SocwatchEngine via manual load...\n";
  EngineHandle swEngine = pCreateSocwatchEngine();
  if (swEngine) {
    const char* swResult = pSocwatchEngine_Run(swEngine);
    std::cout << "[Test] SocwatchEngine_Run -> "
              << (swResult ? swResult : "NULL") << "\n";
    pDestroySocwatchEngine(swEngine);
  }

  // 3. PerfEngine Test
  std::cout << "\n[Test] Testing PerfEngine via manual load...\n";
  EngineHandle perfEngine = pCreatePerfEngine();
  if (perfEngine) {
    const wchar_t* profile = L"CPU";
    const wchar_t* level = L"Verbose";
    const wchar_t* etlFile = L"cpu_profile.etl";

    if (pPerfEngine_StartTrace(perfEngine, profile, level)) {
      std::cout << "[Test] PerfEngine_StartTrace SUCCESSFUL.\n";
      if (pPerfEngine_IsRecording(perfEngine)) {
        std::cout << "[Test] PerfEngine_IsRecording: TRUE\n";
      }
      if (pPerfEngine_StopTrace(perfEngine, etlFile)) {
        std::cout << "[Test] PerfEngine_StopTrace SUCCESSFUL.\n";
      }
    } else {
      std::cerr << "[Test] PerfEngine_StartTrace FAILED.\n";
    }
    pDestroyPerfEngine(perfEngine);
  }
  // 4. CompressEngine Test
  std::cout << "\n[Test] Testing CompressEngine via manual load...\n";
  EngineHandle compressEngine = pCreateCompressEngine();
  if (compressEngine) {
    std::cout << "[Test] CompressEngine handle created successfully.\n";

    
    //rrw this is hardcoded to compres socwatch test about. both need to change to parameters
    const wchar_t* inputCsv = L"ireport1.csv";
    const wchar_t* outputZip = L"ireport1.zip";
    const char* myArchiveName = "ireport1.csv";

    std::cout << "[Test] Compressing " << "ireport1.csv" << " to "
              << "ireport1.zip" << "...\n";
    bool success = pCompressEngine_CompressFileMapped(compressEngine, inputCsv,
                                                      outputZip, myArchiveName);

    if (success) {
      std::cout << "[Test] Compression SUCCESSFUL!\n";
    } else {
      std::cerr << "[Test] Compression FAILED.\n";
    }

    pDestroyCompressEngine(compressEngine);
  }

  // Unload the DLL
  FreeLibrary(hLib);
  std::cout << "\n[Test] Library freed. All tests completed.\n";

  return 0;
}
