// bitset version of counting sort
const int N=2e6+1;
bitset<N> hasX=0;
class Solution {
public:
    static vector<vector<int>> minimumAbsDifference(vector<int>& arr){
        const int n=arr.size();
        int* a=arr.data(); //get C-array
        auto [m, M]=minmax_element(a, a+n);
        int bias=*m, range=*M-bias+1;
        hasX=0;// distinct integers arr
        for(int i=0; i<n; i++){
            hasX[a[i]-bias]=1;
        }
        int  minD=1e9, prevX=-1e9;

        // this part can be simplified in a single loop
        for(int i=0, idx=0; i<range; i++){
            if(!hasX[i]) continue;
            const int x=i+bias;
            a[idx++]=x;
            minD=min(minD, x-prevX);
            prevX=x;
        }

        vector<vector<int>> ans;
        for(int i=1; i<n; i++){
            if (a[i]-a[i-1]==minD)
                ans.push_back({a[i-1], a[i]});
        }
        return ans;
    }
};
auto init = []()
{ 
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 'c';
}();