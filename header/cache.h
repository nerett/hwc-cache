#ifndef CACHE_H_INCLUDED
#define CACHE_H_INCLUDED


#include <iostream>
#include <list>
#include <unordered_map>


template <typename PageT>
class CacheElem
{
    //friend Cache;

    private:

        PageT page_;
        size_t freq_ = 0;

    public:

        CacheElem( PageT page );
        CacheElem();
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


        bool lookup_update( KeyT key, PageT( &slow_get_page )( KeyT key ) );
        bool full() const;
};


#endif //CACHE_H_INCLUDED