# Define the static library
add_library(itemplatelib STATIC
    itemplatelib.cpp
    icomputerinfo.cpp
)

# Define public include directories. 
# Anything linking to this target automatically gets this include path.
target_include_directories(itemplatelib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include/itemplatelib>
)

# Define the iprovider shared library
add_library(iprovider SHARED
    iprovider.cpp
)

# Export the functions for the shared library
target_compile_definitions(iprovider PRIVATE UNMANGLED_LIB_EXPORTS)

# Link iprovider against the same include directories as the main lib
target_include_directories(iprovider PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include/itemplatelib>
)

# Link iprovider against itemplatelib
target_link_libraries(iprovider PRIVATE itemplatelib)
