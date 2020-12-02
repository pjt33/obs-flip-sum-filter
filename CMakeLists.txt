cmake_minimum_required(VERSION 3.10)

project(obs-flip-sum-filter VERSION 0.0.1)

set(PLUGIN_AUTHOR "Peter Taylor")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(LibObs REQUIRED)

configure_file(
	src/plugin-macros.h.in
	../src/plugin-macros.generated.h
)

set(PLUGIN_SOURCES
	src/obs-flip-sum-filter.c
	src/flip-sum-filter.c
)

set(PLUGIN_HEADERS
	src/plugin-macros.generated.h
)

# --- Platform-independent build settings ---
add_library(${CMAKE_PROJECT_NAME} MODULE ${PLUGIN_SOURCES} ${PLUGIN_HEADERS})
target_link_libraries(${CMAKE_PROJECT_NAME}
	libobs
)

# --- Linux-specific build settings and tasks ---
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall")
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES PREFIX "")
