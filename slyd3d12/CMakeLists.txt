cmake_minimum_required(VERSION 2.8.9)
project(slyd3d12)

set(CMAKE_SUPPRESS_REGENERATION true)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../bin)

# Second, for multi-config builds (e.g. msvc)
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY} )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )
 
#sample doesn't work without this, we should figure out why
add_compile_options("/sdl")

include_directories(./include)
include_directories(./../slycore/include)
include_directories(./../slywin32/include)
 
link_directories(./../slycore/lib)
link_directories(./../slywin32/lib)

#this isn't best practice
file(GLOB_RECURSE SOURCES "src/*.cpp" )

add_library(${PROJECT_NAME} SHARED ${SOURCES})

find_library(SLYCORE_LIB slycore PATHS ./../slycore/lib)
find_library(SLYWIN32_LIB slywin32 PATHS ./../slywin32/lib)

target_link_libraries(${PROJECT_NAME} ${SLYCORE_LIB})
target_link_libraries(${PROJECT_NAME} ${SLYWIN32_LIB})
target_link_libraries(${PROJECT_NAME} d3d12.lib)
target_link_libraries(${PROJECT_NAME} dxgi.lib)
target_link_libraries(${PROJECT_NAME} d3dcompiler.lib)

if (MSVC)
# For MSVC, CMake sets certain flags to defaults we want to override.
# This replacement code is taken from sample in the CMake Wiki at
# https://gitlab.kitware.com/cmake/community/wikis/FAQ#dynamic-replace.
foreach (flag_var
         CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
         CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
  if (NOT BUILD_SHARED_LIBS)
    string(REPLACE "/MD" "-MT" ${flag_var} "${${flag_var}}")
  endif()

  # Prevent D9025 warning for targets that have exception handling
  # turned off (/EHs-c- flag). Where required, exceptions are explicitly
  # re-enabled using the cxx_exception_flags variable.
  # string(REPLACE "/EHsc" "" ${flag_var} "${${flag_var}}")
endforeach()
endif()