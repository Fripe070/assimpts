cmake_minimum_required(VERSION 3.31)
project(AssimpTS
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS                       OFF CACHE BOOL "")
set(ASSIMP_BUILD_ZLIB                       ON  CACHE BOOL "")
set(ASSIMP_INSTALL                          OFF CACHE BOOL "")
set(ASSIMP_BUILD_TESTS                      OFF CACHE BOOL "")
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT   ON  CACHE BOOL "")
set(ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT   OFF CACHE BOOL "")

# Allows exporting as a JSON object that can be used in JS
set(ASSIMP_BUILD_ASSJSON_EXPORTER           ON  CACHE BOOL "")

add_subdirectory(assimp)

set(ASSIMPTS_SOURCES
    src/main.cpp
)

add_executable(AssimpTS)
target_sources(AssimpTS PRIVATE ${ASSIMPTS_SOURCES})

if (CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    message(STATUS "Configuring Emscripten/WebAssembly build")
    set_target_properties(AssimpTS PROPERTIES OUTPUT_NAME "assimpts") # Lowercase filenames
    target_link_options(AssimpTS PRIVATE --emit-tsd assimpts.d.ts)
	target_link_options(AssimpTS PRIVATE -lembind)

	target_link_options(AssimpTS PRIVATE -sMODULARIZE=1)
	target_link_options(AssimpTS PRIVATE -sEXPORT_ES6=1)
	target_link_options(AssimpTS PRIVATE -sEXPORT_NAME=loadAssimpTS)
endif()

target_link_libraries(AssimpTS PRIVATE assimp)
target_include_directories(AssimpTS PRIVATE assimp/include)

set_target_properties(AssimpTS
    PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/dist"
)
