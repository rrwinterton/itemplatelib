# itemplatelib
template libraries for telemetry data

### The structure for itemplatelib is as follows:

 itemplatelib/  
├── .clang-format
├── CMakeLists.txt  
├── GEMINI.md
├── include/  
│   └── itemplatelib/  
│       ├── api_exports.h
│       ├── icomputerinfo.h  
│       └── itemplatelib.h
├── src/  
│   ├── CMakeLists.txt  
│   ├── icomputerinfo.cpp  
│   ├── iprovider.cpp
│   └── itemplatelib.cpp
├── tests/  
│   ├── CMakeLists.txt  
│   └── main.cpp  
└── scripts/  
    ├── build_android_arm64.sh    
    ├── build_linux_x64.sh    
    └── build_windows_x64.bat    

The core functionality is provided in the `icomputerinfo` namespace.

## CLI Usage

The test harness (`itemplatelib.exe`) supports several engines. Use the activation flag for each engine to enable its specific options.

| Engine | Activation Flag | Required Parameters (if active) | Description |
| :--- | :--- | :--- | :--- |
| **Math** | `--math` | `--multiplier` | Runs the test MathEngine with a specified multiplier. |
| **Perf** | `--perf` | `--perf-start`, `--profile`, `--level`, `--duration`, `--output` | Executes performance tracing. |
| **SocWatch** | `--socwatch` | `--sw-time`, `--sw-output` | Runs SocWatch data collection for a duration. |
| **Compress** | `--compress` | `--input`, `--out`, `--name` | Compresses a file into a named archive. |

### Example
```powershell
.\build\debug\tests\itemplatelib.exe --math --multiplier 10
```

## C-API Exports (iprovider.dll)

The `iprovider.dll` exports a C-compatible API for dynamic loading.

