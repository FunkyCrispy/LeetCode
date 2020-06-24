#include <iostream>
#include <unordered_map>
using namespace std;


// 36ms, 8.8MB, 57.38%, 100%
// 滑动窗口方式求最大值
// 记录窗口起始位置, 如果出现重复位置在起始位置前就不算重复
// 如果重复出现在起始位置之后, 则减少当前记录的长度, 更改起始位置为重复位置之后一位
int lengthOfLongestSubstring(string s) {
    if (s.empty()) return 0;
    int maxlen = 1, i = 0, temp = 1;
    unordered_map<char, int> m;
    m[s[i]] = i;
    for (int j = i+1; j < s.length(); ++j)
    {
        if (m.find(s[j]) == m.end() || m[s[j]] < i)
        {
            ++temp;
            m[s[j]] = j;
            maxlen = std::max(maxlen, temp);
        }
        else
        {
            temp -= m[s[j]] - i;
            i = m[s[j]] + 1;
            m[s[j]] = j;
        }
    }
    return maxlen;
}

int main()
{
    string s = "tmmzuxt";
    int rst = lengthOfLongestSubstring(s);
    cout << "result is: " << rst << endl;

    return 0;
}