#include "../header/cache.h"

int slow_get_page( long long key )
{
    cout << "slow_get_page key = " << key << "\n";
    return 3;
}

int main()
{
    Cache <int, long long> test_cache( 100 );

    test_cache.lookup_update( 134, slow_get_page );

    Cache <int> test2_cache();
    return 0;
}