add_executable(itemplatelib_exe
    main.cpp
)

set_target_properties(itemplatelib_exe PROPERTIES OUTPUT_NAME itemplatelib)

target_include_directories(itemplatelib_exe PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

# Link only the static library. iprovider will be loaded dynamically.
target_link_libraries(itemplatelib_exe PRIVATE
    itemplatelib
)

# Ensure iprovider is built before itemplatelib_exe
add_dependencies(itemplatelib_exe iprovider)

# Post-build step to copy iprovider.dll to the same directory as itemplatelib_exe
add_custom_command(TARGET itemplatelib_exe POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:iprovider>
    $<TARGET_FILE_DIR:itemplatelib_exe>
)