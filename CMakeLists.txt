cmake_minimum_required(VERSION 3.14)
project(polprodukty)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors -Wconversion)

include_directories(
        include
        netsim_tests
        )

set(SOURCE_FILES
        src/package.cpp
        src/storage_types.cpp
        src/helpers.cpp
        src/factory.cpp
        src/nodes.cpp
        src/reports.cpp
        src/simulation.cpp
        )

add_executable(polprodukty_debug ${SOURCE_FILES} main.cpp)

set(SOURCES_FILES_TESTS
        netsim_tests/test/test_storage_types.cpp
        netsim_tests/test/test_package.cpp
        netsim_tests/test/test_nodes.cpp
        netsim_tests/test/test_Factory.cpp
        netsim_tests/test/test_factory_io.cpp
        netsim_tests/test/test_reports.cpp
        netsim_tests/test/test_simulate.cpp
        )

# Dodaj konfigurację typu `Test`.
add_executable(polprodukty_test ${SOURCE_FILES} ${SOURCES_FILES_TESTS} netsim_tests/test/main_gtest.cpp)

target_compile_definitions(polprodukty_test PUBLIC EXERCISE_ID=SIMULATION)

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