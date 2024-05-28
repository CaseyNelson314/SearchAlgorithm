#pragma once


/**
 *   @brief ハッシュマップ / チェイン法
 */
template <typename Key, typename Value>
class chaining_hash
{
    struct chain
    {
        std::vector<Value> values;
    };

    std::vector<chain> hash_table;

public:

    chaining_hash(const std::vector<std::pair<Key, Value>>& init)
        : hash_table(init.size())
    {
        for (auto&& pair : init)
        {
            hash_table.at(hash(pair.first)).values.push_back(pair.second);
        }
    }

    Value& search(const Key& key, const Value& value)
    {
        auto& chain = hash_table.at(hash(key));  // ハッシュ値よりチェインを取得

        for (auto it = std::begin(chain.values); it != std::end(chain.values); ++it)
        {
            if (*it == value)
            {
                return *it;
            }
        }

        throw std::out_of_range("not found");
    }

private:

    size_t hash(const Key& key) const
    {
        return std::hash<Key>{}(key) % hash_table.size();
    }
};
