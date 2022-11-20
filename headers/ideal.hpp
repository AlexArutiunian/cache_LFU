#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <unordered_map>
#include <deque>
#include <list>


namespace ideal_caches{
template <typename T> struct ideal_cache_{


    size_t data_size;
    size_t cp;
    size_t sz;
    ideal_cache_(const std::vector<T>& data, size_t cp_) : data_size{data.size()}, cp{cp_}, sz(0) {
        for(auto i = data.begin(); i != data.end(); ++i){
            auto search_it = hash_ftr.find(*i);
            if(search_it == hash_ftr.end()){
                unique_key_.push_front({{}, *i});
                unique_key_.front().met.push_back(std::distance(data.begin(), i));
                hash_ftr[*i] = unique_key_.begin();
                
            }
            else{
                search_it->second->met.push_back(std::distance(data.begin(), i));
            
            }
        }
    }

    
    struct met_key{
        std::deque<size_t> met;  
        T key;  
        bool const operator== (const met_key& rhs) {return key == rhs.key;}
        bool const operator== (const int rhs) {return key == rhs;}
        
    };
    
    std::deque<met_key> unique_key_;
    using ItUnKeys = typename std::deque<met_key>::iterator;
    std::unordered_map<T, ItUnKeys> hash_ftr;

    struct elem{
        T key;
        size_t loc;
        bool const operator< (const elem& rhs) { return loc > rhs.loc; }
    };

    std::list<elem> cache_;
    using ListIt = typename std::list<elem>::iterator;
    std::unordered_map<T, ListIt> hash_;

    void upd_cache(){
        for(auto i = cache_.begin(); i != cache_.end(); ++i){
            auto itr = hash_ftr.find(i->key);
            if(*itr->second->met.begin() == data_size + 1){
                auto kick_it = hash_.find(i->key);
                hash_.erase(kick_it);
                cache_.erase(i);
                return;
            }
            i->loc = *itr->second->met.begin();
        }
    }

    void upd_future(T k, const int& num_itrtion){ 
        for(auto i : hash_ftr){
            if(*i.second->met.begin() <=  static_cast<size_t>(num_itrtion)){
                if(i.second->met.size() == 1){
                    i.second->met.push_back(data_size + 1);
                } 
                
                i.second->met.pop_front();
            }
             
        }
    }
    
    bool full() const { return (cache_.size() == cp); }

    template <typename F>
    bool lookup_update(T k, F slow_get_page, int num_itrtion){
        upd_cache();
        auto& ref_itrtion = num_itrtion;
        upd_future(k, ref_itrtion);
        auto hit = hash_.find(k);
        if(hit == hash_.end()){
            auto itr = hash_ftr.find(k);
            if(*itr->second->met.begin() == data_size + 1){
                return false;
            }
            if(full()){
                cache_.sort();
                
                if(itr->second->met.front() < cache_.begin()->loc){                   
                    delete_lfu();  
                } 
                else return false;
            }   
            
            cache_.push_front({k, *(itr->second->met.begin())});
            hash_[k] = cache_.begin();
            return false;

        }
        else{
                         
            return true;
        }

    }

    void delete_lfu(){
        auto i = cache_.begin();
        auto kick_it = hash_.find(i->key);  
        hash_.erase(kick_it);
        cache_.pop_front(); 
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
