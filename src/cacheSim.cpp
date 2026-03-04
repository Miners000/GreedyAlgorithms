#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <queue>
#include <limits>
#include <stdexcept>
#include <string>
using namespace std;

int FIFO(int k, vector<int>& requests)
{
    unordered_set<int> cache;
    queue<int> order;
    int misses = 0;

    for(int item : requests)
    {
        if(cache.count(item))
        {
            // Hit — nothing to do
        }
        else
        {
            misses++;
            if(static_cast<int>(cache.size()) >= k)
            {
                int toEvict = order.front();
                order.pop();
                cache.erase(toEvict);
            }

            cache.insert(item);
            order.push(item);
        }
    }
    return misses;
}

int LRU(int k, vector<int>& requests)
{

}

int optff(int k, vector<int>& requests)
{

}

int main(int argc, char* argv[])
{
    return 0;
}