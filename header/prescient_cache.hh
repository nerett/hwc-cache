#pragma once

#include <iostream>
#include <list>
#include <unordered_map>

const size_t DEFAULT_CAPACITY = 20;

template <typename PageT, typename KeyT = int>
class PrescientCache
{
    struct CacheElem
    {
        PageT page_;
        KeyT key_;

        size_t freq_ = 0;

        CacheElem( KeyT key, PageT page = {} ): page_( page ), key_( key ) {};
    };

    private:

        size_t capacity_;

        std::list <PrescientCache<PageT, KeyT>::CacheElem> data_;
        using ListIt = typename std::list<PrescientCache<PageT, KeyT>::CacheElem>::iterator;
        std::unordered_map <KeyT, ListIt> datatable_;

    public:

        explicit PrescientCache( size_t capacity = DEFAULT_CAPACITY ): capacity_( capacity ) {};
}
