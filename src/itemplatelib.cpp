#include "itemplatelib/itemplatelib.h"
#include <windows.h>
#include <iostream>

namespace itemplatelib {

std::string GetPlatformInfo() {
  std::string info = "Unknown Platform";

#if defined(_WIN32)
  info = "Windows";
#elif defined(__ANDROID__)
  info = "Android";
#elif defined(__linux__)
  info = "Linux";
#endif

  info += " - ";

#if defined(__x86_64__) || defined(_M_X64)
  info += "x64";
#elif defined(__aarch64__) || defined(_M_ARM64)
  info += "ARM64";
#elif defined(__arm__) || defined(_M_ARM)
  info += "ARM32";
#else
  info += "Unknown Arch";
#endif

  // Verify Clang compilation
#if defined(__clang__)
  info += " (Built with Clang " + std::to_string(__clang_major__) + "." +
          std::to_string(__clang_minor__) + ")";
#endif

  return info;
}

}  // namespace itemplatelib
