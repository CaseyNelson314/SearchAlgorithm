#pragma once


/**
 *   @brief ���`�T��
 */
template <typename InputIterator>
InputIterator linear_search(InputIterator begin, InputIterator end, int value)
{
	for (auto it = begin; it != end; ++it)
	{
		if (*it == value)
		{
			return it;  // ����
		}
	}
	return end;
}


/**
 *   @brief ���`�T�� / ���Ԗ@
 */
template <typename InputIterator>
InputIterator linear_sentinel_search(InputIterator begin, int value)
{
	for (auto it = begin; ; ++it)  // �I�[�܂łɂ͕K��������O��
	{
		if (*it == value)
		{
			return it;  // ����
		}
	}

	return {};  // not reached
}
