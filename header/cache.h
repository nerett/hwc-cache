#ifndef CACHE_H_INCLUDED
#define CACHE_H_INCLUDED


#include <iostream>


template <typename PageT>
class CacheElem
{
    friend Cache;

    private:

        PageT page_;
        size_t freq_;

    public:

        explicit CacheElem( PageT page );
        explicit CacheElem();
        ~CacheElem();

};

template <typename PageT, typename KeyT = int>
class Cache
{
    private:

        std::list <CacheElem<PageT>> data_;
        std::unordered_map <CacheElem<PageT>, KeyT> datatable_;

        size_t size_;

    public:

        explicit Cache( size_t size );
        ~Cache();

        bool lookup_update( KeyT key, slow_get_page );
};


#endif //CACHE_H_INCLUDED