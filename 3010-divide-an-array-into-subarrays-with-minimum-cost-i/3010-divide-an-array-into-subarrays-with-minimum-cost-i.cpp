class Solution {
public:
    int minimumCost(vector<int>& nums) {
        int n=nums.size();
        if (n==3) return nums[0]+nums[1]+nums[2];
        int x1=INT_MAX, x2=INT_MAX;
        for (int i=1; i<n; i++){
            int x=nums[i];
            if (x<x1) x2=exchange(x1, x);
            else if (x<x2) x2=x;
        }
        return nums[0]+x1+x2;
    }
};

auto init = []()
{ 
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 'c';
}();