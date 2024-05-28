#include <algorithm>
#include <numeric>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <memory>
#include <stack>

#include "linear_search.hpp"
#include "binary_search.hpp"



/**
 *   @brief 二分岐探索 / 幅優先探索
 */
template <typename InputIterator>
InputIterator breadth_first_search(InputIterator begin, InputIterator end, int value)
{

	return end;
}


/**
 *   @brief 二分岐探索 / 深さ優先探索 / 先行順
 */
template <typename InputIterator>
InputIterator depth_first_preorder_search(InputIterator begin, InputIterator end, int value)
{
	std::stack<InputIterator> stack;
	stack.push(begin);

	while (!stack.empty())
	{
		auto it = stack.top();
		stack.pop();

		if (*it == value)
		{
			return it;  // 発見
		}

		if (it + 1 != end)
		{
			stack.push(it + 1);  // 右側をスタック
		}

		if (it != end)
		{
			stack.push(it);  // 左側をスタック
		}
	}

	return end;
}

/**
 *   @brief 二分岐探索 / 深さ優先探索 / 中間順
 */
template <typename InputIterator>
InputIterator depth_first_inorder_search(InputIterator begin, InputIterator end, int value);

/**
 *   @brief 二分岐探索 / 深さ優先探索 / 後行順
 */
template <typename InputIterator>
InputIterator depth_first_postorder_search(InputIterator begin, InputIterator end, int value);



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

	for (int i = 0; i < 100000; i += 1000)
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


		//// 線形探索 / 兵番法
		//{
		//	// 終端が必ず見つかる前提とする
		//	std::vector<int> terminated_dataset{ std::cbegin(dataset), std::cbegin(dataset) + i };
		//	terminated_dataset.push_back(search_value);

		//	print_search_result(os, [&] {
		//		auto finded = linear_sentinel_search(std::cbegin(terminated_dataset), search_value);
		//		});
		//}


		// 二分探索
		//{
		//	// ソート済みのデータセットを前提とする
		//	std::vector<int> sorted_dataset{ std::cbegin(dataset), std::cbegin(dataset) + i };
		//	std::sort(std::begin(sorted_dataset), std::end(sorted_dataset));

		//	print_search_result(os, [&] {
		//		auto finded = binary_search(std::cbegin(sorted_dataset), std::cend(sorted_dataset), search_value);
		//		});
		//}
		//二分岐探索 幅優先探索
/*		{
			std::vector<int> sorted_dataset{ std::begin(dataset), std::end(dataset) };
			std::sort(std::begin(sorted_dataset), std::end(sorted_dataset));

			const auto start = std::chrono::system_clock::now();

			auto finded = breadth_first_search(std::cbegin(sorted_dataset), std::cend(sorted_dataset), search_value);

			const auto finish = std::chrono::system_clock::now();

			const auto processing_time_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();

			std::cout << "sorted[" << std::distance(std::cbegin(sorted_dataset), finded) << "] = " << *finded << "\t" << processing_time_ns << "ns \t(breadth_first_search)" << std::endl;
		}*/



		//二分木探索 深さ優先探索 先行順
	   //{
	   //	const auto start = std::chrono::system_clock::now();

	   //	auto finded = depth_first_preorder_search(std::cbegin(dataset), std::cend(dataset), search_value);

	   //	const auto finish = std::chrono::system_clock::now();

	   //	const auto processing_time_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();

	   //	std::cout << "dataset[" << std::distance(std::cbegin(dataset), finded) << "] = " << *finded << "\t" << processing_time_ns << "ns \t(depth_first_preorder_search)" << std::endl;
	   //}

		os << std::endl;

	}

}

