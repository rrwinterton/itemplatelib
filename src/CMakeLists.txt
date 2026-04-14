# Define the static library
add_library(itemplatelib STATIC
    itemplatelib.cpp
)

# Define public include directories. 
# Anything linking to this target automatically gets this include path.
target_include_directories(itemplatelib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
)

# Optional: Add specific compile definitions or flags for the library here
# target_compile_definitions(itemplatelib PRIVATE ITEMPLATELIB_INTERNAL)