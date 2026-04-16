add_executable(itemplatelib_exe
    main.cpp
)

set_target_properties(itemplatelib_exe PROPERTIES OUTPUT_NAME itemplatelib)

# Link the static library to the test executable
target_link_libraries(itemplatelib_exe PRIVATE
    itemplatelib
)