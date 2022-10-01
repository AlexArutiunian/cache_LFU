#pragma once

#include <iterator>
#include <list>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <algorithm>


template <typename T = int> struct page {
    T id;
    int freq;
    page(){ freq = 0; }  
};

namespace caches {  
template <typename T = int, typename KeyT = page<int>> struct cache_t{

    size_t sz_;
    std::list<KeyT> cache_;
    using ListIt = typename std::list<KeyT>::iterator;
    std::unordered_map<T, ListIt> hash_; 

    cache_t(size_t sz) : sz_(sz) {}

    bool full() const { return (cache_.size() == sz_); }
    
    bool lookup_update(KeyT key) {    
        auto it = hash_.find(key.id);
        if(it == hash_.end()){            
            
            if(full()){                        
                auto i = cache_.begin();
                auto kick_it = hash_.find(i->id);  
                hash_.erase(kick_it);
                cache_.pop_front();         
            }

            key.freq += 1;      
            cache_.push_front(key);
            hash_[key.id] = cache_.begin();
            for(auto i = cache_.begin(); i != cache_.end(); i++) std::cout << i->id << " ";
            std::cout << " " << std::endl;
            return false;          
        }
               
        else{     
            (it->second)->freq += 1;
            auto i = cache_.begin();                         // save freq sort in cache_
            auto kick = cache_.begin();
            for(i; (i->freq <= (it->second)->freq) && (i != cache_.end()); i++){
                if(((i->freq) == (it->second)->freq) && ((i->id) == (it->second)->id)) kick = i;
            }
  
            auto itr = cache_.insert(i, *(it->second));
            auto kick_it = hash_.find(kick->id);
            cache_.erase(kick);
            hash_.erase(kick_it);
            
            hash_[((it->second)->id)] = itr;
             
            return true;
        }   
    }
       
    };
}


