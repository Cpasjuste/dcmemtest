cmake_minimum_required(VERSION 3.0)
#set(CMAKE_VERBOSE_MAKEFILE ON)

# add libcross2d library
add_subdirectory(libcross2d)

#############
# RetroDream
#############
project(dcmemtest)

set(PROJECT_AUTHOR "Cpasjuste")
set(VERSION_MAJOR "1")
set(VERSION_MINOR "0")
set(VERSION_MICRO "0")

#############
# code
#############
file(GLOB SOURCES src/*)
set(INCLUDES src)
set(CFLAGS
        -DVERSION_MAJOR="${VERSION_MAJOR}"
        -DVERSION_MINOR="${VERSION_MINOR}"
        -DVERSION_MICRO="${VERSION_MICRO}"
        -D__RETRODREAM__)
set(LDFLAGS)

if (PLATFORM_DREAMCAST)
    list(APPEND LDFLAGS)
endif ()

#############
# executable
#############
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDES})
target_compile_options(${PROJECT_NAME} PRIVATE ${CFLAGS})
target_link_libraries(${PROJECT_NAME} cross2d ${LDFLAGS})
if (PLATFORM_DREAMCAST)
    # for dcload-serial binary size
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS -s)
endif ()
#############
# targets
#############
include(${CMAKE_SOURCE_DIR}/libcross2d/cmake/targets.cmake)
