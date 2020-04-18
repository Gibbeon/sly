cmake_minimum_required(VERSION 2.8.9)
project(slyedit)

add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(MACOSX TRUE)
endif()

if(WIN32)
  SET(GFXAPI "D3D12")
else()
  SET(GFXAPI "METAL")
endif()

include_directories(./include)
include_directories(../packages/json/single_include)
include_directories(../packages/GSL/include)
include_directories(../packages/glm)

include_directories(../slycore/include)
include_directories(../slyengine/include)

target_link_directories(slycore PUBLIC ../lib)
target_link_directories(slyengine PUBLIC ../lib)

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

#find_library(SLYCORE_LIB slycore${CMAKE_STATIC_LIBRARY_SUFFIX}  PATHS ../slycore/lib)
#find_library(SLYENGINE_LIB slyengine${CMAKE_STATIC_LIBRARY_SUFFIX}  PATHS ../slyengine/lib)

target_link_libraries(${PROJECT_NAME} slycore${CMAKE_STATIC_LIBRARY_SUFFIX})
target_link_libraries(${PROJECT_NAME} slyengine${CMAKE_STATIC_LIBRARY_SUFFIX})
target_link_directories(${PROJECT_NAME} PUBLIC ../lib)


if(${GFXAPI} MATCHES "D3D12")
    include_directories(../slyd3d12/include)
    #find_library(SLYD3D12_LIB slyd3d12${CMAKE_STATIC_LIBRARY_SUFFIX} PATHS ../slyd3d12/lib)
    target_link_libraries(${PROJECT_NAME} slyd3d12.lib)

    target_link_libraries(${PROJECT_NAME} d3d12.lib)
    target_link_libraries(${PROJECT_NAME} dxgi.lib)
    target_link_libraries(${PROJECT_NAME} d3dcompiler.lib)
    target_link_libraries(${PROJECT_NAME} dxguid.lib)

elseif(${GFXAPI} MATCHES "D3D11")
    target_link_libraries(${PROJECT_NAME} slyd3d11${CMAKE_STATIC_LIBRARY_SUFFIX})
    target_link_libraries(${PROJECT_NAME} d3d11${CMAKE_STATIC_LIBRARY_SUFFIX})
    target_link_libraries(${PROJECT_NAME} dxgi${CMAKE_STATIC_LIBRARY_SUFFIX})
    target_link_libraries(${PROJECT_NAME} d3dcompiler${CMAKE_STATIC_LIBRARY_SUFFIX})
elseif(${GFXAPI} MATCHES "OPENGL4")
    target_link_libraries(${PROJECT_NAME} slygl4${CMAKE_STATIC_LIBRARY_SUFFIX} )
endif()

if(WIN32)
    include_directories(../slywin32/include)
    #find_library(SLYWIN32_LIB slywin32${CMAKE_STATIC_LIBRARY_SUFFIX} PATHS ../slywin32/lib)
    target_link_libraries(${PROJECT_NAME} slywin32.lib)
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
  #string(REPLACE "/EHsc" "" ${flag_var} "${${flag_var}}")
endforeach()
endif()