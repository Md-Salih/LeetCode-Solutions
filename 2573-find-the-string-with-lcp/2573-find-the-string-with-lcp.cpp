class Solution {
class DSU{
public:
    vector<int> parent, rank;

    DSU(int n){
        parent.resize(n);
        rank.resize(n,0);
        for(int i=0;i<n;i++) parent[i]=i;
    }

    int findPar(int x){
        if(parent[x]==x) return x;
        return parent[x]=findPar(parent[x]);
    }

    void unite(int x,int y){
        int px=findPar(x);
        int py=findPar(y);

        if(px==py) return;

        if(rank[px]<rank[py]) parent[px]=py;
        else if(rank[px]>rank[py]) parent[py]=px;
        else{
            parent[px]=py;
            rank[py]++;
        }
    }
};

public:
    void compute(string &word, vector<vector<int>> &dp){
        int n=word.size();
        for(int i=n-1;i>=0;i--){
            for(int j=n-1;j>=0;j--){
                if(word[i]==word[j]){
                    if(i+1<n && j+1<n)
                        dp[i][j]=1+dp[i+1][j+1];
                    else
                        dp[i][j]=1;
                }
                else dp[i][j]=0;
            }
        }
    }

    string findTheString(vector<vector<int>>& lcp) {
        int n=lcp.size();
        DSU dsu(n);

        for(int i=0;i<n;i++){
            if(lcp[i][i]!=n-i) return "";
        }

        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                if(lcp[i][j]>0)
                    dsu.unite(i,j);
            }
        }

        vector<char> grp(n,0);
        string word(n,'?');
        char c='a';

        for(int i=0;i<n;i++){
            int p=dsu.findPar(i);
            if(grp[p]==0){
                if(c>'z') return "";
                grp[p]=c++;
            }
            word[i]=grp[p];
        }

        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(lcp[i][j]==0 && word[i]==word[j])
                    return "";
            }
        }

        vector<vector<int>> dp(n,vector<int>(n,0));
        compute(word,dp);

        return dp==lcp ? word : "";
    }
};