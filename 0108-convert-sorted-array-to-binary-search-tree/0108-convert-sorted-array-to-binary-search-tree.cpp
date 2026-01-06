class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        // Base condition...
        if (nums.size() == 0)
			return NULL;
        // Call the function recursively...
		return sortedArrayToBST(nums, 0, nums.size() - 1);
    }
    // Create another function which will convert any particular range of given nums array...
    // & return its corresponding BST root node....
	TreeNode* sortedArrayToBST(vector<int>& nums, int beg, int end) {
        // If beg > end, return NULL, as we receive a wrong range...
		if (beg > end)
			return NULL;
        // If beg == end, return a new node having value same as nums[beg]... 
        if(beg == end)
            return new TreeNode(nums[beg]);
        // set the middle node...
		int mid = (beg + end) / 2;
        // Initialise root node with value same as nums[mid]
		TreeNode* root = new TreeNode(nums[mid]);
        // Assign left subtrees as the same function called on left subranges...
		root->left = sortedArrayToBST(nums, beg, mid - 1);
        // Assign right subtrees as the same function called on right subranges...
		root->right = sortedArrayToBST(nums, mid + 1, end);
        // Return the root node
		return root;
    }
};