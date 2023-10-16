//
//  main.cpp
//  homework2
//
//  Created by 宋昕乐 on 2023/10/15.
//

#include <iostream>
using namespace std;

int main()
    {
        int side;
        int i = 0;

        cout << "Enter a number: ";
        cin >> side;
    
        while (i < side)
        {
        int j = i;
        while (j >= 0)
        {
            cout << "#";
            j--;
        }
        cout << "\n";
        i++;
        }
    }

