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
