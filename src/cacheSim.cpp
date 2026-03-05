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
    list<int> usageOrder;
    unordered_map<int, list<int>::iterator> cachePosition;
    int misses = 0;

    for(int item : requests)
    {
        auto found = cachePosition.find(item);
        if(found != cachePosition.end())
        {
            usageOrder.erase(found->second);
            usageOrder.push_front(item);
            found->second = usageOrder.begin();
        }
        else
        {
            misses++;

            if(static_cast<int>(cachePosition.size()) >= k)
            {
                int toEvict = usageOrder.back();
                usageOrder.pop_back();
                cachePosition.erase(toEvict);
            }

            usageOrder.push_front(item);
            cachePosition[item] = usageOrder.begin();
        }
    }

    return misses;
}

int optff(int k, vector<int>& requests)
{

}

pair<int, vector<int>> parseInput(const string& filename)
{
    std::ifstream file(filename);
    if(!file.is_open())
    {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    int k;
    int m;

    if(!(file >> k >> m))
    {
        throw std::runtime_error("Failed to read k and m from input.");
    }
    if(k < 1)
    {
        throw std::runtime_error("Cache capacity k must be >= 1.");
    }
    if(m < 0)
    {
        throw std::runtime_error("Number of requests m must be >= 0.");
    }

    vector<int> requests(m);
    for (int i = 0; i < m; i++)
    {
        if(!(file >> requests[i]))
        {
            throw std::runtime_error("Expected " + std::to_string(m) + " requests, found only " +
                std::to_string(i) + ".");
        }
    }
    return {k, requests};
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    pair<int, vector<int>> input;
    try
    {
        input = parseInput(argv[1]);
    }
    catch (const std::exception& e)
    {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    int fifoMisses = FIFO(input.first, input.second);
    int lruMisses = LRU(input.first, input.second);
    int optffMisses = optff(input.first, input.second);

    cout << "FIFO  : " << fifoMisses << "\n";
    cout << "LRU   : " << lruMisses << "\n";
    cout << "OPTFF : " << optffMisses << "\n";

    return 0;
}