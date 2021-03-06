cmake_minimum_required(VERSION 2.6)

project(HSAIL-Tools)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules")

include(CMakeDependentOption)


find_package(LibElf)

if(LIBELF_FOUND)
  find_package(LibDwarf)
endif()

find_package(RE2C REQUIRED)
find_package(LLVM REQUIRED)

option(BUILD_HSAILASM "Build HSAILAsm" ON)


# Only try to build libbrigdwarf if we have both libelf and libdwarf.

# TODO: The checks for libdwarf and libelf need to be refined. There
# are several versions of each, and not all of them work here.
# e.g. This does not build with the versions in macports.
cmake_dependent_option(BUILD_LIBBRIGDWARF "Build libbrigdwarf" ON
  "LIBELF_FOUND;LIBDWARF_FOUND" OFF)

message(STATUS "Building HSAILAsm: ${BUILD_HSAILASM}")
message(STATUS "Building libbrigdwarf: ${BUILD_LIBBRIGDWARF}")


#find_library(LLVM_SUPPORT_LIB LLVMSupport)
if (LIBDWARF_USE_INIT_C)
  add_definitions("-DLIBDWARF_USE_INIT_C")
endif()

if(MSVC)
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

if(UNIX)
  #FIXME: Should set -fno-rtti etc. from LLVM config flags.
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_CFLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_CFLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pthread -D __STDC_LIMIT_MACROS -D __STDC_CONSTANT_MACROS  -D __STDC_FORMAT_MACROS -fno-rtti -fvisibility-inlines-hidden")
endif()

add_subdirectory(libHSAIL)
add_subdirectory(libHSAIL-AMD)

# FIXME: We should check for a usable version of libelf / libdwarf.
if(BUILD_HSAILASM)
  add_subdirectory(HSAILAsm)
endif()

if(BUILD_HSAILTESTGEN)
  add_subdirectory(libTestGen)
  add_subdirectory(HSAILTestGen)
endif()
