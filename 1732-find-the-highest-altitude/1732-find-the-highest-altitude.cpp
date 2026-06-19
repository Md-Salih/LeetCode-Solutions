class Solution {
public:
    int largestAltitude(vector<int>& gain) {
        
        int n = gain.size();

        int pos{};

        int ans{0};

        for (int i = 0; i < n; i++) {
            pos += gain[i];
            ans = max(ans, pos);
        }

        return ans;
    }
};