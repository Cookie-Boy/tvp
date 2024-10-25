#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Matrix {
  private:
    int row;
    int col;

  public:
    Matrix() : row(0), col(0) {}
    Matrix(int row, int col) : row(row), col(col) {}

    int get_row() const {
        return row;
    }

    int get_col() const {
        return col;
    }
};

int OPP(const vector<Matrix>& matrices) {
    int n = matrices.size();
    vector<vector<int>> arr(n, vector<int>(n, INT_MAX));

    for (int i = 0; i < n; i++)
        arr[i][i] = 0;

    for (int t = 1; t < n; t++)
    {
        for (int k = 0; k < n - t; k++)
        {
            int end = k + t;
            for (int j = k; j < end; j++)
            {
                int cost = arr[k][j] + arr[j + 1][end] + matrices[k].get_row() * matrices[j + 1].get_row() * matrices[end].get_col();
                arr[k][end] = min(arr[k][end], cost);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (arr[i][j] == INT_MAX)
                cout << "inf ";
            else 
                cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    return arr[0][n - 1];
}

int main() {
    vector<Matrix> matrices;
    matrices.push_back(Matrix(10, 20));
    matrices.push_back(Matrix(20, 50));
    matrices.push_back(Matrix(50, 1));
    matrices.push_back(Matrix(1, 100));

    cout << "Minimum number of operations: " << OPP(matrices) << endl;

    return 0;
}
