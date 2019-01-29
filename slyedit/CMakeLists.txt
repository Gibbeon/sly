cmake_minimum_required(VERSION 2.8.9)
project(slyedit)

SET(GFXAPI "MACOS" CACHE STRING "D3D12, D3D11, OPENGL4, MACOS")

set(CMAKE_SUPPRESS_REGENERATION true)

set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

# Second, for multi-config builds (e.g. msvc)
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY} )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )
 
#sample doesn't work without this, we should figure out why
if (MSVC)
  add_compile_options("/sdl")
endif()

include_directories(./include)
include_directories(../slycore/include)
include_directories(../slyengine/include)

link_directories(../slycore/lib)
link_directories(../slyengine/lib)
link_directories(../slygl4/lib)
 
#this isn't best practice
file(GLOB_RECURSE SOURCES "src/*.cpp" )

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

find_library(SLYCORE_LIB slycore.a PATHS ../slycore/lib)
find_library(SLYWIN32_LIB slyengine.a PATHS ../slyengine/lib)
find_library(SLYMACOS_LIB slymacOS.a PATHS ../slymacOS/lib)

target_link_libraries(${PROJECT_NAME} ${SLYCORE_LIB})
target_link_libraries(${PROJECT_NAME} ${SLYWIN32_LIB})
target_link_libraries(${PROJECT_NAME} ${SLYMACOS_LIB})

if(WIN32)
    link_directories(../slywin32/lib)
    link_directories(../slyd3d12/lib)
    target_link_libraries(${PROJECT_NAME} slywin32.lib)
    if(${GFXAPI} EQUAL "D3D12")
        target_link_libraries(${PROJECT_NAME} slyd3d12.dll)

    elseif(${GFXAPI} EQUAL "D3D11")
        target_link_libraries(${PROJECT_NAME} slyd3d11.lib)
        target_link_libraries(${PROJECT_NAME} d3d11.lib)
        target_link_libraries(${PROJECT_NAME} dxgi.lib)
        target_link_libraries(${PROJECT_NAME} d3dcompiler.lib)
    elseif(${GFXAPI} EQUAL "OPENGL4")
        target_link_libraries(${PROJECT_NAME} slygl4.lib)
    endif()
else()

endif()


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
  string(REPLACE "/EHsc" "" ${flag_var} "${${flag_var}}")
endforeach()
endif()