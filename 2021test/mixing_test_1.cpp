//
// Created by chenda on 2021/4/17.
//

#include <bits/stdc++.h>

using namespace std;

int main ()
{
//--------------------------------------------deque相关-------------------------------
/*
    std::deque<int> mydeque;

    mydeque.push_back (100);
    mydeque.push_back (200);
    mydeque.push_back (300);

    int s = mydeque.size();
    for (int i = 0; i < s; ++i) {
        std::cout << mydeque[i] << '\t';
    }
    std::cout << '\n';
    std::cout << '\n';

    mydeque.pop_front();

    s = mydeque.size();
    for (int i = 0; i < s; ++i) {
        std::cout << mydeque[i] << '\t';
    }

    std::cout << '\n';
    std::cout << '\n';

    int dd = 3;
    int ff = 4;
    double ii = (double)(dd / ff);
    std::cout << ii << std::endl;
    ii = (double)dd / ff;
    std::cout << ii << std::endl;
*/

//--------------------------------atan2测试-----------------------------------
/*
    double res = atan2(-0.5, 0.5 + 1.773996);
    res += 0.032789;
    res  = res * 180 / 3.14 * 14.5;
    cout << res << endl;

    res = atan2(0.5, 0.5 + 1.772380);
    res += 0.032981;
    res  = res * 180 / 3.14 * 14.5;
    cout << res << endl;
*/

//-------------------------------！取反符号测试-----------------------------
/*
    int n = 10;
    cout << !n << endl;
    cout << !!n << endl;
*/

//-----------------------------尝试一种无限循环的方式----------------------
    int times = 0;
    for (int i = 0; i < 10; ++i, i = i == 10? 0 : i) {
        if (times == 30) break;
        cout << i << endl;
        ++times;
    }


    return 0;
}