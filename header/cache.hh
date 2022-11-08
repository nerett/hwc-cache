#pragma once

#include <iostream>
#include <list>
#include <unordered_map>

const size_t DEFAULT_CAPACITY = 20;

template <typename PageT, typename KeyT = int>
class Cache
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

        std::list <Cache<PageT, KeyT>::CacheElem> data_;
        using ListIt = typename std::list<Cache<PageT, KeyT>::CacheElem>::iterator;
        std::unordered_map <KeyT, ListIt> datatable_;

    public:

        explicit Cache( size_t capacity = DEFAULT_CAPACITY ): capacity_( capacity ) {};

        template <typename F>
        bool lookup_update( KeyT key, F slow_get_page ); //PageT( &slow_get_page )( KeyT key )

        bool full() const { return data_.size() >= capacity_; };
        ListIt lfu()
        {
            size_t least_freq = data_.begin()->freq_;
            ListIt lf_elem = data_.begin(); // = {}; TO FIGURE OUT
            for( ListIt i = data_.begin(); i != data_.end(); ++i )
            {
                if( i->freq_ < least_freq )
                {
                    least_freq = i->freq_;
                    lf_elem = i;
                }
            }

            return lf_elem;
        }
};


/*--------------------------FUNCTION-----------------------------------------*/
template <typename PageT, typename KeyT>
template <typename F>
bool Cache<PageT, KeyT>::lookup_update( KeyT key, F slow_get_page )
{
    auto hit = datatable_.find( key );

    if( hit == datatable_.end() ) //page is not found
    {
        std::cerr << "size = " << data_.size() << " " << "capacity = " << capacity_ << "\n";
        if( full() )
        {
            std::cerr << "full!\n";
            std::cerr << "lfu()->key_ = " << lfu()->key_ << "\n";
        
            datatable_.erase( lfu()->key_ );
            data_.erase( lfu() );
        }

        data_.push_front( Cache<PageT, KeyT>::CacheElem( key, slow_get_page( key ) ) );
        datatable_[key] = data_.begin();

        return false;
    }

    datatable_[key]->freq_++;
    return true;
}


/*--------------------------FUNCTION-----------------------------------------*/
/*
template <typename PageT, typename KeyT>
//template <typename F>
ListIt Cache<PageT, KeyT>::lfu() const
{
    size_t least_freq = data_.begin()->freq_;
    ListIt lf_elem = {};
    for( ListIt i = data_.begin(); i != data_.end(); ++i )
    {
        if( i->freq_ < least_freq )
        {
            least_freq = i->freq_;
            lf_elem = i;
       }
    }

    return lf_elem;
}
*/

