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
            // если кэш заполнен
            // удалим элемент из первого подсписка
            // то есть из первого списка ключей
            // последний ключ
                hash_.erase(cache_.front().list_keys.back().key);
                cache_.front().list_keys.pop_back();
            // если после удаления 
            // первый подсписок стал пустым
            // удалим его
                if(cache_.front().list_keys.size() == 0)
                    cache_.pop_front();
                sz_--;        
            }

            if(empty()){
            // если в кэше нет элементов
            // просто создаем пустой узел вначале
            // в список которого далее
            // поместим список ключей
                cache_.push_front({{}, 1}); 
            }
            
            // если нет узла, в который
            // нужно поместить список для
            // хранения нового элемента
            // то создаем такой узел вначале
            if(cache_.front().freq != 1)
                cache_.push_front({{}, 1});
            
            // помещение переданного ключа в список ключей
            // в первом узле, т.к. нужно сохранение порядка по возрастанию
            // чтобы удалять из начала кэша
 
           // cache_.front().list_keys.insert(cache_.front().list_keys.begin(), {/*slow_get_page(k)*/k, k, cache_.begin()});
            cache_.front().list_keys.push_front({k, k, cache_.begin()});
            hash_[k] = cache_.front().list_keys.begin();
            sz_++;

            return false;
        }

        splice_(hit->second);
        return true;
    }

    void splice_(ListKeysIt it){
        auto & fr = it->itr_freq_node->freq;
        auto & itr_freq_node = it->itr_freq_node;
        
        // если найденный по ключу элемент с самой большой частотой
        // то есть он находится в конце кэша
        // тогда создаем с конца кэша узел со значением += 1
        
        if(itr_freq_node == std::prev(cache_.end())){    
            cache_.push_back({{}, fr + 1});
        } 
        
        // если следующий узел не подходит по параметру частотности для
        // перемещения в него найденного ключа
        // то создаем новый узел с подходящей частотностью
        else if(std::next(itr_freq_node)->freq != fr + 1)
            cache_.insert(std::next(itr_freq_node), {{}, fr + 1});



        // помещаем в узел наш элемент
        auto it_next_freq_node = std::next(itr_freq_node);
        it_next_freq_node->list_keys.splice(it_next_freq_node->list_keys.end(), itr_freq_node->list_keys, it); 
        // сплайс работает так : аргументы (итератор куда, имя списка откуда, итератор откуда)   
        
        // если после перемещения подсписок стал пустым
        // удалим его
        if(itr_freq_node->list_keys.size() == 0) cache_.erase(itr_freq_node);
        // теперь итератор перемещаемого элемента должен указывать на 
        // новый частотный узел, поэтому изменим указатель 
        itr_freq_node = it_next_freq_node;
    }
      
    };

}// namespace caches


