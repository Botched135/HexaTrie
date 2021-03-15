#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "hex_trie_fixture.hpp"
#include "doctest/doctest.h"
#define TEST_BYTES bytes<1>, bytes<2>, bytes<3>, bytes<4>, bytes<5>, bytes<6>, bytes<7>, bytes<8>, bytes<9>, bytes<10>, bytes<11>, bytes<12>

template<size_t size>
struct bytes
{
    static constexpr size_t m_size = size;
    bytes()=default;
    explicit bytes(uint32_t init_val)
    {
        for (size_t i = 0; i < size; ++i)
            data[i] = init_val++;
    }
    char data[size]{};
};
TEST_SUITE("HexTrie Look-up")
{
    TEST_CASE_TEMPLATE("Contain for existing ids just after insert succeeds", T, TEST_BYTES)
    {
        size_t id_count = 10'000;
        std::vector<uint32_t> ids(id_count);
        std::iota(ids.begin(), ids.end(), 0);
        botched::dynamic_hex_trie<int,T> trie;

        for(auto& x: ids)
        {
            trie.insert(x, T());
            CHECK(trie.contains(x));
        }
    }
    TEST_CASE_TEMPLATE("Contain for existing ids succeeds", T, TEST_BYTES)
    {
        hex_trie_fixture<uint32_t, T> fixture;
        size_t id_count = 10'000;
        fixture.init_hex_trie(id_count,0,1);

        for(auto& x: fixture.data)
            CHECK(fixture.hex_trie.contains(x));

    }

    TEST_CASE_TEMPLATE("Contain for non-existing ids fails", T, TEST_BYTES)
    {
        hex_trie_fixture<uint32_t, T> fixture;
        size_t id_count = 10'000;
        fixture.init_hex_trie_two_vectors(id_count,0,1);

        for(auto& x: fixture.non_data)
            CHECK(!fixture.hex_trie.contains(x));

    }

    TEST_CASE_TEMPLATE("Find for existing ids succeeds", T, TEST_BYTES)
    {
        hex_trie_fixture<uint32_t, T> fixture;
        size_t id_count = 10'000;
        auto mod_value = 256;
        fixture.init_hex_trie(id_count,0,1,mod_value);

        for(auto& x: fixture.data)
        {
            auto current_item = fixture.hex_trie.find(x);
            REQUIRE(current_item != nullptr);
            for (int i = 0; i < T::m_size ; ++i)
            {
                //CHECK(current_item->data[i] == ((x%mod_value)+i));
            }
        }
    }

    TEST_CASE_TEMPLATE("Find for non-existing ids fails", T, TEST_BYTES)
    {
        hex_trie_fixture<uint32_t, T> fixture;
        size_t id_count = 10'000;
        fixture.init_hex_trie(id_count,0,1,256);

        for(auto& x: fixture.non_data)
            CHECK(fixture.hex_trie.find(x) == nullptr);

    }

}