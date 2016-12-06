#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

void print_vector(const std::string &tag, const std::vector<int> &v)
{
    std::cout << tag << ": ";
    for (auto &e: v) {
        std::cout << e << " ";
    }
    std::cout << "\n";
}

bool consecutive_values(const std::vector<int> &v, size_t count, int value)
{
    return std::search_n(v.begin(), v.end(), count, value) != v.end();
}

int main()
{
    std::vector<int> v1 {1, 2, 2, 3, 5, 5, 10};
    print_vector("v1", v1);
    std::vector<int> v2 {0, 2, 2, 2, 4, 5, 9};
    print_vector("v2", v2);

    std::vector<int> v3;
    std::vector<int> v4;
    std::vector<int> v5;

    std::set_intersection(v1.begin(), v1.end(),
                          v2.begin(), v2.end(),
                          std::back_inserter(v3));
    print_vector("intersection", v3);

    std::set_union(v1.begin(), v1.end(),
                          v2.begin(), v2.end(),
                          std::back_inserter(v4));
    print_vector("union", v4);

    std::set_difference(v1.begin(), v1.end(),
                          v2.begin(), v2.end(),
                          std::back_inserter(v5));
    print_vector("difference", v5);

    assert(std::includes(v1.begin(), v1.end(),
                         v5.begin(), v5.end()));
    assert(!std::includes(v2.begin(), v2.end(),
                          v5.begin(), v5.end()));

    assert(consecutive_values(v1, 2, 5));
    assert(!consecutive_values(v1, 3, 5));
    assert(!consecutive_values(v1, 1, 7));

    assert(std::binary_search(v1.begin(), v1.end(), 5));
    assert(!std::binary_search(v1.begin(), v1.end(), 7));
}
