cmake_minimum_required(VERSION 3.10)

# set the project name
project(MedicalMayhem VERSION 1.0 LANGUAGES C)

# set build folders
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

# set compiler details
add_compile_options(-Wall -Wextra -Werror -g)
set(CMAKE_CC_COMPILER gcc)

# auto-fill config header file
configure_file(src/config.h.in src/config.h)

# add the executables
file (GLOB_RECURSE Gcc_SOURCES CONFIGURE_DEPENDS "src/*.c")
file (GLOB_RECURSE Gcc_HEADERS CONFIGURE_DEPENDS "src/*.h")

set (Gcc_INCLUDE_DIRS "")
foreach (_headerFile ${Gcc_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND Gcc_INCLUDE_DIRS ${_dir})
endforeach()
list (REMOVE_DUPLICATES Gcc_INCLUDE_DIRS)

add_executable(MedicalMayhem ${Gcc_SOURCES})

target_include_directories(MedicalMayhem PRIVATE ${Gcc_INCLUDE_DIRS})
