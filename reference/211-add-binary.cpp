#include "prelude.hpp"

class Solution {
public:
    string addBinary(string a, string b) {
        string res;
        int i = a.size() - 1, j = b.size() - 1, carry = 0;
        while (i >= 0 || j >= 0 || carry) {
            int sum = carry + (i >= 0 ? a[i--] - '0' : 0) + (j >= 0 ? b[j--] - '0' : 0);
            res.push_back(char('0' + sum % 2));
            carry = sum / 2;
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
