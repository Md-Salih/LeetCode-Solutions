class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        string res = "";

        for(int i=0;i<n;i++){
            // Odd length palindrome
            int st=i,end=i;
            while(st>=0&&end<n&&s[st]==s[end]){
                st--;
                end++;
            }
            string temp=s.substr(st+1,end-st-1);
            if(temp.size()>res.size())res=temp;

            // Even length palindrome
            st=i;
            end=i+1;
            while(st>=0&&end<n&&s[st]==s[end]){
                st--;
                end++;
            }
            temp=s.substr(st+1,end-st-1);
            if(temp.size()>res.size())res=temp;
        }

        return res;
    }
};