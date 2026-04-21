#include <windows.h>
#include <iostream>
#include <cstring>
#include <string>
#include "itemplatelib/api_exports.h"
#include "itemplatelib/icomputerinfo.h"
#include "CLI/cli_helper.hpp"

// --- Function Pointer Typedefs ---
typedef EngineHandle (*CreateMathEngine_t)(int);
typedef int (*MathEngine_Calculate_t)(EngineHandle, int);
typedef void (*DestroyMathEngine_t)(EngineHandle);

typedef bool (*CompressEngine_ParseConfig_t)(int, char**, CompressEngine_Config*);
typedef EngineHandle (*CreateCompressEngine_t)();
typedef bool (*CompressEngine_CompressFileMapped_t)(EngineHandle, const wchar_t*, const wchar_t*, const char*);
typedef void (*DestroyCompressEngine_t)(EngineHandle);

typedef bool (*SocwatchEngine_ParseConfig_t)(int, char**, SocwatchEngine_Config*);
typedef EngineHandle (*CreateSocwatchEngine_t)();
typedef const char* (*SocwatchEngine_Run_t)(EngineHandle, unsigned int, const char*);
typedef void (*DestroySocwatchEngine_t)(EngineHandle);

typedef bool (*PerfEngine_ParseConfig_t)(int, char**, PerfEngine_Config*);
typedef EngineHandle (*CreatePerfEngine_t)();
typedef bool (*PerfEngine_StartTrace_t)(EngineHandle, const wchar_t*, const wchar_t*, unsigned int, const wchar_t*);
typedef bool (*PerfEngine_StopTrace_t)(EngineHandle, const wchar_t*);
typedef bool (*PerfEngine_IsRecording_t)(EngineHandle);
typedef const char* (*PerfEngine_GetLastResult_t)(EngineHandle);
typedef void (*DestroyPerfEngine_t)(EngineHandle);

// --- Global Function Pointers ---
CreateMathEngine_t pCreateMathEngine = nullptr;
MathEngine_Calculate_t pMathEngine_Calculate = nullptr;
DestroyMathEngine_t pDestroyMathEngine = nullptr;

CompressEngine_ParseConfig_t pCompressEngine_ParseConfig = nullptr;
CreateCompressEngine_t pCreateCompressEngine = nullptr;
CompressEngine_CompressFileMapped_t pCompressEngine_CompressFileMapped = nullptr;
DestroyCompressEngine_t pDestroyCompressEngine = nullptr;

SocwatchEngine_ParseConfig_t pSocwatchEngine_ParseConfig = nullptr;
CreateSocwatchEngine_t pCreateSocwatchEngine = nullptr;
SocwatchEngine_Run_t pSocwatchEngine_Run = nullptr;
DestroySocwatchEngine_t pDestroySocwatchEngine = nullptr;

PerfEngine_ParseConfig_t pPerfEngine_ParseConfig = nullptr;
CreatePerfEngine_t pCreatePerfEngine = nullptr;
PerfEngine_StartTrace_t pPerfEngine_StartTrace = nullptr;
PerfEngine_StopTrace_t pPerfEngine_StopTrace = nullptr;
PerfEngine_IsRecording_t pPerfEngine_IsRecording = nullptr;
PerfEngine_GetLastResult_t pPerfEngine_GetLastResult = nullptr;
DestroyPerfEngine_t pDestroyPerfEngine = nullptr;

/**
 * @brief itemplatelib Test Harness (Dynamic Mode)
 */
