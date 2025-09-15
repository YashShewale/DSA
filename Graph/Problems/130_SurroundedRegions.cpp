#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#define ll long long

//Approach :- Mark Safe 'O's before flipping

class Solution
{

public:
    void solve(vector<vector<char>> &board)
    {
        int m = board.size();
        int n = board[0].size();
        vector<vector<int>> change;
        vector<pair<int, int>> dirs;
        change.resize(m, vector<int>(n, 1));
        dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        auto dfs = [&](int x, int y, auto &&self) -> void
        {
            change[x][y] = 0;
            for (auto [dx, dy] : dirs)
            {
                int i = x + dx;
                int j = y + dy;

                if (i >= 0 && i < m && j >= 0 && j < n && board[i][j] == 'O' && change[i][j] == 1)
                {
                    self(i, j, self);
                }
            }
        };

        for (int i = 0; i < m; i++)
        {
            if (board[i][0] == 'O' && change[i][0] == 1)
            {
                dfs(i, 0, dfs);
            }

            if (board[i][n - 1] == 'O' && change[i][n - 1] == 1)
            {
                dfs(i, n - 1, dfs);
            }
        }

        for (int j = 0; j < n; j++)
        {
            if (board[0][j] == 'O' && change[0][j] == 1)
            {
                dfs(0, j, dfs);
            }

            if (board[m - 1][j] == 'O' && change[m - 1][j] == 1)
            {
                dfs(m - 1, j, dfs);
            }
        }

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] == 'O' && change[i][j])
                {
                    board[i][j] = 'X';
                }
            }
        }
    }
};

int main()
{

    return 0;
}