add_executable(itemplate
    main.cpp
)

# Link the static library to the test executable
target_link_libraries(itemplate PRIVATE
    itemplatelib
)