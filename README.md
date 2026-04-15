# itemplatelib
template libraries for telemetry data

### The structure for itemplatelib is as follows:

 itemplatelib/  
├── .gitignore  
├── CMakeLists.txt  
├── include/  
│   └── itemplatelib/  
│       └── icomputerinfo.h  
├── src/  
│   ├── CMakeLists.txt  
│   └── icomputerinfo.cpp  
├── tests/  
│   ├── CMakeLists.txt  
│   └── main.cpp  
└── scripts/  
│   ├── build_linux_x64.sh    
│   ├── build_windows_x64.bat    
│   └── build_android_arm64.sh    

The core functionality is provided in the `icomputerinfo` namespace.
