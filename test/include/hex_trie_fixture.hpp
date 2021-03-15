//
// Created by rbo on 15/03/2021.
//

#ifndef HEX_TRIE_HEX_TRIE_FIXTURE_HPP
#define HEX_TRIE_HEX_TRIE_FIXTURE_HPP
#include "hex_trie/dynamic_hex_trie.hpp"
#include <algorithm>
#include <vector>
#include <numeric>
#include <cstdint>

template<typename K, typename V>
class hex_trie_fixture
{
public:
    botched::dynamic_hex_trie<K,V> hex_trie;
    std::vector<K> data;
    std::vector<K> non_data;
    void init_hex_trie(size_t total_tracks, size_t initial_value, size_t increment)
    {
        data.resize(total_tracks);
        std::generate(data.begin(), data.end(), [n = initial_value, increment] () mutable {return n+=increment;});

        for(auto& x: data)
        {
            hex_trie.insert(x, V());
            //REQUIRE(hex_trie.contains(x));
        }
    }

    void init_hex_trie_two_vectors(size_t total_tracks, size_t initial_value, size_t increment)
    {
        data.resize(total_tracks);
        non_data.resize(total_tracks);
        std::generate(data.begin(), data.end(), [n = initial_value, increment] () mutable {return n+=increment;});
        std::generate(data.begin(), data.end(), [n = data.back()+1, increment] () mutable {return n+=increment;});

        for(auto& x: data)
        {
            hex_trie.insert(x, V());
            //REQUIRE(hex_trie.contains(x));
        }
    }

    void init_hex_trie(size_t total_tracks, size_t initial_value, size_t increment, uint32_t mod_value)
    {
        data.resize(total_tracks);
        std::generate(data.begin(), data.end(), [n = initial_value, increment] () mutable {return n+=increment;});

        for(auto& x: data)
        {
            hex_trie.insert(x, V(x % mod_value));
            //REQUIRE(hex_trie.contains(x));
        }
    }

    void init_hex_trie_two_vectors(size_t total_tracks, size_t initial_value, size_t increment, uint32_t mod_value)
    {
        data.resize(total_tracks);
        non_data.resize(total_tracks);
        std::generate(data.begin(), data.end(), [n = initial_value, increment] () mutable {return n+=increment;});
        std::generate(data.begin(), data.end(), [n = data.back()+1, increment] () mutable {return n+=increment;});

        for(auto& x: data)
        {
            hex_trie.insert(x, V(x%mod_value));
            //REQUIRE(hex_trie.contains(x));
        }
    }
};
#endif //HEX_TRIE_HEX_TRIE_FIXTURE_HPP
