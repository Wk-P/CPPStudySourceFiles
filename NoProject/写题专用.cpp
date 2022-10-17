#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

typedef vector<int> IntVec;

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int i = 0, j = 0, size1 = nums1.size(), size2 = nums2.size(), line = (size1 + size2) / 2, k = 0;
    vector<int> nums3;
    if (size1 == 0 && size2 == 0) return 0;
    if (size1 && !size2) return nums1[size1 / 2];
    if (!size1 && size2) return nums2[size2 / 2];
    while (k <= line && i < size1 && j < size2) {
        if (nums1[i] < nums2[j]) {
            nums3.push_back(nums1[i]);
            i++;
        }
        else {
            nums3.push_back(nums2[j]);
            j++;
        }
        k++;
    }
    while (i < size1 && k <= line) {
        nums3.push_back(nums1[i]);
        i++;
        k++;
    }
    while (j < size2 && k <= line) {
        nums3.push_back(nums2[j]);
        j++;
        k++;
    }
    if ((size1 + size2) % 2) return nums3[line];
    else return ((double)nums3[line - 1] + (double)nums3[line]) / 2;
}

int main() {
    IntVec nums1 = { 1, 2 };
    IntVec nums2 = { 3, 4 };
    cout << findMedianSortedArrays(nums1, nums2);
    return 0;
}