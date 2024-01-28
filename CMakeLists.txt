if (TARGET Rut)
   return()
endif()

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


