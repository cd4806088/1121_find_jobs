//
// Created by chenda on 2021/4/8.
//

#include <bits/stdc++.h>

using namespace std;

int main() {
/*    string str ("chendahanhan");
    const char* pstr = str.data();
    const char* pstr2 = str.c_str();
    cout << pstr << endl;
    cout << pstr2 << endl;
    cout << str[str.size()] << endl;
    */

/*
    std::multiset<int, std::greater<int>> buffer;
    for (int i = 0; i < 10; ++i) {
        buffer.emplace(i);
    }
    for (auto& val : buffer) {
        cout << val << endl;
    }
*/

    std::vector<int> v { 3, 1, 4, 1, 5, 9 };

    std::make_heap(v.begin(), v.end());

    std::cout << "v: ";
    for (auto i : v) std::cout << i << ' ';
    std::cout << '\n';

    v.push_back(6);

    std::cout << "before push_heap: ";
    for (auto i : v) std::cout << i << ' ';
    std::cout << '\n';
    std::push_heap(v.begin(), v.end());
    std::cout << "after push_heap: ";
    for (auto i : v) std::cout << i << ' ';
    std::cout << '\n';

    std::cout << "before pop_heap: ";
    for (auto i : v) std::cout << i << ' ';
    std::cout << '\n';
    std::pop_heap(v.begin(), v.end());
    std::cout << "after pop_heap: ";
    for (auto i : v) std::cout << i << ' ';
    std::cout << '\n';

    return 0;
}