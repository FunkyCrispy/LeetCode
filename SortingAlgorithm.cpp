#include <iostream>
#include <math.h>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;


// 选择排序(不稳定)
void SelectSorting(vector<int>& nums)
{
    for (int i = 0; i < nums.size()-1; ++i)
    {
        int index = i;
        for (int j = i+1; j < nums.size(); ++j)
        {
            if (nums[j] < nums[index])
                index = j;
        }
        std::swap(nums[i], nums[index]);
    }
}

// 插入排序
void InsertSorting(vector<int>& nums)
{
    for (int i = 1; i < nums.size(); ++i)
    {
        int value = nums[i], j = i - 1;
        for (; j >= 0 && nums[j] > value; --j)
            nums[j+1] = nums[j];
        nums[j+1] = value;
    }
}

// 冒泡排序
void BubbleSorting(vector<int>& nums)
{
    for (int i = 1; i < nums.size(); ++i)
    {
        for (int j = 0; j < nums.size()-i; ++j)
        {
            if (nums[j] > nums[j+1])
                std::swap(nums[j], nums[j+1]);
        }
    }
}

// 希尔排序
void ShellSorting(vector<int>& nums)
{
    for (int k = 4; k > 0; --k)
    {
        for (int i = 1; i < nums.size(); ++i)
        {
            int value = nums[i], j = i - k;
            for (; j >= 0 && nums[j] > value; j -= k)
                nums[j+k] = nums[j];
            nums[j+k] = value;
        }
    }
}

// 快速排序
int pivotDouble(vector<int>& nums, int low, int high)
{
    while (low < high)
    {
        while(low < high && nums[low] <= nums[high])
            --high;
        std::swap(nums[low], nums[high]);
        while(low < high && nums[low] <= nums[high])
            ++low;
        std::swap(nums[low], nums[high]);
    }
    return low;
}
int pivotSingle(vector<int>& nums, int low, int high)
{
    int idx = low;
    std::swap(nums[low], nums[high]);
    for (int i = low; i < high; ++i)
    {
        if (nums[i] <= nums[high])
            std::swap(nums[idx++], nums[i]);
    }
    std::swap(nums[idx], nums[high]);
    return idx;
}
void QuickHelp(vector<int>& nums, int low, int high)
{
    if (low < high)
    {
        // int mid = pivotDouble(nums, low, high);
        int mid = pivotSingle(nums, low, high);
        QuickHelp(nums, low, mid-1);
        QuickHelp(nums, mid+1, high);
    }
}
void QuickSorting(vector<int>& nums)
{
    QuickHelp(nums, 0, nums.size()-1);
}

// 堆排序
void HeapAdjust(vector<int>& nums, int low, int high)
{
    for (int i = low, f = 2*low + 1; f <= high; f = 2*f+1)
    {
        if (f < high && nums[f] < nums[f+1])
            ++f;
        if (nums[i] >= nums[f])
            break;
        std::swap(nums[i], nums[f]);
        i = f;
    }
}
void HeapSorting(vector<int>& nums)
{
    for (int i = (nums.size()-2)/2; i >= 0; --i)
        HeapAdjust(nums, i, nums.size()-1);
    for(int i = nums.size()-1; i > 0; --i)
    {
        std::swap(nums[i], nums[0]);
        HeapAdjust(nums, 0, i-1);
    }
}

// 归并排序
void Merge(vector<int>& nums, vector<int>& temp, int low, int high)
{
    int mid = (low + high) / 2;
    int idx = low, i = low, j = mid+1;
    while (i <= mid && j <= high)
    {
        if (nums[i] <= nums[j])
            temp[idx++] = nums[i++];
        else
            temp[idx++] = nums[j++];
    }
    while (i <= mid)
        temp[idx++] = nums[i++];
    while (j <= high)
        temp[idx++] = nums[j++];
    for (int i = low; i <= high; ++i)
        nums[i] = temp[i];
}
void MergeHelp(vector<int>& nums, vector<int>& temp, int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        MergeHelp(nums, temp, low, mid);
        MergeHelp(nums, temp, mid+1, high);
        Merge(nums, temp, low, high);
    }
}
void MergeSorting(vector<int>& nums)
{
    vector<int> temp(nums.size());
    MergeHelp(nums, temp, 0, nums.size());
}

