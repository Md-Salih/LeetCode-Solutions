// Use DP+ Floyd Warshall's algorithm
// Trie needs redesigning to replace the part of hashmap id & lens
// add bitmask for Floyd Warshall's alg to reduce
// the computational amounts
using int2 = pair<short, short>;

struct TrieNode {
    TrieNode* links[26];
    short id; 
};

static constexpr int N=200000;// 200 (strings)*1000 (length)
static TrieNode POOL[N];
int ptr=0;
int idx=0;

struct Trie {
    TrieNode* root;
    TrieNode* newNode() {
        TrieNode* node = &POOL[ptr++];
        memset(node->links, 0, sizeof(node->links));
        node->id=-1;
        return node;
    }
    void reset() { 
        ptr=idx= 0; 
        root=newNode(); 
    }
    
    int insert(const string& s) {// returning id
        TrieNode* cur=root;
        for (char c : s) {
            int i=c-'a';
            if (!cur->links[i]) cur->links[i]=newNode();
            cur=cur->links[i];
        }
        if (cur->id==-1) cur->id=idx++;
        return cur->id;
    }
};

uint64_t D[201][201];
uint64_t dp[1001];
const uint64_t INF=ULONG_MAX;

uint64_t rowMask[4], colMask[4];// for row, col bitmasks

class Solution {
public:
    Trie trie;

    void init() {
        if (D[0][0]!=INF)
            memset(D, 255, sizeof(D));
    }
    int maxLen=0;

    long long minimumCost(string source, string target, vector<string>& original, vector<string>& changed, vector<int>& cost) {
        init();
        trie.reset();
        int m=original.size(), n=source.size();
        memset(rowMask, 0, sizeof(rowMask));
        memset(colMask, 0, sizeof(colMask));
        for (int i=0; i<m; i++) {
            maxLen=max(maxLen, (int)original[i].size());
            int row=trie.insert(original[i]);
            int col=trie.insert(changed[i]);

            // bitmask
            auto [q0, r0]=div(row, 64);
            rowMask[q0]|=(1ULL<<r0);
            auto [q1, r1]=div(col, 64);
            colMask[q1]|=(1ULL<<r1);

            D[row][col]=min(D[row][col], (uint64_t)cost[i]);
        }

        for (int i=0; i<idx; i++) D[i][i]=0;

        for (int k=0; k<idx; k++) {
            for(int wr=0; wr<4; wr++){
                for (uint64_t r=rowMask[wr]; r; r&=(r-1)) {
                    const int i=wr*64+countr_zero(r);
                    if (D[i][k]==INF) continue;
                    for(int wc=0; wc<4; wc++){
                        for (uint64_t c=colMask[wc]; c; c&=(c-1)) {
                            const int j=wc*64+countr_zero(c);
                            if (D[k][j]==INF) continue;
                                D[i][j]=min(D[i][j], D[i][k]+D[k][j]);
                        }
                    }
                }
            }
        }

        memset(dp, 255, sizeof(uint64_t)*(n+1));
        dp[0]=0;

        for (int i=0; i<n; i++) {
            if (dp[i]==INF) continue;

            // Match
            if (source[i]==target[i]) 
                dp[i+1]=min(dp[i+1], dp[i]);

            // Simultaneous Trie traversal
            TrieNode* curS=trie.root, *curT=trie.root;
            
            // Limit search by the maximum word length or string remaining
            const int lz=min(maxLen, n-i);
            for (int len=1; len<=lz; len++) {
                int charS=source[i+len-1]-'a';
                int charT=target[i+len-1]-'a';
                
                // If the prefix doesn't exist in our Trie at all, we can stop
                if (curS) curS=curS->links[charS];
                if (curT) curT=curT->links[charT];
                
                if (!curS && !curT) break;

                // If both source and target substrings have IDs, check the cost
                if (curS && curT && curS->id!=-1 && curT->id!= -1) {
                    uint64_t c=D[curS->id][curT->id];
                    if (c<INF) dp[i+len] = min(dp[i+len], dp[i]+c);
                }
            }
        }
        for (int i=0; i<idx; i++)// reset for the next testcase
            memset(D[i], 255, sizeof(uint64_t)*idx);
        return dp[n]==INF? -1 : dp[n];
    }
};

auto init = []() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 'c';
}();