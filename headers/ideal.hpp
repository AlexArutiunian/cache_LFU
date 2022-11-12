#pragma once

#include <iterator>
#include <list>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <algorithm>



namespace ideal_caches {  
template <typename T, typename KeyT = int> struct ideal_cache_{  
    struct Page{
        KeyT id; 
        size_t loc = 0;
    };  
    std::size_t sz_;
    std::list<Page> cache_;
    using ListIt = typename std::list<Page>::iterator;
    std::unordered_map<KeyT, ListIt> hash_; 

    ideal_cache_(size_t sz) : sz_(sz) {};
    bool full() const { return (cache_.size() == sz_); }

    using vect_itr = typename std::vector<T>::iterator;

    // main idea : sort cache
    // by leate met
    // delete from front if 
    // element met eailer
    // than front element in cache

    template <typename F>
    bool lookup_update(const std::vector<T>& all_keys, KeyT k, F slow_get_page, int num_iteration) {
        auto hit = hash_.find(k);
        size_t pos = next_pos(all_keys, num_iteration, k);
        if(hit == hash_.end()){      
            if(full()){  
                if(pos < cache_.begin()->loc){
                    save_sort();                    
                    delete_lfu();  
                } 
                else return false;
            } 
            if(pos != all_keys.size() + 1) push_new_elem(k, slow_get_page, pos);
            save_sort();
            return false; 
                  
        }
               
        else{                                  
            
            (hit->second)->loc = pos;
            save_sort();
            lookup_future(all_keys, num_iteration, k);
            delete_if(pos, k, all_keys);
            return true;
        }     
    } 
    
    void delete_if(size_t pos, KeyT k, const std::vector<T>& all_keys){
        if(pos == all_keys.size() + 1){
            auto i = cache_.begin();
            for(i; i != cache_.end(); ++i){
                if(k = i->id) break; 
            } 
            auto kick_it = hash_.find(i->id);
            hash_.erase(kick_it);
            cache_.erase(i);
            
        }
    }

    void delete_lfu(){
        auto i = cache_.begin();
        auto kick_it = hash_.find(i->id);  
        hash_.erase(kick_it);
        cache_.pop_front(); 
    }

    void push_new_elem(KeyT k, KeyT slow_get_page, size_t pos){
        cache_.push_front({slow_get_page, pos});
        hash_[k] = cache_.begin();
    }

    // save freq sort in cache_
    // for simple delete from it
    // complexity O(N)

    void save_sort(){
        for(auto i = std::next(cache_.begin()); i != cache_.end(); ++i){
            if(i->loc > std::prev(i)->loc){
                hash_[i->id] = std::prev(i);
                hash_[std::prev(i)->id] = i;
                std::iter_swap(i, std::prev(i));
            }       
        }
    }

    size_t next_pos(const std::vector<T>& data, int num_itrtion, KeyT k){
        size_t m = static_cast<size_t>(num_itrtion);
        std::vector<T> data_slice(data.size());
        std::copy(data.begin() + m, data.end(), data_slice.begin());
        auto i = std::find(data_slice.begin(), std::prev(data_slice.end()), k);
        size_t res = m + std::distance(data_slice.begin(), i);
        return (res <= data.size()) ? res : data.size() + 1;
    }
    
    void lookup_future(const std::vector<T>& data, int num_itrtion, KeyT k){
        for(auto i : cache_){
            i.loc = next_pos(data, num_itrtion, i.id);
            save_sort();
        }
    }

    void dump(int n) const{ 
        std::cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
        std::cout << n << ")";
        for(auto i = std::prev(cache_.end()); i != std::prev(cache_.begin()); --i){
            std::cout << "\nKEY " << i->id << " " << " NEXT MET " << i->loc << std::endl;
        }
        std::cout << std::endl;  
    }

    };
}// namespace ideal_caches


