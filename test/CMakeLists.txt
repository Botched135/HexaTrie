add_executable(hexa_trie_test "")

target_include_directories(hexa_trie_test
    PRIVATE 
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/data>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/doctest>
)

target_sources(hexa_trie_test
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/hexa_trie_load_test.cpp
)

target_link_library(hexa_trie_test hexa_trie)

add_test(NAME hexa_trie_test COMMAND hexa_trie_test)