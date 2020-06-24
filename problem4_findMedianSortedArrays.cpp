#include <iostream>
#include <vector>
using namespace std;

// 20ms 7.1MB 62.62% 100%
// 两个数组已经是升序排列, 在两数组情况下求这些数的中位数, 要求O(log(m+n))
// 见到log考虑二分查找, 难点在于两个数组分开如何进行二分
// 问题转化为求取两个数组中第k大的数
// 两边分别约定每次查找的起始索引, 以及当前查找第k大的k值
// 采用每次增加k/2的方式迫近结果, 并修改起始索引, 如果索引超过范围, 则在未超过的一方得到结果
// 如果如[1, 3],[2, 4] k=2 最终 k=1时, 两边都面对 k=1的情况, 选择小的一个
double getKLargestNum(vector<int>& nums1, int start1, vector<int>& nums2, int start2, int k)
{
    int m = nums1.size(), n = nums2.size();
    if (start1 >= m) return nums2[start2+k-1];
    if (start2 >= n) return nums1[start1+k-1];
    if (k == 1 && start1 < m && start2 < n) return std::min(nums1[start1], nums2[start2]);
    int nums1mid = start1+k/2-1 < m ? nums1[start1+k/2-1] : INT_MAX;
    int nums2mid = start2+k/2-1 < n ? nums2[start2+k/2-1] : INT_MAX;
    if (nums1mid < nums2mid)
        return getKLargestNum(nums1, start1+k/2, nums2, start2, k-k/2);
    else
        return getKLargestNum(nums1, start1, nums2, start2+k/2, k-k/2);
}

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
{
    int m = nums1.size(), n = nums2.size();
    // 巧妙的操作, 得以一致处理奇数和偶数的情况
    int k1 = (m+n+1) / 2;
    int k2 = (m+n+2) / 2;
    double rst1 = getKLargestNum(nums1, 0, nums2, 0, k1);
    double rst2 = getKLargestNum(nums1, 0, nums2, 0, k2);
    return (rst1 + rst2) / 2;
}

int main()
{
    // vector<int> nums1 = {1, 3};
    // vector<int> nums2 = {2};
    vector<int> nums1 = {1, 2};
    vector<int> nums2 = {3, 4};
    double rst = findMedianSortedArrays(nums1, nums2);
    cout << "result is: " << rst << endl;

    return 0;
}