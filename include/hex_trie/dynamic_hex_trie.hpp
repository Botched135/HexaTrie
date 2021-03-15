//
// Created by rbo on 14/03/2021.
//

#ifndef HEXTRIE_DYNAMIC_HEX_TRIE_HPP
#define HEXTRIE_DYNAMIC_HEX_TRIE_HPP
#define BIT_SHIFT 4
#include "typedef.hpp"
namespace botched
{
    template<typename K, typename V>
    class dynamic_hex_trie
    {
        struct node;
        struct branch;
        node m_root;
        u64 m_size;
        template<typename T>
        static T* mult_ptr(T* ptr, u64 val)
        {
            return reinterpret_cast<T*>(reinterpret_cast<u64>(ptr)*val);
        }
        struct branch
        {
            node m_children[16];
        };
        struct node
        {
            branch* m_branch = nullptr;
            V* m_value = nullptr;
            node() = default;
            ~node()
            {
                delete m_branch;
                delete m_value;
                m_branch = nullptr;
                m_value = nullptr;
            }

        };
        // Lets just say that branchless implementation is 8 times faster than the branching one, at 10'000 iterations
        // since the branchless implementation didn't find anything, we need to test again
        node* walk_trie(K& key)
        {
            node* currentNode = &m_root;
            K hex_index, end = 1;
            while(key * end > 0)
            {
                hex_index = key & 0xF;
                currentNode = &currentNode->m_branch->m_children[hex_index];
                end = currentNode->m_branch != nullptr;
                key >>= BIT_SHIFT;
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

                currentNode = &currentNode->m_branch->m_children[hex_index];
                key >>= BIT_SHIFT;
            }
            return currentNode->m_value = new V;
        }
    public:
        dynamic_hex_trie(): m_size(0){}
        V* find(K key)
        {
            auto final_node = walk_trie(key)->m_value;
            return mult_ptr(final_node, key == 0);
        }

        bool contains(K key)
        {
            return reinterpret_cast<u64>(walk_trie(key)->m_value)*(key == 0);
        }

        V& insert(K key, V value)
        {
            V* x = create_node_path(key);
            return *x = value;
        }
/*
        V& insert_or_assign(K key, V value)
        {

        }

        V& emplace(K key, V value)
        {

        }*/
    };
}
#endif //HEXTRIE_DYNAMIC_HEX_TRIE_HPP
