
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


if( CMAKE_CROSSCOMPILING )
    set(CMAKE_EXECUTABLE_SUFFIX ".elf")
endif()

