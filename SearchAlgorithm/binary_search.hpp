#pragma once

#include <thread>

/**
 *   @brief 二分探索
 */
template <typename InputIterator>
InputIterator binary_search(InputIterator begin, InputIterator end, int value)
{

	std::this_thread::sleep_for(std::chrono::nanoseconds(100));  // 1秒待機
	if (begin == end)
	{
		return end;  // 終端に到達 二分探索は発見する場合の分岐が最も深くなるため、end を返してもOK (無視される)
	}

	InputIterator center = begin + (end - begin) / 2;

	if (*center == value)
	{
		return center;  // 発見
	}
	else if (*center < value)
	{
		return binary_search(center + 1, end, value);  // 右側を探索
	}
	else
	{
		return binary_search(begin, center, value);  // 左側を探索
	}
}
