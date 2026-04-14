#!/bin/bash
# Assuming host is Linux x64

BUILD_DIR="../build/linux_x64"

cmake -S .. -B ${BUILD_DIR} -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=clang \
    -DCMAKE_CXX_COMPILER=clang++

cmake --build ${BUILD_DIR}

# Run the test
${BUILD_DIR}/tests/itemplatelib_test
