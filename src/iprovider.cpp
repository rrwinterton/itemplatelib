#include "itemplatelib/api_exports.h"
#include <iostream>

class MathEngine {
public:
    MathEngine(int multiplier) : m_multiplier(multiplier) {}
    int Calculate(int input) {
        return input * m_multiplier;
    }
private:
    int m_multiplier;
};

extern "C" {
    API_EXPORT EngineHandle CreateMathEngine(int multiplier) {
        std::cout << "[iprovider] Creating MathEngine with multiplier: " << multiplier << std::endl;
        return static_cast<EngineHandle>(new MathEngine(multiplier));
    }

    API_EXPORT int MathEngineCalculate(EngineHandle handle, int input) {
        if (!handle) return 0;
        MathEngine* engine = static_cast<MathEngine*>(handle);
        int result = engine->Calculate(input);
        std::cout << "[iprovider] Calculating: " << input << " -> " << result << std::endl;
        return result;
    }

    API_EXPORT void DestroyMathEngine(EngineHandle handle) {
        if (handle) {
            std::cout << "[iprovider] Destroying MathEngine" << std::endl;
            delete static_cast<MathEngine*>(handle);
        }
    }
}
