cmake_minimum_required(VERSION 3.14)
project(polprodukty)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors -Wconversion)

include_directories(
        include
        )

set(SOURCE_FILES
        src/package.cpp
        src/storage_types.cpp
        )

add_executable(polprodukty_debug ${SOURCE_FILES} main.cpp)

set(SOURCES_FILES_TESTS
        netsim_tests/test/test_storage_types.cpp
        netsim_tests/test/test_package.cpp
        )

# Dodaj konfigurację typu `Test`.
add_executable(polprodukty_test ${SOURCE_FILES} ${SOURCES_FILES_TESTS} netsim_tests/test/main_gtest.cpp)

target_compile_definitions(polprodukty_test PUBLIC EXERCISE_ID=1)

# Dodaj katalogi z plikami nagłówkowymi wyłącznie do konkretnej konfiguracji (tu: `Test`).
target_include_directories(polprodukty_test PUBLIC
        googletest-master/googlemock/include
        googletest-master/googletest/include
        mocks
        )

# Dodaj podkatalog `googletest-master`.
add_subdirectory(googletest-master)

# Podlinkuj bibliotekę o identyfikatorze `gmock` (w pliku CMake) wyłącznie do konkretnej
# konfiguracji (tu: `Test`).
target_link_libraries(polprodukty_test gmock)