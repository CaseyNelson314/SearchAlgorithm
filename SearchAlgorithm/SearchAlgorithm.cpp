#include <algorithm>
#include <iostream>
#include <vector>
#include <chrono>

std::vector<int> dataset = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
				  11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };

/**
 *   @brief 線形探索
 */
template <typename InputIterator>
InputIterator linear_seach_sentinel_loop(InputIterator begin, InputIterator end, int value)
{
	for (auto it = begin; it != end; ++it)  // 終端までには必ず見つかる前提
	{
		if (*it == value)
		{
			return it;
		}
	}
	return dataset.cend();
}

/**
 *   @brief 線形探索 兵番法
 */
template <typename InputIterator>
InputIterator linear_seach_sentinel_loop(InputIterator begin, int value)
{
	for (auto it = begin; ; ++it)  // 終端までには必ず見つかる前提
	{
		if (*it == value)
		{
			return it;
		}
	}

	return {};  // not reached
}

std::vector<int>::const_iterator binary_seach_impl(
	std::vector<int>::const_iterator begin,
	std::vector<int>::const_iterator end,
	int value)
{
	std::vector<int>::const_iterator center = begin + (end - begin) / 2;

	if (*center == value)
	{
		return center;
	}
	else if (begin == end)
	{
		return end;
	}
	else if (*center < value)
	{
		return binary_seach_impl(center + 1, end, value);
	}
	else
	{
		return binary_seach_impl(begin, center, value);
	}
}

/**
 *   @brief 二分探索
 */
int* binary_seach(int* begin, int* end, int value)
{
	std::vector<int> sorted_dataset{ begin, end };
	std::vector<int>::iterator;
	std::sort(std::begin(sorted_dataset), std::end(sorted_dataset));
	return binary_seach_impl(sorted_dataset.data(), sorted_dataset.data() + sorted_dataset.size(), value);
}


/**
 *   @brief 実行時間計測
 */
template <typename F>
double progress_time_ns(F&& functor, int n)
{
	const auto start = std::chrono::system_clock::now();

	for (int i = 0; i < n; ++i)
	{
		functor();
	}

	const auto finish = std::chrono::system_clock::now();

	return std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() / (double)n;
}


int main(char** argv)
{
	const int search_value = 20;

	{
		const auto t = progress_time_ns([] {
			linear_seach(std::begin(dataset), std::end(dataset), search_value);
			}, 10'000);

		std::cout << "linear_seach: " << t << "ns" << std::endl;
	}

	{
		const auto t = progress_time_ns([] {
			linear_seach_sentinel_loop(std::begin(dataset), search_value);
			}, 10'000);

		std::cout << "linear_seach_sentinel_loop: " << t << "ns" << std::endl;
	}

	{
		std::vector<int> sorted_vector{ std::begin(dataset), std::end(dataset) };
		std::sort(std::begin(sorted_vector), std::end(sorted_vector));

		const auto t = progress_time_ns([&] {
			binary_seach_impl(sorted_vector.data(), sorted_vector.data() + sorted_vector.size(), search_value);
			}, 10'000);

		std::cout << "binary_seach: " << t << "ns" << std::endl;
	}

}

