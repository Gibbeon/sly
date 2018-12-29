cmake_minimum_required(VERSION 2.8.9)
project(slyedit)

set(CMAKE_SUPPRESS_REGENERATION true)

SET(GFXAPI "D3D12" CACHE STRING "D3D12, D3D11, OPENGL4")

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
include_directories(../slyengine/include)

link_directories(../slyengine/lib)
link_directories(../slywin32/lib)
link_directories(../slyd3d12/lib)
link_directories(../slygl4/lib)
 
#this isn't best practice
file(GLOB_RECURSE SOURCES "src/*.cpp" )

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

target_link_libraries(${PROJECT_NAME} slyengine.lib)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} slywin32.lib)
    if(${GFXAPI} EQUAL "D3D12")
        target_link_libraries(${PROJECT_NAME} slyd3d12.lib)
        target_link_libraries(${PROJECT_NAME} d3d12.lib)
        target_link_libraries(${PROJECT_NAME} dxgi.lib)
        target_link_libraries(${PROJECT_NAME} d3dcompiler.lib)
    elseif(${GFXAPI} EQUAL "D3D11")
        target_link_libraries(${PROJECT_NAME} slyd3d11.lib)
        target_link_libraries(${PROJECT_NAME} d3d11.lib)
        target_link_libraries(${PROJECT_NAME} dxgi.lib)
        target_link_libraries(${PROJECT_NAME} d3dcompiler.lib)
    elseif(${GFXAPI} EQUAL "OPENGL4")
        target_link_libraries(${PROJECT_NAME} slygl4.lib)
        target_link_libraries(${PROJECT_NAME} opengl32.lib)
    endif()
endif()

