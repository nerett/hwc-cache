#ifndef CACHE_H_INCLUDED
#define CACHE_H_INCLUDED


#include <iostream>
#include <list>
#include <unordered_map>


template <typename PageT>
class CacheElem
{
    //friend Cache;

    public: //FIXME

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

        size_t size_;

        std::list <CacheElem<PageT>> data_;
        using ListIt = typename std::list<PageT>::iterator;
        //std::unordered_map <CacheElem<PageT>, KeyT> datatable_;
        std::unordered_map <KeyT, ListIt> datatable_;

    public:

        explicit Cache( size_t size );
        ~Cache();

        template <typename F>
        bool lookup_update( KeyT key, F slow_get_page ); //PageT( &slow_get_page )( KeyT key )
        bool full() const;
};


/*--------------------------FUNCTION-----------------------------------------*/
template <typename PageT>
CacheElem<PageT>::CacheElem( PageT page ):
    page_( page )
{

}


/*--------------------------FUNCTION-----------------------------------------*/
template <typename PageT>
CacheElem<PageT>::CacheElem():
    page_()
{

}


/*--------------------------FUNCTION-----------------------------------------*/
template <typename PageT>
CacheElem<PageT>::~CacheElem()
{

}


/*--------------------------FUNCTION-----------------------------------------*/
template <typename PageT, typename KeyT>
Cache<PageT, KeyT>::Cache( size_t size ):
    size_( size ),
    data_( size ),
    datatable_()
{

}


/*--------------------------FUNCTION-----------------------------------------*/
template <typename PageT, typename KeyT>
Cache<PageT, KeyT>::~Cache()
{

}


/*--------------------------FUNCTION-----------------------------------------*/
template <typename PageT, typename KeyT>
template <typename F>
bool Cache<PageT, KeyT>::lookup_update( KeyT key, F slow_get_page )
{
    auto hit = datatable_.find( key );

    if( hit == datatable_.end() ) //page is not found
    {
        if( full() )
        {
            datatable_.erase( data_.back().id ); //FIXME
            data_.pop_back(); //FIXME
        }

        data_.push_front( slow_get_page( key ) );
        datatable_[key] = data_.begin();

        return false;
    }

    /*
    auto eltit = hit->second;
    if( eltit != data_.begin() )
    data_.splice( data_.begin(), data_, eltit, std::next( eltit ) );
    */

    //datatable_[key].freq_++;
    ListIt test = data_.begin(); //test
    ListIt iter = datatable_[key];
    iter.freq_++;

    return true;
}


/*--------------------------FUNCTION-----------------------------------------*/
template <typename PageT, typename KeyT> //не знаю, можно ли вынести реализаию этой функции в cache.cc
bool Cache<PageT, KeyT>::full() const
{
    if( data_.size() >= size_ )
    {
        return true;
    }

    return false;
}


#endif //CACHE_H_INCLUDED