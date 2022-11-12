#pragma once

#include <iterator>
#include <list>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <algorithm>


namespace caches {  
template <typename T, typename KeyT = int> struct cache_t{  
    struct Page{
        KeyT id;
        int freq = 1;
    };  
    std::size_t sz_;
    std::list<Page> cache_;
    using ListIt = typename std::list<Page>::iterator;
    std::unordered_map<KeyT, ListIt> hash_; 

    cache_t(size_t sz) : sz_(sz) {};
    bool full() const { return (cache_.size() == sz_); }
    bool empty() const { return (cache_.size() == 0); }
    
    template <typename F>
    bool lookup_update(KeyT k, F slow_get_page) {
        auto hit = hash_.find(k);
        if(hit == hash_.end()){            
            if(full()){                        
                delete_lfu();
                 
            }      
            push_new_elem(k, slow_get_page);
            return false;         
        }
               
        else{
            (hit->second)->freq += 1;                                  
            save_freq_sort();
            return true;
        }     
    } 
    
    void delete_lfu(){
        auto i = cache_.begin();
        auto kick_it = hash_.find(i->id);  
        hash_.erase(kick_it);
        cache_.pop_front(); 
    }

    void push_new_elem(KeyT k, KeyT slow_get_page){
        cache_.push_front({slow_get_page, 1});
        hash_[k] = cache_.begin();
    }

    // save freq sort in cache_
    // for simple delete from it
    // complexity O(N)
    void save_freq_sort(){
        for(auto i = std::next(cache_.begin()); i != cache_.end(); i++){
            if(i->freq < std::prev(i)->freq){
                hash_[i->id] = std::prev(i);
                hash_[std::prev(i)->id] = i;
                std::iter_swap(i, std::prev(i));
            }       
        }
    }

    };
}


