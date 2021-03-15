cmake_minimum_required(VERSION 3.12)
project(hex_trie VERSION 1.0.0 LANGUAGES CXX)

option(HEX_TRIE_TEST "Generate the test target." ON)


add_library(${PROJECT_NAME}  INTERFACE)
add_library(botched135::hex_trie ALIAS ${PROJECT_NAME} )

target_include_directories(${PROJECT_NAME} INTERFACE
	$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  	$<INSTALL_INTERFACE:include/)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)

enable_testing()
add_subdirectory(test)

