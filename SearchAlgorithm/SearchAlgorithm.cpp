#include <algorithm>
#include <numeric>
#include <iostream>
#include <vector>
#include <chrono>
#include <memory>

/**
 *   @brief 線形探索
 */
template <typename InputIterator>
InputIterator linear_seach(InputIterator begin, InputIterator end, int value)
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


/**
 *   @brief 線形探索 / 兵番法
 */
template <typename InputIterator>
InputIterator linear_sentinel_seach(InputIterator begin, int value)
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


/**
 *   @brief 二分探索
 */
template <typename InputIterator>
InputIterator binary_seach(InputIterator begin, InputIterator end, int value)
{
	if (begin == end)
	{
		return end;
	}

	InputIterator center = begin + (end - begin) / 2;

	if (*center == value)
	{
		return center;  // 発見
	}
	else if (*center < value)
	{
		return binary_seach(center + 1, end, value);  // 再帰木の右側を探索
	}
	else
	{
		return binary_seach(begin, center, value);  // 再帰木の左側を探索
	}
}


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
	if (begin == end)
	{
		return end;
	}

	InputIterator center = begin + (end - begin) / 2;

	if (*center == value)
	{
		return center;
	}

	auto left = breadth_first_search(begin, center, value);
	if (left != end)
	{
		return left;  // 左側を探索し発見した場合
	}

	auto right = breadth_first_search(center + 1, end, value);
	if (right != end)
	{
		return right;  // 右側を探索し発見した場合
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

	chaining_hash(std::initializer_list<std::pair<Key, Value>> init)
		: hash_table(std::distance(std::begin(init), std::end(init)))
	{
		for (auto&& pair : init)
		{
			hash_table.at(hash(pair.first)).values.push_back(pair.second);
		}
	}

	Value& search(const Key& key, const Value& value)
	{
		auto& chain = hash_table.at(hash(key));  // ハッシュ値よりチェインを取得

		auto it = std::find(std::begin(chain.values), std::end(chain.values), value);   // value が見つかるまでチェインを探索

		if (it == std::end(chain.values))
		{
			throw std::out_of_range("not found");
		}

		return *it;
	}

private:

	size_t hash(const Key& key) const
	{
		return std::hash<Key>{}(key) % hash_table.size();
	}
};


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

	open_addressing_hash(std::initializer_list<std::pair<Key, Value>> init)
		: hash_table(std::distance(std::begin(init), std::end(init)))
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


int main()
{
	std::vector<int> dataset(1000);
	std::iota(dataset.begin(), dataset.end(), 0);
	std::random_shuffle(dataset.begin(), dataset.end());

	const int search_value = 2000;

	// 線形探索
	{
		const auto start = std::chrono::system_clock::now();

		auto finded = linear_seach(std::cbegin(dataset), std::cend(dataset), search_value);

		const auto finish = std::chrono::system_clock::now();

		const auto processing_time_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();

		if (finded == std::cend(dataset))
		{
			std::cout << "not found" << "\t" << processing_time_ns << "ns \t(linear_seach)" << std::endl;
		}
		else
		{
			std::cout << "dataset[" << std::distance(std::cbegin(dataset), finded) << "] = " << *finded << "\t" << processing_time_ns << "ns \t(linear_seach)" << std::endl;
		}
	}


	// 線形探索 / 兵番法
	{
		std::vector<int> terminated_dataset{ std::begin(dataset), std::end(dataset) };
		terminated_dataset.push_back(search_value);

		const auto start = std::chrono::system_clock::now();

		auto finded = linear_sentinel_seach(std::cbegin(terminated_dataset), search_value);

		const auto finish = std::chrono::system_clock::now();

		const auto processing_time_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();

		if (finded == std::cend(terminated_dataset) - 1)
		{
			std::cout << "not found" << "\t" << processing_time_ns << "ns \t(linear_sentinel_seach)" << std::endl;
		}
		else
		{
			std::cout << "dataset[" << std::distance(std::cbegin(terminated_dataset), finded) << "] = " << *finded << "\t" << processing_time_ns << "ns \t(linear_sentinel_seach)" << std::endl;
		}
	}


	// 二分探索
	{
		std::vector<int> sorted_dataset{ std::begin(dataset), std::end(dataset) };
		std::sort(std::begin(sorted_dataset), std::end(sorted_dataset));

		const auto start = std::chrono::system_clock::now();

		auto finded = binary_seach(std::cbegin(sorted_dataset), std::cend(sorted_dataset), search_value);

		const auto finish = std::chrono::system_clock::now();

		const auto processing_time_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();

		if (finded == std::cend(sorted_dataset))
		{
			std::cout << "not found" << "\t" << processing_time_ns << "ns \t(binary_seach)" << std::endl;
		}
		else
		{
			std::cout << "sorted[" << std::distance(std::cbegin(sorted_dataset), finded) << "] = " << *finded << "\t" << processing_time_ns << "ns \t(binary_seach)" << std::endl;
		}
	}

	 //二分木探索 深さ優先探索 先行順
	{
		const auto start = std::chrono::system_clock::now();

		auto finded = depth_first_preorder_search(std::cbegin(dataset), std::cend(dataset), search_value);

		const auto finish = std::chrono::system_clock::now();

		const auto processing_time_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();

		std::cout << "dataset[" << std::distance(std::cbegin(dataset), finded) << "] = " << *finded << "\t" << processing_time_ns << "ns \t(depth_first_preorder_search)" << std::endl;
	}


	// 二分岐探索 幅優先探索
	//{
	//	std::vector<int> sorted_dataset{ std::begin(dataset), std::end(dataset) };
	//	std::sort(std::begin(sorted_dataset), std::end(sorted_dataset));

	//	const auto start = std::chrono::system_clock::now();

	//	auto finded = breadth_first_search(std::cbegin(sorted_dataset), std::cend(sorted_dataset), search_value);

	//	const auto finish = std::chrono::system_clock::now();

	//	const auto processing_time_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();

	//	std::cout << "sorted[" << std::distance(std::cbegin(sorted_dataset), finded) << "] = " << *finded << "\t" << processing_time_ns << "ns \t(breadth_first_search)" << std::endl;
	//}


	// ハッシュマップ / チェイン法
	{
		chaining_hash<int, double> hash_table
		{
			{  5,  50.0 },
			{  7,  70.0 },
			{ 11,  90.0 },  // ハッシュ衝突
			{ 11, 110.0 },  // ハッシュ衝突
			{ 11, 113.0 },  // ハッシュ衝突
			{ 13, 130.0 },
			{ 17, 170.0 },
		};

		const auto start = std::chrono::system_clock::now();

		auto finded = hash_table.search(11, 110.0);

		const auto finish = std::chrono::system_clock::now();

		const auto processing_time_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();

		std::cout << "hash_table[11] = " << finded << "\t" << processing_time_ns << "ns \t(chaining_hash)" << std::endl;
	}


	// ハッシュマップ / オープンアドレス法
	{
		open_addressing_hash<int, double> hash_table
		{
			{  5,  50.0 },
			{  7,  70.0 },
			{ 11,  90.0 },  // ハッシュ衝突
			{ 11, 110.0 },  // ハッシュ衝突
			{ 11, 113.0 },  // ハッシュ衝突
			{ 13, 130.0 },
			{ 17, 170.0 },
		};

		const auto start = std::chrono::system_clock::now();

		auto finded = hash_table.search(11, 110.0);

		const auto finish = std::chrono::system_clock::now();

		const auto processing_time_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();

		std::cout << "hash_table[11] = " << finded << "\t" << processing_time_ns << "ns \t(open_addressing_hash)" << std::endl;
	}

}