// 归并排序原地算法
void MergeInplace(vector<int>& nums, int low, int high)
{
    int mid = (low + high)/2;
    int i = low, j = mid+1;
    int idx;
    while (i < j && j <= high)
    {
        idx = j;
        while (i < j && nums[i] <= nums[j])
            ++i;
        while (j <= high && nums[j] <= nums[i])
            ++j;
        std::reverse(nums.begin()+i, nums.begin()+idx);
        std::reverse(nums.begin()+idx, nums.begin()+j);
        std::reverse(nums.begin()+i, nums.begin()+j);
        i += j - idx;
    }
}
void MergeHelpInplace(vector<int>& nums, int low, int high)
{
    if (low < high)
    {
        int mid = (low + high)/2;
        MergeHelpInplace(nums, low, mid);
        MergeHelpInplace(nums, mid+1, high);
        MergeInplace(nums, low, high);
    }
}
void MergeSortingInplace(vector<int>& nums)
{
    MergeHelpInplace(nums, 0, nums.size()-1);
}

// 桶排序
void BucketSorting(vector<int>& nums)
{
    int minv = INT_MAX, maxv = INT_MIN;
    for (int n : nums)
    {
        minv = std::min(n, minv);
        maxv = std::max(n, maxv);
    }
    vector<int> bucket(maxv-minv+1);
    for (int n : nums)
        ++bucket[n-minv];
    int idx = 0, i = 0; 
    while (idx < maxv - minv + 1)
    {
        while (bucket[idx] > 0)
        {
            nums[i++] = idx + minv;
            --bucket[idx];
        }
        ++idx;
    }
}

// 基数排序
void RadixSorting(vector<int>& nums)
{
    vector<queue<int>> bucket(10);
    int maxv = INT_MIN, len = 0;
    for (int n : nums)
        maxv = std::max(maxv, n);
    while (maxv > 0)
    {
        maxv /= 10;
        ++len;
    }
    int lenidx = 1;
    while (lenidx <= len)
    {
        for (int n : nums)
        {
            int temp = n % (int)pow(10, lenidx) / (int)pow(10, lenidx-1);
            bucket[temp].push(n);
        }
        int idx = 0;
        for (int i = 0; i <= 9; ++i)
        {
            while (!bucket[i].empty())
            {
                nums[idx++] = bucket[i].front();
                bucket[i].pop();
            }
        }
        ++lenidx;
    }
}

void ShowResult(vector<int>& nums, string str)
{
    cout << str << " Result: ";
    for (int i = 0; i < nums.size(); ++i)
        cout << nums[i] << " ";
    cout << endl;
}

int main()
{
    vector<int> nums = {8, 56, 11, 12, 10, 5, 1, 21, 5, 6, 5};
    
    // 选择排序
    // SelectSorting(nums);
    // ShowResult(nums, "SelectSorting");

    // 插入排序
    // InsertSorting(nums);
    // ShowResult(nums, "InsertSorting");

    // 冒泡排序
    // BubbleSorting(nums);
    // ShowResult(nums, "BubbleSorting");

    // 希尔排序 ———— 插入排序对应的高级算法
    // ShellSorting(nums);
    // ShowResult(nums, "ShellSorting");

    // 快速排序 ———— 冒泡排序对应的高级算法
    // QuickSorting(nums);
    // ShowResult(nums, "QuickSorting");

    // 堆排序 ———— 选择排序对应的高级算法
    // HeapSorting(nums);
    // ShowResult(nums, "HeapSorting");

    // 归并排序
    // MergeSorting(nums);
    // ShowResult(nums, "MergeSorting");
    // MergeSortingInplace(nums);
    // ShowResult(nums, "MergeSortingInplace");

    // // 桶排序
    // BucketSorting(nums);
    // ShowResult(nums, "BucketSorting");

    // 基数排序
    // RadixSorting(nums);
    // ShowResult(nums, "RadixSorting");

    return 0;
}