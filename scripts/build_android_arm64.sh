#!/bin/bash
# Assuming host is Linux or Windows (WSL)

if [ -z "$ANDROID_NDK_HOME" ]; then
    echo "Error: ANDROID_NDK_HOME environment variable is not set."
    exit 1
fi

BUILD_DIR="../build/android_arm64"

cmake -S .. -B ${BUILD_DIR} -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_TOOLCHAIN_FILE=${ANDROID_NDK_HOME}/build/cmake/android.toolchain.cmake \
    -DANDROID_ABI=arm64-v8a \
    -DANDROID_PLATFORM=android-28

# The NDK toolchain automatically overrides the compiler paths to the NDK's internal Clang

cmake --build ${BUILD_DIR}

echo "Build complete. Push ${BUILD_DIR}/tests/itemplatelib_test to Android device via adb to execute."
