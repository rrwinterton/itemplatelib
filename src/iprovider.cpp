#include <iostream>
#include <string>
#include "itemplatelib/api_exports.h"
#include "itemplatelib/itemplatelib.h"

// --- MathEngine Implementation ---
class MathEngine {
 public:
  MathEngine(int multiplier) : m_multiplier(multiplier) {}
  int Calculate(int input) { return input * m_multiplier; }

 private:
  int m_multiplier;
};

// --- SocwatchEngine Implementation ---
class SocwatchEngine {
 public:
  SocwatchEngine() {}
  const char* Run() {
    m_lastResult = itemplatelib::RunSocWatch();
    return m_lastResult.c_str();
  }

 private:
  std::string m_lastResult;
};

// --- PerfEngine Implementation ---
class PerfEngine {
 public:
  PerfEngine() : m_isRecording(false) {}

  bool StartTrace(const wchar_t* profileName, const wchar_t* profileLevel) {
    if (m_isRecording)
      return false;

    std::wcout << L"[iprovider] Starting Perf Trace - Profile: " << profileName
               << L", Level: " << profileLevel << std::endl;
    m_isRecording = true;
    return true;
  }

  bool StopTrace(const wchar_t* etlFileName) {
    if (!m_isRecording)
      return false;

    std::wcout << L"[iprovider] Stopping Perf Trace - Saving to: "
               << etlFileName << std::endl;
    m_isRecording = false;
    return true;
  }

  bool IsRecording() const { return m_isRecording; }

 private:
  bool m_isRecording;
};

// --- CompressEngine Implementation ---
class CompressEngine {
 public:
  CompressEngine() {}
  bool Compress(const wchar_t* input,
                const wchar_t* output,
                const char* archiveName) {
    // Placeholder for compression logic
    std::wcout << L"[iprovider] Compressing " << input << L" to " << output;
    if (archiveName) {
      std::cout << " (Archive: " << archiveName << ")";
    }
    std::wcout << std::endl;
    return true;
  }
};

extern "C" {
// MathEngine
API_EXPORT EngineHandle CreateMathEngine(int multiplier) {
  return static_cast<EngineHandle>(new MathEngine(multiplier));
}

API_EXPORT int MathEngine_Calculate(EngineHandle handle, int input) {
  if (!handle)
    return 0;
  return static_cast<MathEngine*>(handle)->Calculate(input);
}

API_EXPORT void DestroyMathEngine(EngineHandle handle) {
  delete static_cast<MathEngine*>(handle);
}

// CompressEngine
API_EXPORT EngineHandle CreateCompressEngine() {
  return static_cast<EngineHandle>(new CompressEngine());
}

API_EXPORT bool CompressEngine_CompressFileMapped(EngineHandle handle,
                                                  const wchar_t* inputFilePath,
                                                  const wchar_t* outputFilePath,
                                                  const char* archiveName) {
  if (!handle)
    return false;
  return static_cast<CompressEngine*>(handle)->Compress(
      inputFilePath, outputFilePath, archiveName);
}

API_EXPORT void DestroyCompressEngine(EngineHandle handle) {
  delete static_cast<CompressEngine*>(handle);
}

// SocwatchEngine
API_EXPORT EngineHandle CreateSocwatchEngine() {
  return static_cast<EngineHandle>(new SocwatchEngine());
}

API_EXPORT const char* SocwatchEngine_Run(EngineHandle handle) {
  if (!handle)
    return nullptr;
  return static_cast<SocwatchEngine*>(handle)->Run();
}

API_EXPORT void DestroySocwatchEngine(EngineHandle handle) {
  delete static_cast<SocwatchEngine*>(handle);
}

// PerfEngine
API_EXPORT EngineHandle CreatePerfEngine() {
  return static_cast<EngineHandle>(new PerfEngine());
}

API_EXPORT bool PerfEngine_StartTrace(EngineHandle handle,
                                      const wchar_t* profileName,
                                      const wchar_t* profileLevel) {
  if (!handle)
    return false;
  return static_cast<PerfEngine*>(handle)->StartTrace(profileName,
                                                      profileLevel);
}

API_EXPORT bool PerfEngine_StopTrace(EngineHandle handle,
                                     const wchar_t* etlFileName) {
  if (!handle)
    return false;
  return static_cast<PerfEngine*>(handle)->StopTrace(etlFileName);
}

API_EXPORT bool PerfEngine_IsRecording(EngineHandle handle) {
  if (!handle)
    return false;
  return static_cast<PerfEngine*>(handle)->IsRecording();
}

API_EXPORT void DestroyPerfEngine(EngineHandle handle) {
  delete static_cast<PerfEngine*>(handle);
}
}
