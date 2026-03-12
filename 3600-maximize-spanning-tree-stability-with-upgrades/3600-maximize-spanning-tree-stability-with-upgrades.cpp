constexpr int N=1e5;
int Rt[N], Rk[N];
// arrays for bucket sort (linked list)
int head[N+1], next_e[N+1];

class UnionFind { // UnionFind class with rank, component
    int* root, *rank;
public:
    int component; // make it public 
    UnionFind(int n) : component(n) {
        root=Rt;
        rank=Rk;
        memset(rank, 0, n*sizeof(int));
        iota(root, root+n, 0);
    }

    int Find(int x) {
        return (x==root[x])?x:root[x]=Find(root[x]);
    }

    bool Union(int x, int y) {
        x=Find(x), y=Find(y);
        if (x == y) return 0;
        if (rank[x]>rank[y]) swap(x, y);
        root[x]=y;
        if (rank[x]==rank[y]) rank[y]++;
        component--;
        return 1;
    }
};

class Solution {
public:
    static int maxStability(int n, vector<vector<int>>& edges, int k) {
        UnionFind G(n);
        int sMax=0, sMin=N+1;
        int score=2e5;
        const int E=edges.size();

        // Initialize buckets (linked list)
        memset(head, -1, sizeof(head));

        for (int i=0; i<E; i++) {
            const auto& e=edges[i];
            const int u=e[0], v=e[1], s=e[2], must=e[3];
            if (must) {
                if (!G.Union(u, v)) // cycle detect
                    return -1;
                score=min(score, s);
            } 
            else {
                sMax=max(sMax, s);
                sMin=min(sMin, s);
                // Insert index i at head of list for bucket s
                next_e[i]=head[s];
                head[s]=i;
            }
        }
        if (G.component==1) return score>N ? -1 : score;

        int used=0, needed=G.component-1;
        int minX2=N*2;
        int minX1=N*2;

        // Kruskal's via Buckets (descending)
        for (int s=sMax; s>=sMin; s--) {
            for (int i = head[s]; i != -1; i = next_e[i]) {
                if (!G.Union(edges[i][0], edges[i][1])) continue;   
                used++;
                // The very min which is x2
                if (used==needed) minX2=s*2;
                
                // The min score for edges not upgrading
                // (needed-k)-th edge which is x1
                if (used==needed-k) minX1=s;
                if (G.component==1) break;
            }
            if (G.component==1) break;
        }

        if (G.component>1) return -1;

        int opt_score=minX2;
        if (needed>k) 
            opt_score=min(opt_score, minX1);

        int ans=min(score, opt_score);
        return ans>N*2?-1:ans;
    }
};