cmake_minimum_required(VERSION 3.1)
project(HexaTrie VERSION 1.0.0 LANGUAGES CXX)

option(HEXA_TRIE_TEST "Generate the test target." OFF)

if(HEXA_TRIE_TEST)
	enable_testing()
	add_subdirectory(test)
endif()


add_library(hexa_trie INTERFACE)
add_library(botched135::hexa_trie ALIAS hexa_trie)

target_include_directories(hexa_trie INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)