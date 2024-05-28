#pragma once

#include <thread>

/**
 *   @brief �񕪒T��
 */
template <typename InputIterator>
InputIterator binary_search(InputIterator begin, InputIterator end, int value)
{

	std::this_thread::sleep_for(std::chrono::nanoseconds(100));  // 1�b�ҋ@
	if (begin == end)
	{
		return end;  // �I�[�ɓ��B �񕪒T���͔�������ꍇ�̕��򂪍ł��[���Ȃ邽�߁Aend ��Ԃ��Ă�OK (���������)
	}

	InputIterator center = begin + (end - begin) / 2;

	if (*center == value)
	{
		return center;  // ����
	}
	else if (*center < value)
	{
		return binary_search(center + 1, end, value);  // �E����T��
	}
	else
	{
		return binary_search(begin, center, value);  // ������T��
	}
}
