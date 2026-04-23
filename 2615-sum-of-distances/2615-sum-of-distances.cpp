#include <memory_resource>
pmr::unsynchronized_pool_resource pool;
class Solution {
public:
    static void print(auto& c){
        for (auto x: c)cout<<x<<", ";
        cout<<endl;
    }
    static vector<long long> distance(vector<int>& nums) {
        pmr::unordered_map<int, vector<long long>> idx(&pool);
        const int n=nums.size();
        idx.reserve(n);
        for(int i=0; i<n; i++){
            const int x=nums[i];
            auto it=idx.find(x);
            if (it==idx.end()) idx[x]={i};
            else idx[x].push_back(i);
        }
        vector<long long> ans(n, 0);
        for(auto& [x, v]: idx){
        //    cout<<"x="<<x<<":"; print(v);
            int vs=v.size();
            if (vs==1) continue;
            vector<long long> sum(vs+1, 0);
            partial_sum(v.begin(), v.end(), sum.begin()+1);
        //    cout<<"sum"<<":"; print(sum);
            for(int i=0; i<vs; i++){
                ans[v[i]] = sum.back()-2LL*sum[i] - (vs-2LL*i) * v[i];

            }

        }
        return ans;
    }
};



auto init = []() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 'c';
}();