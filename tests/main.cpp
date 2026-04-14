#include <iostream>
#include "itemplatelib/itemplatelib.h"

int main() {
    std::cout << "itemplatelib Test Harness Initialized.\n";
    std::cout << "Platform/Arch: " << itemplatelib::GetPlatformInfo() << "\n";
    
    // Add further initialization and testing logic here
    
    return 0;
}
