#pragma once

/**
 *   @brief 線形探索
 */
template <typename InputIterator>
InputIterator linear_search(InputIterator begin, InputIterator end, int value)
{
    for (auto it = begin; it != end; ++it)
    {
        if (*it == value)
        {
            return it;  // 発見
        }
    }
    return end;
}