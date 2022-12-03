#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <unordered_map>
#include <deque>
#include <list>
#include <map>


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
        bool operator< (const elem& rhs) const {return rhs.loc > loc; }
    };
    std::deque<elem> unique_key_;
    using ItUnKeys = typename std::deque<elem>::iterator;
    std::unordered_map<T, ItUnKeys> hash_ftr;

    std::map<size_t, elem> cache_;
    using MapIt = typename std::map<size_t, elem>::iterator;
    std::unordered_map<T, MapIt> hash_;
    
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
               
                auto kick_candidate = std::prev(cache_.end());
                if(itr->second->met.front() < kick_candidate->second.loc){                   
                    delete_(kick_candidate);  
                } 
                else return false;
            }   
            
            auto in = cache_.insert({*(itr->second->met.begin()), {k, *(itr->second->met.begin()), {}}});
            hash_[k] = in.first;
            return false;

        }
        else{
            auto itr = hash_ftr.find(k);
            upd_cache(k, num_itrtion);  
            
            if(*itr->second->met.begin() == 0){
                erase_(k);
                return true;
            }   
            delete_(hit->second);
            auto in = cache_.insert({*(itr->second->met.begin()), {k, *(itr->second->met.begin()), {}}});
            hash_[k] = in.first;
            return true;
        }

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

    void delete_(MapIt it){
        auto kick_it = hash_.find(it->second.key);  
        hash_.erase(kick_it);
        cache_.erase(it); 
    }

    void dump_c() const {
        std::cout << "\nKEY; NEXT MET\n";
        for(auto i : cache_){
            std::cout << i.second.key << "    ";
            std::cout << i.second.loc << "\n";
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
