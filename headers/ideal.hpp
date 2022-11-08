#pragma once

#include <iostream>
#include <unordered_map>
#include <iterator>
#include <list>
#include <vector>

namespace ideal_caches {
template <typename T, typename KeyT = int> struct ideal_cache_{
    
    struct freq_key{
        int key;
        int freq = 0;
        const bool operator<(const freq_key & rhs) { return freq < rhs.freq; } 
    };
    size_t sz_;
    ideal_cache_(std::size_t cp): sz_(cp) {};

    std::list<freq_key> cache_;
    using ListIt = typename std::list<freq_key>::iterator;
    std::unordered_map<KeyT, ListIt> hash_;
    bool full() const { return (cache_.size() == sz_); } 
    
    // now we know future
    // then we can look at the whole freq 
    // for each element
    // which hits in cache_

    template <typename F>
    bool lookup_update(const std::vector<T> & all_keys, KeyT k, F slow_get_page){
        auto hit = hash_.find(k);
        if(hit == hash_.end()){
            if(full()){
                if(more_for_freq(k, all_keys)){
                    delete_();
                }
                else return false;
            }
            cache_.push_front({k, freq_(all_keys, slow_get_page)});
            hash_[k] = cache_.begin();
            return false;
        }
        else{
            return true;
        }
    }
    
    int freq_(const std::vector<T> & all_keys, KeyT k){
        int freq = 0;
        for(auto i = all_keys.begin(); i != all_keys.end(); ++i){
            if(*i == k) freq++;
        }
        return freq;
    }

    void delete_(){
        cache_.sort();
        auto i = cache_.begin();
        auto kick_it = hash_.find(i->key);  
        hash_.erase(kick_it);
        cache_.pop_front();
    }

    void dump() const{
        for(auto i = hash_.begin(); i != hash_.end(); ++i){
            std::cout << i->first << " ";
        }
        std::cout << '\n';
    }
    bool more_for_freq(KeyT k, const std::vector<T> & all_keys){
        auto& least_in_cache = cache_.begin()->freq;
        return(least_in_cache <= freq_(all_keys, k));
    }
};

} // namespace ideal_caches