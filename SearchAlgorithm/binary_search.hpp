#pragma once

#include <thread>

/**
 *   @brief “ñ•ª’Tõ
 */
template <typename InputIterator>
InputIterator binary_search(InputIterator begin, InputIterator end, int value)
{

	std::this_thread::sleep_for(std::chrono::nanoseconds(100));  // 1•b‘Ò‹@
	if (begin == end)
	{
		return end;  // I’[‚É“’B “ñ•ª’Tõ‚Í”­Œ©‚·‚éê‡‚Ì•ªŠò‚ªÅ‚à[‚­‚È‚é‚½‚ßAend ‚ğ•Ô‚µ‚Ä‚àOK (–³‹‚³‚ê‚é)
	}

	InputIterator center = begin + (end - begin) / 2;

	if (*center == value)
	{
		return center;  // ”­Œ©
	}
	else if (*center < value)
	{
		return binary_search(center + 1, end, value);  // ‰E‘¤‚ğ’Tõ
	}
	else
	{
		return binary_search(begin, center, value);  // ¶‘¤‚ğ’Tõ
	}
}
