//
//  main.cpp
//  Queenbee
//
//  Created by 王宇晨 on 2018/12/2.
//  Copyright © 2018 王宇晨. All rights reserved.
//

#include <iostream>
#include <cmath>
using namespace std;

struct Hex
{
    int  color =2;
    int  td = 0;
    //int  td_r1 = 1;
    //int  td_b0 = 1;
    //int  td_b1 = 1;
    bool count = 0;
};

//计算双距离
int TwoDistance()
{
    
    return 0;
}

//判断相邻,1相邻，2不相邻
bool neighbour(int a, int b, int c, int d)
{
    bool neighbour =0;
    if(a-c==-1)
    {
        if((b-d==-1)||(b-d==0))
        {
            neighbour =1;
        }
    }
    if(a-c==0)
    {
        if((b-d==-1)||(b-d==1))
        {
            neighbour =1;
        }
    }
    if(a-c==1)
    {
        if((b-d==-1)||(b-d==0))
        {
            neighbour =1;
        }
    }
    return neighbour;
}
//赋值1
void first(int color, int size, Hex **a)
{
    int Continue = 0;
    for(int i=0; i<size; i++)
    {
        int n= 0;
        int mn[25];
        if(a[i][0].color == 2)
        {
            a[i][0].td =1;
        }
        else
            if(a[i][0].color == color)
            {
                a[i][1].td= 1;
                if(i<size)
                {
                    a[i+1][0].td =1;
                }
                if(i-1>-1)
                {
                    a[i-1][0].td =1;
                    a[i-1][1].td =1;
                }
                mn[0] = i;
                //从第一列有棋子的点往深
                while(true)
                {
                    int time = 0;
                    for(int s = 0; s < Continue + 1; s++)
                    {
                        for(int x=0; x < i+1; x++)
                        {
                            if(neighbour(mn[s], n, x, n+1))
                            {
                                if(a[x][n+1].color == color)
                                {
                                    time += 1;
                                    if(time ==1)
                                    {
                                        mn[0] = x;
                                        a[x][n+2].td= 1;
                                        if(x+1<size)
                                        {
                                            a[x+1][n+1].td =1;
                                        }
                                        if(x-1>-1)
                                        {
                                            a[x-1][n+1].td =1;
                                            a[x-1][n+2].td =1;
                                        }
                                    }
                                    else
                                    {
                                        mn[time-1] = x;
                                        if(x+1<size)
                                        {
                                            a[x+1][n+1].td =1;
                                        }
                                        if(n+2<size)
                                        {
                                            a[x][n+2].td= 1;
                                        }
                                        //a[x][n+2].td= 1;
                                        //a[x+1][n+1].td =1;
                                    }
                                }
                            }
                        }
                        n += 1;
                    }
                    Continue = time;
                    if(time==0)
                    {
                        break;
                    }
                }
            }
    }
}

//遍历邻居棋子
void LookAround(int color, int size, Hex **a)
{
    //遍历邻居
    for(int i=0; i<size; i++)
    {
        for(int j=1;j<size;j++)
        {
            //申请动态数组
            bool **signal = new bool*[size];
            for(int i = 0; i < size; i++)
            {
                signal[i] = new bool [size];
            }
            //
            if(a[i][j].color==2)
            {
                
            }
            
            //删除动态数组
            for(int i=0; i<size;i++)
            {
                delete []signal[size];
            }
            delete []signal;
        }
    }
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
    board_size = 5;//读取棋盘大小
    Hex **origin = new Hex*[board_size];
    for(int i=0;i<board_size;i++)
    {
        origin[i] = new Hex[board_size];
    }
    
    int Max[2];
    Max[0]=-1;
    Max[1]=-1;
    
    //test
    origin[2][1].color =1;
    origin[2][0].color =1;
    origin[1][2].color =1;
    first(1, board_size, origin);
    
    for(int i=0;i<board_size;i++)
    {
        for(int j=0;j<board_size;j++)
        {
            if(origin[i][j].td == 1)
            {
                cout<<"("<<i<<","<<j<<")"<<endl;
            }
        }
    }
    return 0;
}
