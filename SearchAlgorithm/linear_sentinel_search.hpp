#pragma once

/**
 *   @brief 線形探索 / 兵番法
 */
template <typename InputIterator>
InputIterator linear_sentinel_search(InputIterator begin, int value)
{
    for (auto it = begin; ; ++it)  // 終端までには必ず見つかる前提
    {
        if (*it == value)
        {
            return it;  // 発見
        }
    }
    return {};  // not reached
}
