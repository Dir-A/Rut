# Main CMakeLists
cmake_minimum_required(VERSION 3.15)

# Project Name
project(Rut)

# Cpp Standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set Source File Path
list(APPEND SRC_FILE 
    "src/Rut/RxSys/Win32/File.cpp" 
    "src/Rut/RxSys/Win32/Path.cpp" 
    "src/Rut/RxSys/Win32/String.cpp" 
    "src/Rut/RxSys/Win32/System.cpp" 
    "src/Rut/RxBench.cpp" 
    "src/Rut/RxCmd.cpp" 
    "src/Rut/RxPath.cpp" 
    "src/Rut/RxFile.cpp" 
    "src/Rut/RxMem.cpp" 
    "src/Rut/RxINI.cpp" 
    "src/Rut/RxJson.cpp" 
    "src/Rut/RxStr.cpp" )

# Set Library
add_library("${PROJECT_NAME}" "${SRC_FILE}")
target_include_directories(Rut INTERFACE "src")

# Compiler
target_compile_definitions(Rut PRIVATE UNICODE _UNICODE)
target_compile_options(Rut PRIVATE "$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>")

# Test
if(RUT_BUILD_TEST)
    add_subdirectory("test")
endif()

