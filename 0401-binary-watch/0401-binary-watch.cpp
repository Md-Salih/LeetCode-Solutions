class Solution {
public:
    vector<string> readBinaryWatch(int k) {
        if (k == 0) return {"0:00"};
        if (k > 8) return {};
        vector<string> res;
        int q = (1 << k) - 1;

        while (q < (1 << 10)) {
            string time = isValid(q);
            if (!time.empty()) res.push_back(time);
            int r = q & -q;
            int n = q + r;
            q = (((n ^ q) >> 2) / r) | n;
        }
        return res;
    }

    string isValid(int q) {
        int hour = q >> 6;
        int min = q & 63;
        if (hour >= 12 || min >= 60) return "";
        return to_string(hour) + ":" + (min < 10 ? "0" : "") + to_string(min);
    }
};
