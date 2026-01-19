class Solution {
public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> ps(m+1, vector<int>(n+1, 0));
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                ps[i][j] = mat[i-1][j-1] + ps[i-1][j] + ps[i][j-1] - ps[i-1][j-1];
        int res = 0, size = min(m, n);
        for (int k = 1; k <= size; k++) {
            bool found = false;
            for (int i = 0; i + k <= m && !found; i++)
                for (int j = 0; j + k <= n; j++)
                    if (ps[i+k][j+k] - ps[i][j+k] - ps[i+k][j] + ps[i][j] <= threshold) {
                        found = true; break;
                    }
            if (found) res = k; else break;
        }
        return res;
    }
};