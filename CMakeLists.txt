cmake_minimum_required(VERSION 3.31)
project(assimpts
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS                       OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL                          OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS                      OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT   ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ZLIB                       ON CACHE BOOL "" FORCE)
add_subdirectory(assimp)

if (CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    message(STATUS "Configuring Emscripten/WebAssembly build")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --emit-tsd assimpts.d.ts" CACHE STRING "" FORCE)
endif()

set(ASSIMPTS_SOURCES
    src/main.cpp
)

add_executable(assimpts)
target_sources(assimpts PRIVATE ${ASSIMPTS_SOURCES})

target_link_libraries(assimpts PRIVATE assimp)
target_include_directories(assimpts PRIVATE assimp/include)

set_target_properties(assimpts
    PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/dist"
)
