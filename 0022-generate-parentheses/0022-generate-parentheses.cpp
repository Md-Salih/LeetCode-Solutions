#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        backtrack(result, "", 0, 0, n);
        return result;
    }
    
    void backtrack(vector<string>& result, string current, int openCount, int closeCount, int n) {
        if (openCount == n && closeCount == n) {
            result.push_back(current);
            return;
        }
        
        if (openCount < n) {
            backtrack(result, current + "(", openCount + 1, closeCount, n);
        }
        if (closeCount < openCount) {
            backtrack(result, current + ")", openCount, closeCount + 1, n);
        }
    }
};