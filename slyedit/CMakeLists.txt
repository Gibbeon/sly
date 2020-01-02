cmake_minimum_required(VERSION 2.8.9)
project(slyedit)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(MACOSX TRUE)
endif()

if(WIN32)
  SET(GFXAPI "D3D12" CACHE STRING "D3D12, D3D11, OPENGL4, METAL")
else()
  SET(GFXAPI "METAL" CACHE STRING "D3D12, D3D11, OPENGL4, METAL")
endif()

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
else()
  add_compile_options("-g")
endif()

include_directories(./include)
include_directories(../packages/json/single_include)
include_directories(../packages/GSL/include)

include_directories(../slycore/include)
include_directories(../slyengine/include)

link_directories(../slycore/lib)
link_directories(../slyengine/lib)
 
#this isn't best practice
file(GLOB_RECURSE SOURCES "src/*.cpp" )

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

# Link shared library with apple OS libraries
if (MACOSX)
	find_library(CoreFoundation CoreFoundation)
	target_link_libraries(${PROJECT_NAME} ${CoreFoundation})
  target_link_libraries(${PROJECT_NAME} "-framework Metal")
  target_link_libraries(${PROJECT_NAME} "-framework AppKit")
  target_link_libraries(${PROJECT_NAME} "-framework MetalKit")
endif()

find_library(SLYCORE_LIB slycore${CMAKE_STATIC_LIBRARY_SUFFIX}  PATHS ../slycore/lib)
find_library(SLYENGINE_LIB slyengine${CMAKE_STATIC_LIBRARY_SUFFIX}  PATHS ../slyengine/lib)

target_link_libraries(${PROJECT_NAME} ${SLYCORE_LIB})
target_link_libraries(${PROJECT_NAME} ${SLYENGINE_LIB})


if(${GFXAPI} EQUAL "D3D12")
    include_directories(../slyd3d12/include)
    link_directories(../slyd3d12/lib)
    target_link_libraries(${PROJECT_NAME} slyd3d12${CMAKE_SHARED_LIBRARY_SUFFIX})
    target_link_libraries(${PROJECT_NAME} dxgi${CMAKE_STATIC_LIBRARY_SUFFIX})
    target_link_libraries(${PROJECT_NAME} d3dcompiler${CMAKE_STATIC_LIBRARY_SUFFIX})
elseif(${GFXAPI} EQUAL "D3D11")
    target_link_libraries(${PROJECT_NAME} slyd3d11${CMAKE_STATIC_LIBRARY_SUFFIX})
    target_link_libraries(${PROJECT_NAME} d3d11${CMAKE_STATIC_LIBRARY_SUFFIX})
    target_link_libraries(${PROJECT_NAME} dxgi${CMAKE_STATIC_LIBRARY_SUFFIX})
    target_link_libraries(${PROJECT_NAME} d3dcompiler${CMAKE_STATIC_LIBRARY_SUFFIX})
elseif(${GFXAPI} EQUAL "OPENGL4")
    target_link_libraries(${PROJECT_NAME} slygl4${CMAKE_STATIC_LIBRARY_SUFFIX} )
endif()

if(WIN32)
    link_directories(../slywin32/lib)
    include_directories(../slywin32/include)
    find_library(SLYWIN32_LIB slywin32${CMAKE_STATIC_LIBRARY_SUFFIX} PATHS ../slywin32/lib)
    target_link_libraries(${PROJECT_NAME} ${SLYWIN32_LIB})
elseif(MACOSX)
    link_directories(../slymacos/lib)
    include_directories(../slymacos/include)
    find_library(SLYMACOS_LIB slymacos${CMAKE_STATIC_LIBRARY_SUFFIX} PATHS ../slymacos/lib)
    target_link_libraries(${PROJECT_NAME} ${SLYMACOS_LIB})
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