#include "../header/cache.hh"
#include <vector>

int slow_get_page( long long key )
{
    std::cerr << "slow_get_page key = " << key << "\n";
    return 231;
}

int main()
{
    size_t N_keys = 0, cachesize = 0;
    std::cin >> cachesize >> N_keys;

    std::vector<long long> element_keys = {};
    for( size_t i = 0; i < N_keys; i++ )
    {
        long long buffer = 0;
        std::cin >> buffer;
        element_keys.push_back( buffer );
    }

    Cache <char, long long> cache( cachesize );
    size_t N_hits = 0;
    for( size_t i = 0; i < N_keys; i++ ) //FIXME
    {
        bool buffer = cache.lookup_update( element_keys[i], slow_get_page );
        N_hits += buffer;

        std::cerr << "Lookup result is " << buffer << " for element # " << element_keys[i] << std::endl;
    }

    std::cout << N_hits << std::endl;
    return 0;
}