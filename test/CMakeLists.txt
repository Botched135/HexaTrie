add_executable(hex_trie_test "")

target_include_directories(hex_trie_test
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/data>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/doctest>
)

target_sources(hex_trie_test
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/hex_trie_load_test.cpp
)

target_link_libraries(hex_trie_test PUBLIC botched135::hex_trie)

add_test(NAME hex_trie_test COMMAND hex_trie_test)