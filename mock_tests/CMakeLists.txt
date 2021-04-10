cmake_minimum_required(VERSION 3.15)
project(main)

# -----------------------------------
# Флаги и версии

set(CMAKE_CXX_STANDARD 14)
set(GOOGLETEST_VERSION 1.10.0)
SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage --coverage -fno-inline")
SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage --coverage -fno-inline")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage -fno-inline")

# -----------------------------------
# Подключаем Google Test и Mock

set(WORKING_GTEST_COMMIT https://github.com/google/googletest/archive/965f8ecbfd8b91bbd4f5ee4914c028660bb89029.zip)
include(FetchContent)
FetchContent_Declare(
        googletest
        URL ${WORKING_GTEST_COMMIT}
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()
include(GoogleTest)

# -----------------------------------
# Проект

add_executable(
        main
        main.cpp
)
target_link_libraries(
        main
        gtest_main
        gmock
)

