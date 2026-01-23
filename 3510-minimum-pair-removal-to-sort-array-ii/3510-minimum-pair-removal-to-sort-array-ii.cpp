using ll=long long;
using int2=pair<long long, int>;
const int N=1e5;
bitset<N> rmv=0;
int prv[N], nxt[N];
int2 heap[3*N];
class Solution {
public:
    static int minimumPairRemoval(vector<int>& nums_) {
        const int n=nums_.size();
        ll* nums=(ll*)alloca(n*sizeof(ll));
        copy(nums_.begin(), nums_.end(), nums);

        if (is_sorted(nums, nums+n)) return 0;

        rmv.reset();

        for (int i = 0; i<n; i++) {
            prv[i]=i-1;
            nxt[i]=(i+1<n)? i+1 : -1;
        }

        for (int i=0; i<n-1; i++)
            heap[i]={nums[i]+nums[i+1], i};
        int sz=n-1;
        make_heap(heap, heap+sz, greater<>());

        // initial violation count
        int bad=0;
        for (int i=0; i<n-1; i++)
            if (nums[i]>nums[i+1]) bad++;

        int op=0;

        while (bad>0) {
            pop_heap(heap, heap+sz, greater<>());
            auto [sum, i]=heap[--sz];

            if (rmv[i] || nxt[i]==-1) continue;
            int j=nxt[i];
            if (rmv[j] || nums[i]+nums[j] != sum) continue;

            int pi=prv[i];
            int nj=nxt[j];

            // remove old violations
            if (pi != -1 && nums[pi]>nums[i]) bad--;
            if (nums[i] > nums[j]) bad--;
            if (nj != -1 && nums[j]>nums[nj]) bad--;

            // merge
            nums[i]=sum;
            rmv[j]=1;

            nxt[i]=nj;
            if (nj != -1) prv[nj]=i;

            // add new violations
            if (pi!=-1 && nums[pi]>nums[i]) bad++;
            if (nj!=-1 && nums[i]>nums[nj]) bad++;

            // update heap
            if (pi != -1){
                heap[sz++]={nums[pi]+nums[i], pi};
                push_heap(heap, heap+sz, greater<>());
            }
            if (nj != -1){
                heap[sz++]={nums[i]+nums[nj], i};
                push_heap(heap, heap+sz, greater<>());
            }
            op++;
        }

        return op;
    }
};

