#include "itemplatelib/api_exports.h"
#include "itemplatelib/itemplatelib.h"
#include <iostream>
#include <string>

// --- MathEngine Implementation ---
class MathEngine {
public:
    MathEngine(int multiplier) : m_multiplier(multiplier) {}
    int Calculate(int input) {
        return input * m_multiplier;
    }
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

// --- CompressEngine Implementation ---
class CompressEngine {
public:
    CompressEngine() {}
    bool Compress(const wchar_t* input, const wchar_t* output) {
        // Placeholder for compression logic
        std::wcout << L"[iprovider] Compressing " << input << L" to " << output << std::endl;
        return true;
    }
};

extern "C" {
    // MathEngine
    API_EXPORT EngineHandle CreateMathEngine(int multiplier) {
        return static_cast<EngineHandle>(new MathEngine(multiplier));
    }

    API_EXPORT int MathEngine_Calculate(EngineHandle handle, int input) {
        if (!handle) return 0;
        return static_cast<MathEngine*>(handle)->Calculate(input);
    }

    API_EXPORT void DestroyMathEngine(EngineHandle handle) {
        delete static_cast<MathEngine*>(handle);
    }

    // CompressEngine
    API_EXPORT EngineHandle CreateCompressEngine() {
        return static_cast<EngineHandle>(new CompressEngine());
    }

    API_EXPORT bool CompressEngine_CompressFileMapped(EngineHandle handle, const wchar_t* inputFilePath, const wchar_t* outputFilePath) {
        if (!handle) return false;
        return static_cast<CompressEngine*>(handle)->Compress(inputFilePath, outputFilePath);
    }

    API_EXPORT void DestroyCompressEngine(EngineHandle handle) {
        delete static_cast<CompressEngine*>(handle);
    }

    // SocwatchEngine
    API_EXPORT EngineHandle CreateSocwatchEngine() {
        return static_cast<EngineHandle>(new SocwatchEngine());
    }

    API_EXPORT const char* SocwatchEngine_Run(EngineHandle handle) {
        if (!handle) return nullptr;
        return static_cast<SocwatchEngine*>(handle)->Run();
    }

    API_EXPORT void DestroySocwatchEngine(EngineHandle handle) {
        delete static_cast<SocwatchEngine*>(handle);
    }
}
