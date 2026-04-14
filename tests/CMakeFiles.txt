add_executable(itemplatelib_test
    main.cpp
)

# Link the static library to the test executable
target_link_libraries(itemplatelib_test PRIVATE
    itemplatelib
)