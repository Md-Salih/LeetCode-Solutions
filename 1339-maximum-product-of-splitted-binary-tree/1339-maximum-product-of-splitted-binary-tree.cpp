class Solution {
public:
    static const int MOD = 1e9 + 7;

    // Compute sum of subtree rooted at node
    long long subtreeSum(TreeNode* root) {
        if (!root) return 0;
        return root->val + subtreeSum(root->left) + subtreeSum(root->right);
    }

    long long totalSum(TreeNode* root) {
        if (!root) return 0;
        return root->val + totalSum(root->left) + totalSum(root->right);
    }

    void dfs(TreeNode* node, TreeNode* root, long long total, long long& ans) {
        if (!node) return;

        // skip root because we cannot cut above it
        if (node != root) {
            long long sub = subtreeSum(node);
            long long product = sub * (total - sub);
            ans = max(ans, product);
        }

        dfs(node->left, root, total, ans);
        dfs(node->right, root, total, ans);
    }

    int maxProduct(TreeNode* root) {
        long long total = totalSum(root);
        long long ans = 0;

        dfs(root, root, total, ans);

        return ans % MOD;
    }
};