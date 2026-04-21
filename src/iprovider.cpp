#include "itemplatelib/api_exports.h"
#include <iostream>
#include <string>

// --- MathEngine Implementation ---
struct MathEngine {
    int multiplier;
};

extern "C" {
API_EXPORT EngineHandle CreateMathEngine(int multiplier) {
    return new MathEngine{multiplier};
}

API_EXPORT int MathEngine_Calculate(EngineHandle handle, int input) {
    if (!handle) return 0;
    return static_cast<MathEngine*>(handle)->multiplier * input;
}

API_EXPORT void DestroyMathEngine(EngineHandle handle) {
    delete static_cast<MathEngine*>(handle);
}

// --- CompressEngine Implementation ---
API_EXPORT bool CompressEngine_ParseConfig(int argc, char** argv, CompressEngine_Config* outConfig) {
    return true;
}

API_EXPORT EngineHandle CreateCompressEngine() {
    return (EngineHandle)1; // Dummy handle
}

API_EXPORT bool CompressEngine_CompressFileMapped(EngineHandle handle,
                                                  const wchar_t* inputFilePath,
                                                  const wchar_t* outputFilePath,
                                                  const char* archiveName) {
    return true;
}

API_EXPORT void DestroyCompressEngine(EngineHandle handle) {}

// --- SocwatchEngine Implementation ---
API_EXPORT bool SocwatchEngine_ParseConfig(int argc, char** argv, SocwatchEngine_Config* outConfig) {
    return true;
}

API_EXPORT EngineHandle CreateSocwatchEngine() {
    return (EngineHandle)1; // Dummy handle
}

API_EXPORT const char* SocwatchEngine_Run(EngineHandle handle, unsigned int durationInSeconds, const char* outputFileName) {
    return "Socwatch shell run complete.";
}

API_EXPORT void DestroySocwatchEngine(EngineHandle handle) {}

// --- PerfEngine Implementation ---
API_EXPORT bool PerfEngine_ParseConfig(int argc, char** argv, PerfEngine_Config* outConfig) {
    return true;
}

API_EXPORT EngineHandle CreatePerfEngine() {
    return (EngineHandle)1; // Dummy handle
}

API_EXPORT bool PerfEngine_StartTrace(EngineHandle handle,
                                      const wchar_t* profileName,
                                      const wchar_t* profileLevel,
                                      unsigned int duration,
                                      const wchar_t* etlFileName) {
    return true;
}

API_EXPORT bool PerfEngine_StopTrace(EngineHandle handle,
                                     const wchar_t* etlFileName) {
    return true;
}

API_EXPORT bool PerfEngine_IsRecording(EngineHandle handle) {
    return false;
}

API_EXPORT const char* PerfEngine_GetLastResult(EngineHandle handle) {
    return "PerfEngine shell result.";
}

API_EXPORT void DestroyPerfEngine(EngineHandle handle) {}
}
