#pragma once

#include <iterator>
#include <list>
#include <unordered_map>
#include <iostream>


namespace caches {  
template <typename T, typename KeyT = int> struct cache_t{

    std::size_t sz_;
    std::size_t cp_;
    struct freq_value;
    struct elem{
        T value;
        KeyT key;
        using freq = typename std::list<freq_value>::iterator;
        freq itr_freq_node;
    };

    struct freq_value{
        std::list<elem> list_keys;
        int freq = 1;

    };
    
    std::list<freq_value> cache_;

    using ListKeysIt = typename std::list<elem>::iterator;
    std::unordered_map<KeyT, ListKeysIt> hash_;
    cache_t(std::size_t cp) : cp_{cp}, sz_{0} {};

    bool full() const { return (sz_ == cp_); }
    bool empty() const { return (sz_ == 0); }

    template <typename F>
    bool lookup_update(KeyT k, F slow_get_page) { 
        auto hit = hash_.find(k);
        if(hit == hash_.end()){
            if(full()){
            	delete_key();
                sz_--; 
            }

            if(empty()){
            
            // create node in front
            // for list in which
            // we add list_keys
 
                cache_.push_front({{}, 1}); 
            }
            
            
            // if node in which have to add 
            // list_keys for new elem not exists 
            // then create such a node at front

            if(cache_.front().freq != 1)
                cache_.push_front({{}, 1});
            
            
            push_key(k);
            sz_++;

            return false;
        }

        splice_(hit->second);
        return true;
    }

    void splice_(ListKeysIt it){
        auto & fr = it->itr_freq_node->freq;
        auto & itr_freq_node = it->itr_freq_node;
        
        // if found element has max freq
        // so it place in back cache, back freq_node
        // then create node in back and its freq+=1
        
        if(itr_freq_node == std::prev(cache_.end())){    
            cache_.push_back({{}, fr + 1});
        } 
        
        // if next node not fit for freq
        // for replace in next node
        // then create new node with fit freq

        else if(std::next(itr_freq_node)->freq != fr + 1)
            cache_.insert(std::next(itr_freq_node), {{}, fr + 1});

        // replace in nose found element

        auto it_next_freq_node = std::next(itr_freq_node);
        it_next_freq_node->list_keys.splice(it_next_freq_node->list_keys.end(), itr_freq_node->list_keys, it); 
           
        // if after replace sublist is empthy
        // then delete it

        if(itr_freq_node->list_keys.size() == 0) cache_.erase(itr_freq_node);

        // now itr replaced elem link to another freq node

        itr_freq_node = it_next_freq_node;
    }

    void push_key(KeyT k){
        
        // add key in list_keys
        // in 1st node, because
        // save freq sort
        // to delete from front 

        cache_.front().list_keys.push_front({k, k, cache_.begin()});
        hash_[k] = cache_.front().list_keys.begin();
    }
    
    void delete_key(){
        // delete back element
        // from 1st sublist (list_keys)
   
        hash_.erase(cache_.front().list_keys.back().key);
        cache_.front().list_keys.pop_back();

        // if after delete 
        // 1st sublist is empthy
        // then delete it

        if(cache_.front().list_keys.size() == 0)
            cache_.pop_front();
          
    }
 
          
    };

    

    

}// namespace caches