int main(int argc, char* argv[]) {
  // 0. Load the DLL
  HMODULE hProvider = LoadLibraryA("iprovider.dll");
  if (!hProvider) {
    std::cerr << "Failed to load iprovider.dll (Error: " << GetLastError() << ")\n";
    return 1;
  }

  // 1. Resolve Function Pointers
  pCreateMathEngine = (CreateMathEngine_t)GetProcAddress(hProvider, "CreateMathEngine");
  pMathEngine_Calculate = (MathEngine_Calculate_t)GetProcAddress(hProvider, "MathEngine_Calculate");
  pDestroyMathEngine = (DestroyMathEngine_t)GetProcAddress(hProvider, "DestroyMathEngine");

  pCompressEngine_ParseConfig = (CompressEngine_ParseConfig_t)GetProcAddress(hProvider, "CompressEngine_ParseConfig");
  pCreateCompressEngine = (CreateCompressEngine_t)GetProcAddress(hProvider, "CreateCompressEngine");
  pCompressEngine_CompressFileMapped = (CompressEngine_CompressFileMapped_t)GetProcAddress(hProvider, "CompressEngine_CompressFileMapped");
  pDestroyCompressEngine = (DestroyCompressEngine_t)GetProcAddress(hProvider, "DestroyCompressEngine");

  pSocwatchEngine_ParseConfig = (SocwatchEngine_ParseConfig_t)GetProcAddress(hProvider, "SocwatchEngine_ParseConfig");
  pCreateSocwatchEngine = (CreateSocwatchEngine_t)GetProcAddress(hProvider, "CreateSocwatchEngine");
  pSocwatchEngine_Run = (SocwatchEngine_Run_t)GetProcAddress(hProvider, "SocwatchEngine_Run");
  pDestroySocwatchEngine = (DestroySocwatchEngine_t)GetProcAddress(hProvider, "DestroySocwatchEngine");

  pPerfEngine_ParseConfig = (PerfEngine_ParseConfig_t)GetProcAddress(hProvider, "PerfEngine_ParseConfig");
  pCreatePerfEngine = (CreatePerfEngine_t)GetProcAddress(hProvider, "CreatePerfEngine");
  pPerfEngine_StartTrace = (PerfEngine_StartTrace_t)GetProcAddress(hProvider, "PerfEngine_StartTrace");
  pPerfEngine_StopTrace = (PerfEngine_StopTrace_t)GetProcAddress(hProvider, "PerfEngine_StopTrace");
  pPerfEngine_IsRecording = (PerfEngine_IsRecording_t)GetProcAddress(hProvider, "PerfEngine_IsRecording");
  pPerfEngine_GetLastResult = (PerfEngine_GetLastResult_t)GetProcAddress(hProvider, "PerfEngine_GetLastResult");
  pDestroyPerfEngine = (DestroyPerfEngine_t)GetProcAddress(hProvider, "DestroyPerfEngine");

  // Verify pointers
  if (!pCreateMathEngine || !pMathEngine_Calculate || !pDestroyMathEngine ||
      !pCompressEngine_ParseConfig || !pCreateCompressEngine || !pCompressEngine_CompressFileMapped || !pDestroyCompressEngine ||
      !pSocwatchEngine_ParseConfig || !pCreateSocwatchEngine || !pSocwatchEngine_Run || !pDestroySocwatchEngine ||
      !pPerfEngine_ParseConfig || !pCreatePerfEngine || !pPerfEngine_StartTrace || !pPerfEngine_StopTrace || !pPerfEngine_IsRecording || !pPerfEngine_GetLastResult || !pDestroyPerfEngine) {
    std::cerr << "Failed to resolve one or more required functions from iprovider.dll\n";
    FreeLibrary(hProvider);
    return 1;
  }

  CLI::App app{"itemplatelib Test Harness (Dynamic Mode)"};

  bool runMath = false;
  int mathMultiplier = 1;
  bool runSocwatch = false;
  SocwatchEngine_Config swConfig{};
  bool runPerf = false;
  PerfEngine_Config perfConfig{};
  bool runCompress = false;
  std::wstring compInput, compOutput;
  std::string compName;

  // Setup CLI using the helper in cli_helper.hpp
  SetupCLI(app, runMath, mathMultiplier, runSocwatch, swConfig, runPerf, perfConfig, runCompress, compInput, compOutput, compName);

  CLI11_PARSE(app, argc, argv);

  std::cout << "itemplatelib Test Harness (Dynamic Mode) Initialized.\n";
  std::cout << "Platform/Arch: " << icomputerinfo::GetPlatformInfo() << "\n";

  // 1. MathEngine
  if (runMath) {
    std::cout << "\n[Test] Running MathEngine (Multiplier: " << mathMultiplier << ")...\n";
    EngineHandle handle = pCreateMathEngine(mathMultiplier);
    if (handle) {
      int input = 5;
      int result = pMathEngine_Calculate(handle, input);
      std::cout << "[Test] MathEngine_Calculate(" << input << ") -> " << result << "\n";
      pDestroyMathEngine(handle);
    }
  }

  // 2. SocwatchEngine
  if (runSocwatch) {
    std::cout << "\n[Test] Running SocwatchEngine...\n";
    EngineHandle handle = pCreateSocwatchEngine();
    if (handle) {
      const char* swResult = pSocwatchEngine_Run(handle, swConfig.duration, swConfig.outputFileName);
      std::cout << "[Test] SocwatchEngine_Run -> " << (swResult ? swResult : "NULL") << "\n";
      pDestroySocwatchEngine(handle);
    }
  }

  // 3. PerfEngine
  if (runPerf) {
    std::cout << "\n[Test] Running PerfEngine...\n";
    EngineHandle handle = pCreatePerfEngine();
    if (handle) {
      wchar_t wProfile[256], wLevel[256], wEtlFile[260];
      MultiByteToWideChar(CP_ACP, 0, perfConfig.profileName, -1, wProfile, 256);
      MultiByteToWideChar(CP_ACP, 0, perfConfig.profileLevel, -1, wLevel, 256);
      MultiByteToWideChar(CP_ACP, 0, perfConfig.etlFileName, -1, wEtlFile, 260);

      if (perfConfig.isStartTrace) {
        if (pPerfEngine_StartTrace(handle, wProfile, wLevel, perfConfig.duration, wEtlFile)) {
          std::cout << "[Test] PerfEngine_StartTrace SUCCESSFUL. Waiting for " << perfConfig.duration << " seconds...\n";
          Sleep(perfConfig.duration * 1000);
          pPerfEngine_StopTrace(handle, wEtlFile);
        } else {
          std::cerr << "[Test] PerfEngine_StartTrace FAILED: " << (pPerfEngine_GetLastResult ? pPerfEngine_GetLastResult(handle) : "Unknown") << "\n";
        }
      }

      if (pPerfEngine_IsRecording(handle)) {
        std::cout << "[Test] PerfEngine_IsRecording: TRUE\n";
      }

      pDestroyPerfEngine(handle);
    }
  }

  // 4. CompressEngine
  if (runCompress) {
    std::cout << "\n[Test] Running CompressEngine...\n";
    EngineHandle handle = pCreateCompressEngine();
    if (handle) {
      if (pCompressEngine_CompressFileMapped(handle, compInput.c_str(), compOutput.c_str(), compName.c_str())) {
        std::cout << "[Test] CompressEngine_CompressFileMapped SUCCESSFUL!\n";
      } else {
        std::cerr << "[Test] CompressEngine_CompressFileMapped FAILED.\n";
      }
      pDestroyCompressEngine(handle);
    }
  }

  std::cout << "\n[Test] CLI tests completed.\n";

  FreeLibrary(hProvider);
  return 0;
}
