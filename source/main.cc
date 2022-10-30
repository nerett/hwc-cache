#include "../header/cache.hh"

int slow_get_page( long long key )
{
    std::cout << "slow_get_page key = " << key << "\n";
    return 3;
}

int main()
{
    Cache <int, long long> test_cache( 3 );

    test_cache.lookup_update( 100, slow_get_page ); //100
    test_cache.lookup_update( 200, slow_get_page ); //200
    test_cache.lookup_update( 300, slow_get_page ); //300

    test_cache.lookup_update( 100, slow_get_page ); //
    test_cache.lookup_update( 200, slow_get_page ); //
    test_cache.lookup_update( 400, slow_get_page ); //400 (300)
    test_cache.lookup_update( 300, slow_get_page ); //300 (400)
    test_cache.lookup_update( 400, slow_get_page ); //400 (300)
    test_cache.lookup_update( 300, slow_get_page ); //300 (400)
    test_cache.lookup_update( 300, slow_get_page ); //
    test_cache.lookup_update( 400, slow_get_page ); //400 (100/200/300)

    Cache <int> test2_cache();
    return 0;
}