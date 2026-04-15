# Gemini CLI Project Mandates - itemplatelib

This document outlines foundational mandates and architectural patterns for the `itemplatelib` project and its integration with related instrumentation provider projects.

## Development Standards

### Toolchain
- **Compiler:** Always use **Clang** (`clang` for C, `clang++` for C++).
- **Build System:** Use **CMake** with the **Ninja** generator (`-G Ninja`).
- **Build Type:** Default to `Debug` for development and testing unless `Release` is explicitly requested.

### Project Structure
- **Headers:** Maintain a standard include directory structure (`include/itemplatelib/*.h`).
- **Exports:** For DLL projects like `iprovider`, use the `UNMANGLED_LIB_EXPORTS` macro to ensure C-API compatibility (extern "C").
- **Organization:** Keep `src`, `include`, `tests`, and `scripts` distinct.

### Windows Specifics
- **Process Management:** When launching external tools like `socwatch.exe`, use `CreateProcessW` with the `CREATE_NO_WINDOW` flag for silent execution.
- **Execution Directory:** Be mindful of paths; ensure the working directory contains necessary executables (e.g., `socwatch.exe`) during test runs.

## Key Workflows
1. **Reproduction:** Before applying fixes, verify issues using existing or new test cases in the `tests/` directory.
2. **Build scripts:** Maintain `scripts/build_windows_x64.bat` as the primary entry point for automated builds.
3. **Integration:** Check sibling directories like `iprovider` for related shared library implementation and configuration.
