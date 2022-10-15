#pragma once

#include <iterator>
#include <list>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <algorithm>




namespace caches {  
template <typename T, typename KeyT = int> struct cache_t{
    

    struct page{
    KeyT id;
    int freq = 1;
    
    bool operator<(const page & rhs)
    {
        return freq < rhs.freq;
    }
    
    };

    std::size_t sz_;
    std::list<page> cache_;
    using ListIt = typename std::list<page>::iterator;
    std::unordered_map<KeyT, ListIt> hash_; 

    cache_t(size_t sz) : sz_(sz) {}

    bool full() const { return (cache_.size() == sz_); }
    
    template <typename F>
    bool lookup_update(KeyT k, F slow_get_page) { 
           
        auto it = hash_.find(k);
        if(it == hash_.end()){            
            if(full()){ 
                cache_.sort();                       
                auto i = cache_.begin();
                auto kick_it = hash_.find(i->id);  
                hash_.erase(kick_it);
                cache_.pop_front();         
            }      
            cache_.push_front({k, 1});
            hash_[k] = cache_.begin();
            return false;          
        }
               
        else{     
            (it->second)->freq += 1;                        
            return true;
        }   
    }
       
    };
}


