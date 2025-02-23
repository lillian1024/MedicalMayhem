cmake_minimum_required(VERSION 3.10)

# set the project name
project(MedicalMayhem VERSION 1.0 LANGUAGES C)

include(CTest)

set(MAIN_C_FILE "src/main.c")

# set build folders
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

set(RESOURCE_FILE my.rc)

# set compiler details
add_compile_options(-Wall -Wextra -Werror -g)

# auto-fill config header file
configure_file(src/config.h.in src/config.h)

# add the executables
file (GLOB_RECURSE TESTS_SOURCES CONFIGURE_DEPENDS "tests/*.c")
file (GLOB_RECURSE Gcc_SOURCES CONFIGURE_DEPENDS "src/*.c")
file (GLOB_RECURSE Gcc_HEADERS CONFIGURE_DEPENDS "src/*.h")

list(LENGTH Gcc_SOURCES SOURCES_LENGTH)

# Prepare test sources
file(REAL_PATH ${MAIN_C_FILE} REAL_MAIN_PATH)
list(SUBLIST Gcc_SOURCES 0 ${SOURCES_LENGTH} TEST_SOURCES)
list(REMOVE_ITEM TEST_SOURCES ${REAL_MAIN_PATH})

set (Gcc_INCLUDE_DIRS "")
foreach (_headerFile ${Gcc_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND Gcc_INCLUDE_DIRS ${_dir})
endforeach()
list (REMOVE_DUPLICATES Gcc_INCLUDE_DIRS)

# Compile app executable
add_executable(MedicalMayhem ${Gcc_SOURCES} ${RESOURCE_FILE})

target_sources(MedicalMayhem PRIVATE ${RESOURCE_FILE})

# Compile test executables
foreach (_testFile ${TESTS_SOURCES})
    cmake_path(GET _testFile FILENAME _filename)
    cmake_path(REMOVE_EXTENSION _filename OUTPUT_VARIABLE _filenameNoExt)
    list(APPEND _fileSources ${_testFile})
    list(APPEND _fileSources ${TEST_SOURCES})
    add_executable(${_filenameNoExt} ${_fileSources})
    unset(_fileSources)
    # target_link_libraries(${_filename} vtkCommon)
    add_test(NAME ${_filenameNoExt} COMMAND ${_filenameNoExt})
endforeach()

target_include_directories(MedicalMayhem PRIVATE ${Gcc_INCLUDE_DIRS})
