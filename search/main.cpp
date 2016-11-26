#include "timer.h"
#include "random_int.h"

#include <boost/bind.hpp>
#include <boost/foreach.hpp>

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

void generateVector(int n, int lowerBound, int upperBound, std::vector<int> &result) {
	using utils::RandomInt;
	RandomInt random(lowerBound, upperBound);
	result.resize(n);
	std::generate(result.begin(), result.end(), boost::bind(&RandomInt::generate, &random));
}

void testLowerBound(const std::vector<int> &data, const std::vector<int> &queries) {
	utils::Timer timer;
	int result = 0;
	BOOST_FOREACH(int query, queries) {
		result += static_cast<int>(std::lower_bound(data.begin(), data.end(), query) - data.begin());
	}
	std::cout << result << std::endl
	          << timer.getElapsedTime() / queries.size() << std::endl;
}

void testSmartSearch(const std::vector<int> &data, const std::vector<int> &queries) {
	int blockSize = 0;
	while (blockSize * blockSize * blockSize < static_cast<int>(data.size())) {
		blockSize++;
	}
	if (blockSize * blockSize * blockSize != static_cast<int>(data.size())) {
		throw std::runtime_error("data.size() is not a cube");
	}
	
	std::vector<int> level1(blockSize), level2(blockSize * blockSize);
	for (int i = 0; i < blockSize; ++i) {
		level1[i] = data[(i + 1) * blockSize * blockSize - 1];
	}
	for (int i = 0; i < blockSize * blockSize; ++i) {
		level2[i] = data[(i + 1) * blockSize - 1];
	}
	
	utils::Timer timer;
	int result = 0;
	BOOST_FOREACH(int query, queries) {
		int x = static_cast<int>(std::lower_bound(level1.begin(), level1.end(), query) - level1.begin());
		if (x != blockSize) {
			x = static_cast<int>(std::lower_bound(level2.begin() + x * blockSize, level2.begin() + (x + 1) * blockSize, query) - level2.begin());
			x = static_cast<int>(std::lower_bound(data.begin() + x * blockSize, data.begin() + (x + 1) * blockSize, query) - data.begin());
			result += x;
		}
		else {
			result += static_cast<int>(data.size());
		}
	}
	
	std::cout << result << std::endl
	          << timer.getElapsedTime() / queries.size() << std::endl;	
}

int main() {
	const int N = 1 << 27;
	const int MAX_NUM = 2000000000;
	const int NUM_QUERIES = 10000000;
	
	std::vector<int> data;
	generateVector(N, 0, MAX_NUM, data);
	std::sort(data.begin(), data.end());	
	std::cout << "generated data" << std::endl;
	
	std::vector<int> queries;
	generateVector(NUM_QUERIES, 0, MAX_NUM, queries);
	std::cout << "generated queries" << std::endl;

	testSmartSearch(data, queries);
	testLowerBound(data, queries);
	return 0;
}
