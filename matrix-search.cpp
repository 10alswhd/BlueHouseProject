// This is a simple example of an algorithm that does a binary search in
// a [m, n] matrix containing integer numbers, ordered such that for each
// i, j and k, l that i<=k and j<=l, m[i][j] <= m[k][l].
// The matrix is pregenerated and the dimensions are fixed for simplicity.
// However the algorithm itself is generic enough to handle any ordered matrix.

#include <iostream>
#include <ostream>
#include <iomanip>
#include <vector>
#include <limits>
#include <algorithm>
#include <string>
#include <tuple>
#include <boost/lexical_cast.hpp>

using namespace std;

using matrix = vector<vector<int>>;

matrix generate(int m, int n)
{
    matrix mat(m);
    for (int i = 0; i != m; ++i)
        mat[i].resize(n);

    for (int i = 0; i != m; ++i)
        for (int j = 0; j != n; ++j)
            mat[i][j] = i * j + 3 * i + j;

    return mat;
}

void print(matrix const & mat)
{
    int m = mat.size();
    int n = mat[0].size();
    int mx = numeric_limits<int>::min();

    for (auto const & col: mat)
        for (auto const & cell: col)
            mx = max(mx, cell);

    int width = boost::lexical_cast<string>(mx).size() + 1;

    for (auto const & col: mat)
    {
        for (auto const & cell: col)
            cout << setw(width) << cell;
        cout << endl;
    }
}

tuple<int, int, bool> search_rec(matrix const & mat,
                                 int min_m,
                                 int min_n,
                                 int max_m,
                                 int max_n,
                                 int val)
{
    cout << "search_rec: (" << min_m << ", " << min_n << "), (" << max_m << ", " << max_n << ")\n";
    if (min_m >= max_m || min_n >= max_n)
        return make_tuple(0, 0, false);

    int mid_m = min_m + (max_m - min_m) / 2;

    auto pivot = lower_bound(mat[mid_m].begin() + min_n, mat[mid_m].begin() + max_n, val);
    int mid_n = pivot - mat[mid_m].begin();

    if (mid_n != max_n && *pivot == val)
        return make_tuple(mid_m, mid_n, true);

    if (mid_n != max_n)
        cout << "value at pivot: " << *pivot << " (" << mid_m << ", " << mid_n << ")" << endl;

    auto search_sq1 = search_rec(mat, min_m, mid_n, mid_m, max_n, val);
    if (get<2>(search_sq1))
        return search_sq1;

    return search_rec(mat, mid_m + 1, min_n, max_m, mid_n, val);
}

tuple<int, int, bool> search(matrix const & mat, int val)
{
    int m = mat.size();
    int n = mat[0].size();
    return search_rec(mat, 0, 0, m, n, val);
}

int main(int argc, char * argv[])
{
    int findv = 42;
    if (argc > 1)
        findv = boost::lexical_cast<int>(argv[1]);

    matrix m = generate(10, 10);
    print(m);
    auto pos = search(m, findv);
    if (get<2>(pos))
        cout << "found: " << get<0>(pos) << ", " << get<1>(pos) << endl;
    else
        cout << "not found\n";
}
