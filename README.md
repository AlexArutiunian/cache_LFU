# Cache: Least frequency used
In this repository is 3 types of time-complexity for LFU cache. In the directory "headers" 3 header-files - it is 3 types; there are also tests and model of ideal cache (when we know all keys from future).

Input: number of requests (keys) and these requests. <br>
Output: number of hits (requests that push in cache but yet is in cache) 
Example:
```bash
6 1 2 1 2 3 4
```
```bash
2
```

## 1) O(1) 
We can read about this method at [the link](https://arpitbhayani.me/blogs/lfu).

The main idea of constant time method is in the picture:
![logo](https://user-images.githubusercontent.com/4745789/90469593-e08c5c00-e136-11ea-995b-e4590981dd89.png)

## 2) O(N)

The main idea here is that we can save freq-sort and use struct page.
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

I used metod of stl: sort in this way.
The main idea: use struct page and metod sort for list stl.

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
After that you can start the program cache_LFU
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
This test is only for key type of int, but code fits for stl types.

| num of test | list of keys | res for lfu1 | res for ideal_cache |
| ---- | ---- | ---- | ---- |
| 1 | 3 6 7 5 3 5 6 2 9 1 | 1 | 3 |
| 2 | 2 7 0 9 3 6 0 6 2 6 | 2 | 4 |
| 3 | 1 8 7 9 2 0 2 3 7 5 | 1 | 2 |
| 4 | 9 2 2 8 9 7 3 6 1 2 | 3 | 3 |
| 5 | 9 3 1 9 4 7 8 4 5 0 | 1 | 2 |
| 6 | 3 6 1 0 6 3 2 0 6 1 | 2 | 3 |
| 7 | 5 5 4 7 6 5 6 9 3 7 | 3 | 4 |
| 8 | 4 5 2 5 4 7 4 4 3 0 | 4 | 4 |
| 9 | 7 8 6 8 8 4 3 1 4 9 | 2 | 3 |
| 10 | 2 0 6 8 9 2 6 6 4 9 | 1 | 3 |


### You can test to compare the result for cache_lfu and cache_ideal.

There is 'test_lfu_vs_ideal.cpp' in the directory 'tests'. You can look result of this test in the 
directory 'tests' in the file 'compare_lfu_vs_ideal.txt'. 
