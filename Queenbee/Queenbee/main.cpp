//
//  main.cpp
//  Queenbee
//
//  Created by 王宇晨 on 2018/12/2.
//  Copyright © 2018 王宇晨. All rights reserved.
//

#include <iostream>
using namespace std;


struct Hex
{
    int  color =2;
    int  td_r0 = 1;
    int  td_r1 = 1;
    int  td_b0 = 1;
    int  td_b1 = 1;
};

//计算双距离
int TwoDistance()
{
    
    return 0;
}

//遍历邻居棋子
void LookAround(int size, Hex a[size][size])
{
    
}

//计算每一条边的双距离之前的坐标转换
//0:red,1:blue;
void ChangePosition(int a, int b, int size, Hex h[size][size], Hex temp[size][size])
{
    if(a == 0)
    {
        if(b == 1)
        {
            for(int i=0;i<size;i++)
            {
                for(int j=0;j<size;j++)
                {
                    temp[size-1-i][size-1-j] = h[i][j];
                }
            }
        }
    }
    else
    {
        if(b == 0)
        {
            for(int i=0;i<size;i++)
            {
                for(int j=0;j<size;j++)
                {
                    temp[j][i] = h[i][j];
                }
            }
        }
        else
        {
            for(int i=0;i<size;i++)
            {
                for(int j=0;j<size;j++)
                {
                    temp[size-1-j][size-1-i] = h[i][j];
                }
            }
        }
    }
}

//读取棋子
void readhex()
{
    int a[2];
    a[0]=1;
    a[1]=2;
}

int main()
{
    
    int board_size;
    cin>>board_size;//读取棋盘大小
    Hex hex[board_size][board_size];
    Hex hex_temp[board_size][board_size];
    //cout<<hex[0][1].color<<endl;
    
    return 0;
}
