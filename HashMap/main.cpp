#include <algorithm>
#include <numeric>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>

#include "chaining_hash.hpp"
#include "open_addressing_hash.hpp"


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

    for (int i = 0; i < 1000000; i += 10000)
    {
        os << i << ",";

        std::vector<std::pair<int, double>> dataset;

        // データセットを作成
        {
            dataset =
            {
                // ハッシュを衝突させる
                { 11, 110.0 },
                //{ 11,  90.0 },
                //{ 11, 113.0 },
                //{ 11, 115.0 },
                //{ 11, 120.0 },
                //{ 11, 130.0 },
                //{ 11, 140.0 },
                //{ 11, 150.0 },
                //{ 11, 160.0 },
                //{ 11, 170.0 },
            };

            for (int i = 0; i < 10000 - dataset.size(); ++i)
            {
                dataset.push_back({ i, i * 1.1 });
            }
        }

        // ハッシュマップ / チェイン法
        {
            chaining_hash<int, double> hash_table(dataset);

            print_search_result(os, [&]()
                {
                    auto finded = hash_table.search(11, 110.0);
                });
        }


        // ハッシュマップ / オープンアドレス法
        {
            open_addressing_hash<int, double> hash_table(dataset);

            print_search_result(os, [&]()
                {
                    auto finded = hash_table.search(11, 110.0);
                });
        }

        os << std::endl;

    }
}