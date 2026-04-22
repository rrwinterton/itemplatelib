#pragma once
#include "CLI.hpp"
#include "itemplatelib/api_exports.h"
#include <string>
#include <vector>

/**
 * @brief Helper function to setup the CLI for the test harness.
 */
inline void SetupCLI(CLI::App& app,
                    bool& runMath, int& mathMultiplier,
                    bool& runSocwatch, SocwatchEngine_Config& swConfig,
                    bool& runPerf, PerfEngine_Config& perfConfig,
                    bool& runCompress, std::vector<std::wstring>& compInputs, std::string& compOutput, std::vector<std::string>& compNames) {
    
    // 1. MathEngine Parameters
    auto mathGroup = app.add_flag("--math", runMath, "Execute MathEngine");
    app.add_option("--multiplier", mathMultiplier, "Math multiplier (integer)")->needs(mathGroup);

    // 2. SocwatchEngine Parameters
    auto swGroup = app.add_flag("--socwatch", runSocwatch, "Execute SocwatchEngine");
    static std::string swTimeStr, swOutputFileStr;
    app.add_option("--sw-time", swTimeStr, "Collection time (seconds)")->needs(swGroup);
    app.add_option("--sw-output", swOutputFileStr, "Output file path")->needs(swGroup);
    
    // 3. PerfEngine Parameters
    auto perfGroup = app.add_flag("--perf", runPerf, "Execute PerfEngine");
    app.add_flag("--perf-start", perfConfig.isStartTrace, "Start the trace")->needs(perfGroup);
    
    static std::string perfProfileStr, perfLevelStr, perfOutputStr;
    app.add_option("--profile", perfProfileStr, "Trace profile (e.g., CPU)")->needs(perfGroup);
    app.add_option("--level", perfLevelStr, "Detail level (e.g., light)")->needs(perfGroup);
    app.add_option("--duration", perfConfig.duration, "Duration in seconds")->needs(perfGroup);
    app.add_option("--output", perfOutputStr, "Output ETL filename")->needs(perfGroup);

    // 4. CompressEngine Parameters
    auto compGroup = app.add_option("--compress", compInputs, "Execute CompressEngine and optionally specify input files")
        ->expected(0, -1)
        ->delimiter(',')
        ->each([&runCompress](const std::string&) { runCompress = true; });
    
    app.add_option("--input", compInputs, "Input files to compress (wide)")->needs(compGroup)->delimiter(',');
    app.add_option("--out", compOutput, "Output compressed file path (wide)")->needs(compGroup);
    app.add_option("--name", compNames, "Archive names inside the file")->needs(compGroup)->delimiter(',');

    // Post-parse callback to copy strings into C structs if needed
    app.callback([&]() {
        if (app.count("--compress") > 0 || !compInputs.empty()) {
            runCompress = true;
        }
        if (runSocwatch) {
            swConfig.duration = swTimeStr.empty() ? 0 : std::stoul(swTimeStr);
            strncpy_s(swConfig.outputFileName, sizeof(swConfig.outputFileName), swOutputFileStr.c_str(), _TRUNCATE);
        }
        if (runPerf) {
            strncpy_s(perfConfig.profileName, sizeof(perfConfig.profileName), perfProfileStr.c_str(), _TRUNCATE);
            strncpy_s(perfConfig.profileLevel, sizeof(perfConfig.profileLevel), perfLevelStr.c_str(), _TRUNCATE);
            strncpy_s(perfConfig.etlFileName, sizeof(perfConfig.etlFileName), perfOutputStr.c_str(), _TRUNCATE);
        }
    });
}
