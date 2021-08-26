//
// Created by chenda on 2021/4/2.
//

/*题目描述：
 * 小明现在有一个长度为n的不递减数列，现在你可以操作任意次（>=0），每一次操作
 * 可以让某一个位置上的数增加1,但是每一个位置的数最多只能操作一次，现在想问你
 * 通过这个操作，能让新产生的序列中最多有多少个不同的数（重复的数算一个）*/

/*思路-1：
 * 使用hash_set，见如下方法，非常方便，但是此种方法没有利用非递减特性，*/

/*思路-2：
 * 使用快慢指针--主要需要注意两种特殊情况*/

#include <bits/stdc++.h>

int maxSpecies(int* ptr, int len) {
    if (!ptr || len <= 0) return 0;
    std::unordered_set<int> mySet;
    mySet.emplace(ptr[0]);
    for (int i = 1; i < len; ++i) {
        if (mySet.count(ptr[i]) > 0) {
            mySet.emplace(++ptr[i]);
        } else {
            mySet.emplace(ptr[i]);
        }
    }
    return mySet.size();
}

int maxSpecies_2(int* ptr, int len) {
    if (!ptr || len <= 0) return 0;
    int slow = 0, fast = 0, res = 1;
    while (fast < len -1) {
        ++fast;
        if (ptr[slow] == ptr[fast]) {
            continue;
        } else if (ptr[slow] == (ptr[fast] - 1)) {
            ++res;
            slow = fast;
        } else {
            ++res;
            if (fast - slow > 1) ++res;
            slow = fast;
        }
    }
    if (res == 1) return 2;//数组里面只包含一种值
    if (fast - slow > 0) ++res;//数组里面最后一个数值重复多次
    return res;
}

int main() {
    int n;
    std::cin >> n;
    int* nums = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> nums[i];
    }
    int res = maxSpecies_2(nums, n);
    std::cout << res << '\n';
    delete[] nums;
    return 0;
}

