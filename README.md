# Cache: Least frequency used
In this repository is 3 types of time-complexity for LFU cache. In the directory "headers" 3 header-files - it is 3 types.

## 1) O(1) 
We can read about this method at [the link](https://arpitbhayani.me/blogs/lfu).

The main idea of constant time method is in the picture:
![logo](https://user-images.githubusercontent.com/4745789/90469593-e08c5c00-e136-11ea-995b-e4590981dd89.png)

## 2) O(N)

The main idea here is that we can save freq-sort and use struct.
When a hit occurs, element of cache which has max freq move in the back of list cache.
```C++
struct page{
    KeyT id;
    int freq = 1;
};    
```
```C++
void save_freq_sort(){
        for(auto i = std::next(cache_.begin()); i != cache_.end(); i++){
            if(i->freq < std::prev(i)->freq){
                hash_[i->id] = std::prev(i);
                hash_[std::prev(i)->id] = i;
                std::iter_swap(i, std::prev(i));
            }       
        }
    }
```

## 3) O(N*LOG(N))

In this way i used metod of stl: sort.
The main idea: use struct and metod sort for list stl.

```C++
struct page{
    KeyT id;
    int freq = 1;
    
    bool operator<(const page & rhs)
    {
        return freq < rhs.freq;
    }
}; 
std::list<page> cache_;   
```
```C++
cache_.sort();
```
Exactly sort has complexity-time O(NLogN).

## How to build with CMake?

### Windows
in dir with cache_LFU
in cmd 
```
cmake -G "Unix Makefiles"
cmake --build .
```
After it you can start the program cache_LFU
just input in cmd
```
lfu
```
### Linux
in dir with cache_LFU
```
mkdir build
cd build
cmake ..
cmake --build .

```
## About tests
I made random number generation for capacity of cache = 3, range and numder of keys = 10.
This test is only for key type of int.
