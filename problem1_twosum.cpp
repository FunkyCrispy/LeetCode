


// （1）二重循环暴力法
// （2）先构建hashtable再查找
// （3）边构建hashtable边查找
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> m;
    for (int i= 0; i < nums.size(); ++i)
    {
        if (m.find(target-nums[i]) != m.end())
            return {m[target-nums[i]], i};
        else
            m[nums[i]] = i;
    }
    return {};
}