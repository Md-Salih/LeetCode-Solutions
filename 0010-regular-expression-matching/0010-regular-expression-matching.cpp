class Solution {
public:
    int dp[25][25];

    bool solve(string &txt, string &pat, int i, int j) {
        if (i == pat.size())
            return j == txt.size();

        if (dp[i][j] != -1)
            return dp[i][j];

        bool isMatch = (j < txt.size() &&
                       (pat[i] == txt[j] || pat[i] == '.'));

        if (i + 1 < pat.size() && pat[i + 1] == '*') {
            return dp[i][j] = (
                solve(txt, pat, i + 2, j) ||
                (isMatch && solve(txt, pat, i, j + 1))
            );
        }

        return dp[i][j] = (isMatch && solve(txt, pat, i + 1, j + 1));
    }

    bool isMatch(string s, string p) {
        memset(dp, -1, sizeof(dp));
        return solve(s, p, 0, 0);
    }
};