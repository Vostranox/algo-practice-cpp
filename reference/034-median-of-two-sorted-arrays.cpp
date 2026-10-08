#include "prelude.hpp"

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        vector<int>& A = nums1.size() <= nums2.size() ? nums1 : nums2;
        vector<int>& B = nums1.size() <= nums2.size() ? nums2 : nums1;
        int m = A.size(), n = B.size(), half = (m + n + 1) / 2;
        int lo = 0, hi = m;
        while (true) {
            int i = lo + (hi - lo) / 2;
            int j = half - i;
            int64_t aLeft = i > 0 ? A[i - 1] : INT64_MIN, aRight = i < m ? A[i] : INT64_MAX;
            int64_t bLeft = j > 0 ? B[j - 1] : INT64_MIN, bRight = j < n ? B[j] : INT64_MAX;
            if (aLeft > bRight) {
                hi = i - 1;
            } else if (bLeft > aRight) {
                lo = i + 1;
            } else {
                int64_t leftMax = max(aLeft, bLeft);
                if ((m + n) % 2) return leftMax;
                return (leftMax + min(aRight, bRight)) / 2.0;
            }
        }
    }
};
