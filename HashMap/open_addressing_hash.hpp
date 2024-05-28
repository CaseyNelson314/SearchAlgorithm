#pragma once


/**
 *   @brief ハッシュマップ / オープンアドレス法
 */
template <typename Key, typename Value>
class open_addressing_hash
{
    struct element {
        Value value;
        bool is_empty = true;
    };

    std::vector<element> hash_table;

public:

    open_addressing_hash(const std::vector<std::pair<Key, Value>>& init)
        : hash_table(init.size())
    {
        for (auto&& pair : init)
        {
            for (int i = 0; i < hash_table.size(); ++i)
            {
                size_t index = hash(pair.first, i);  // 衝突回数に応じてハッシュの算出方法を変える

                auto& e = hash_table.at(index);

                if (e.is_empty)
                {
                    e.value = pair.second;
                    e.is_empty = false;
                    break;
                }
            }
        }
    }

    Value& search(const Key& key, const Value& value)
    {
        for (int i = 0; i < hash_table.size(); ++i)
        {
            size_t index = hash(key, i);  // value が見つかるまでハッシュの算出方法を変える

            if (hash_table.at(index).is_empty)
            {
                throw std::out_of_range("not found");
            }

            if (hash_table.at(index).value == value)  // value が見つかるまで
            {
                return hash_table.at(index).value;
            }
        }

        throw std::out_of_range("not found");
    }

private:

    size_t hash(const Key& key, size_t collision_count) const
    {
        return (std::hash<Key>{}(key)+collision_count) % hash_table.size();
    }
};
