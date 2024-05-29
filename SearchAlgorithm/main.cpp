#include <algorithm>
#include <numeric>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <memory>
#include <stack>

#include "linear_search.hpp"
#include "linear_sentinel_search.hpp"
#include "binary_search.hpp"


template <typename F>
void print_search_result(std::ostream& os, F f)
{
    const auto start = std::chrono::system_clock::now();

    const int n = 10;

    for (int i = 0; i < n; ++i)
    {
        f();
    }

    const auto finish = std::chrono::system_clock::now();

    const auto processing_time_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start) / n;

    os << processing_time_ns.count() << ",";
}


int main()
{

    std::ofstream ofs("search_algorithm.csv");
    std::ostream& os = ofs;
    if (!ofs)
    {
        std::cerr << "ファイルを開けませんでした" << std::endl;
        return 1;
    }

    //std::ostream& os = std::cout;

    for (int i = 0; i < 1000; i += 10)
    {
        os << i << ",";

        std::vector<int> dataset(i);
        std::iota(dataset.begin(), dataset.end(), 0);
        std::random_shuffle(dataset.begin(), dataset.end());

        const int search_value = 0;

        // 線形探索
        {
            print_search_result(os, [&] {
                auto finded = linear_search(std::cbegin(dataset), std::cbegin(dataset) + i, search_value);
                });
        }


        // 線形探索 / 兵番法
        {
            // 終端が必ず見つかる前提とする
            std::vector<int> terminated_dataset{ std::cbegin(dataset), std::cbegin(dataset) + i };
            terminated_dataset.push_back(search_value);

            print_search_result(os, [&] {
                auto finded = linear_sentinel_search(std::cbegin(terminated_dataset), search_value);
                });
        }


        // 二分探索
        {
            // ソート済みのデータセットを前提とする
            std::vector<int> sorted_dataset{ std::cbegin(dataset), std::cbegin(dataset) + i };
            std::sort(std::begin(sorted_dataset), std::end(sorted_dataset));

            print_search_result(os, [&] {
                auto finded = binary_search(std::cbegin(sorted_dataset), std::cend(sorted_dataset), search_value);
                });
        }

        os << std::endl;

    }

}

