#pragma once

#include <iterator>
#include <list>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <algorithm>

struct page{
    int id;
    int freq;
    page(){ freq = 0; }
    
};

bool operator<(const page & lhs, const page & rhs)
{
    return lhs.freq < rhs.freq;
}

namespace caches {
template <typename T, typename KeyT = page> struct cache_t{

    size_t sz_;
    std::list<page> cache_;
    using ListIt = typename std::list<page>::iterator;
    std::unordered_map<int, ListIt> hash_; 

    cache_t(size_t sz) : sz_(sz) {}

    bool full() const { return (cache_.size() == sz_); }
    
    bool lookup_update(int k) {
        page key;
        key.id = k;
        auto it = hash_.find(key.id);
        if(it == hash_.end()){         
            if(full()){  
                
                cache_.sort();
                auto kick_it = hash_.begin();  
                key.freq += 1;
                hash_.erase(kick_it);
                cache_.push_front(key);
                hash_[key.id] = cache_.begin();   
            }

            key.freq += 1;      
            cache_.push_front(key);
            hash_[key.id] = cache_.begin();
            return false;
              
        }
               
        else{
            (it->second)->freq += 1;
            return true;
        } 
        }
    };
}
