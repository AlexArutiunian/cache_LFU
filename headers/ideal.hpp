#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <unordered_map>
#include <deque>
#include <list>


namespace ideal_caches{
template <typename T> struct ideal_cache_{


    size_t cp = 0;
    size_t sz = 0;
    ideal_cache_(const std::vector<T>& data, size_t cp_) : cp{cp_} {
        for(auto i = data.begin(); i != data.end(); ++i){
            auto search_it = hash_ftr.find(*i);
            if(search_it == hash_ftr.end()){
                unique_key_.push_front({{}, static_cast<size_t>(*i)});
                unique_key_.front().met.push_back(std::distance(data.begin(), i) + 1);
                hash_ftr[*i] = unique_key_.begin();               
            }
            else{
                search_it->second->met.push_back(std::distance(data.begin(), i) + 1);
            
            }
        }
    }

    struct elem{
        T key;
        size_t loc;
        std::deque<size_t> met;
    };
    std::deque<elem> unique_key_;
    using ItUnKeys = typename std::deque<elem>::iterator;
    std::unordered_map<T, ItUnKeys> hash_ftr;

    std::list<elem> cache_;
    using ListIt = typename std::list<elem>::iterator;
    std::unordered_map<T, ListIt> hash_;
    
    bool full() const { return (cache_.size() == cp); }

    template <typename F>
    bool lookup_update(T k, F slow_get_page, const int& num_itrtion){  


        auto hit = hash_.find(k);
        if(hit == hash_.end()){
            upd_cache(k, num_itrtion);
            auto itr = hash_ftr.find(k);
            if(*itr->second->met.begin() == 0){
                return false;
            }
            if(full()){
                auto kick_candidate = find_max();
                if(itr->second->met.front() < kick_candidate->loc){                   
                    delete_(kick_candidate);  
                } 
                else return false;
            }   
            
            cache_.push_front({k, *(itr->second->met.begin()), {}});
            hash_[k] = cache_.begin();
            return false;

        }
        else{
            auto itr = hash_ftr.find(k);
            upd_cache(k, num_itrtion);  
           
            if(*itr->second->met.begin() == 0){
                erase_(k);
                return true;
            }   
            hit->second->loc = *itr->second->met.begin();       
            return true;
        }

    }

    const ListIt find_max(){
        size_t max = cache_.begin()->loc;
        auto kick_candidate = cache_.begin();
        for(auto i = cache_.begin(); i != cache_.end(); ++i){
            if(i->loc > max){
                max = i->loc;
                kick_candidate = i;
            }
        } 
        return kick_candidate;
    }

    void upd_cache(const T&k, const int& num_itrtion){
        auto itr = hash_ftr.find(k);
        while(num_itrtion >= *itr->second->met.begin() - 1){
            if(itr->second->met.size() == 1){
                itr->second->met.pop_front();
                itr->second->met.push_back(0);
                break;
            }
            else itr->second->met.pop_front();
        } 
    }

    void erase_(const T& k){
        auto kick_it = hash_.find(k);
        cache_.erase(kick_it->second);
        hash_.erase(kick_it);
    }

    void delete_(ListIt it){
        auto kick_it = hash_.find(it->key);  
        hash_.erase(kick_it);
        cache_.erase(it); 
    }

    void dump_c() const {
        std::cout << "\nKEY; NEXT MET\n";
        for(auto i : cache_){
            std::cout << i.key << "    ";
            std::cout << i.loc << "\n";
        }
        std::cout << "\n- - - - - - - - - - ";
    }

    void dump_ftr() const {
        std::cout << "\nKEY;   MET\n";
        for(auto i : hash_ftr){
            std::cout << i.first << "   ";
            std::cout << *i.second->met.begin() << "\n";
        }
        std::cout << "\n- - - - - - - - - - ";
    }

};
} // namespace
