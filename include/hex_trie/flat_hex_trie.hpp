//
// Created by rbo on 12/03/2021.
//

#ifndef HEXTRIE_FLAT_HEX_TRIE_HPP
#define HEXTRIE_HEX_TRIE_HPP
#define BITS_MOVED 4
#include "typedef.hpp"
#include <utility>

namespace botched
{
    template<typename K, typename V>
    class flat_hex_trie
    {
        node m_root;
        V* m_data;
        u64 m_size, m_capacity;
        static K* mult_ptr(K* ptr, u64 val)
        {
            return reinterpret_cast<K*>(reinterpret_cast<u64>(ptr)*val);
        }
        // size
        // underlying data (enables iterators, however should not allow random access)
        struct branch
        {
            node m_children[16]
        };
        struct node
        {
            branch* m_branch = nullptr;
            u64 m_value_offset = -1;
            node() = default;
            ~node()
            {
                delete m_branch;
                m_branch = nullptr;
            }

        };

        node* walk_trie(K& key)
        {
            node* currentNode = &m_root;
            K hex_index, end;
            while(key * end > 0)
            {
                hex_index = key & 0xF;
                currentNode = &(*currentNode).m_branch.m_children[hex_index];
                end = currentNode->m_branch != nullptr;
                key >>= BITS_MOVED * end;
            }
            return currentNode;
        }
        V* create_node_path(K key)
        {
            node* currentNode = &m_root;
            K hex_index;

            while(key > 0)
            {
                hex_index = key & 0xF;
                //hexa_track_id*= (currentNode->m_children != nullptr);
                // is there anyway to avoid this branching? I dont think so
                if(!currentNode->m_branch) currentNode->m_branch = new branch;
                currentNode = (*currentNode->m_branch).m_children[hex_index];
                key >>= BITS_MOVED;
            }
            return currentNode->m_value;
        }
    public:
        flat_hex_trie(): m_size(0), m_capacity(0), m_data(nullptr){}
        ~flat_hex_trie()
        {
            delete [] m_data;
        }
        u64 reserve(u64 n)
        {
            if(n <= m_capacity)
                return m_capacity;

            V* temp_data =  new V[n];
            if(m_data)
            {
                for (u64 i = 0; i < m_size ; ++i)
                    temp_data[i] = std::move(m_data[i]);
            }

            m_data = temp_data;
            m_capacity = n;
            return m_capacity

        }
        V* find(K key)
        {
            return mult_ptr(walk_trie(key)->m_value_offset+m_root, (key == 0));
        }

        bool contains(K key)
        {
            return (walk_trie(key)->m_value_offset >= 0)*(key == 0);
        }

        V& insert(K key, V value)
        {
            V* x = create_node_path(key);

        }

        V& insert_or_assign(K key, V value)
        {

        }

        V& emplace(K key, V value)
        {

        }
    };
}
#endif //HEXATRIE_HEXA_TRIE_HPP
