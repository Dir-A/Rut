# Main CMakeLists
cmake_minimum_required(VERSION 3.15)

# Project Name
project(Rut)

# Cpp Standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set Source File Path
list(APPEND SRC_FILE 
    "src/RxSys/Win32/File.cpp" 
    "src/RxSys/Win32/Path.cpp" 
    "src/RxSys/Win32/String.cpp" 
    "src/RxSys/Win32/System.cpp" 
    "src/RxBench.cpp" 
    "src/RxCmd.cpp" 
    "src/RxPath.cpp" 
    "src/RxFile.cpp" 
    "src/RxMem.cpp" 
    "src/RxINI.cpp" 
    "src/RxJson.cpp" 
    "src/RxStr.cpp" )

# Set Library
add_library("${PROJECT_NAME}" "${SRC_FILE}")
target_include_directories(Rut INTERFACE "src")

# Compiler
target_compile_definitions(Rut INTERFACE UNICODE _UNICODE)
target_link_options(Rut INTERFACE "$<$<CXX_COMPILER_ID:MSVC>:/OPT:REF>")
target_link_options(Rut INTERFACE "$<$<CXX_COMPILER_ID:MSVC>:/LTCG:INCREMENTAL>")
target_compile_options(Rut INTERFACE "$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>")

# Test
if(RUT_BUILD_TEST)
    add_subdirectory("test")
endif()

