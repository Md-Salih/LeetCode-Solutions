class Solution {
public:
        long long maxMatrixSum(vector<vector<int>>& mat) {
        int n = mat.size();
        long long total = 0;
        long long cnt = 0;
        int minm = INT_MAX;
        long long neg = 0;
        for(int i = 0;i<n;i++){
            for(int j = 0;j<n;j++){
                total += abs(mat[i][j]);
                minm = min(minm, abs(mat[i][j]));
                if(mat[i][j] == 0) cnt++;
                if(mat[i][j] < 0) neg++;
            }
        }
        if((neg % 2)==0){
            return total;
        }
        else{
            if(cnt > 0) return total;
            else{
                total -= minm;
                total -= minm;
                return total;
            }
        }
    }
};