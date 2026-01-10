// Fast version using global variable DP with &1 trick
short dp[2][1001]={0};// short is sufficient
class Solution {
public:
    static int minimumDeleteSum(string& s1, string& s2) {
        const int n1 = s1.size(), n2 = s2.size();
        if (n1<n2){// WLOG assume n1>=n2
            return minimumDeleteSum(s2, s1);
        }
        memset(dp[0], 0, sizeof(short)*(n2+1));
        memset(dp[1], 0, sizeof(short)*(n2+1));

        for (int x=0; x<n1; x++) {
            const bool par=(x+1)&1, prev=par^1;// 1-indexed
            for (int y=0; y<n2; y++) {
                if (s1[x] == s2[y])
                    dp[par][y+1] = s1[x] + dp[prev][y];
                else
                    dp[par][y+1] = max(dp[prev][y+1], dp[par][y]);
            }
        }
        // std::accumulate is good for using
        int AsciiSum = accumulate(s1.begin(), s1.end(), 0);
        AsciiSum = accumulate(s2.begin(), s2.end(), AsciiSum);

        return AsciiSum - 2*dp[n1&1][n2];
    }
};