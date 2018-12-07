//
//  main.cpp
//  Queenbee
//
//  Created by 王宇晨 on 2018/12/2.
//  Copyright © 2018 王宇晨. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
using namespace std;

struct Hex
{
    int  color =2;
    int  td = -1;
    int  td_r = -1;
    int  td_b = -1;
};


//判断相邻,1相邻，2不相邻
bool neighbour(int a, int b, int c, int d,int size)
{
    bool neighbour =0;
    if(b==0&&d==0)
    {
        neighbour=1;
    }
    if(b==size-1&&d==size-1)
    {
        neighbour=1;
    }
    if(a-c==-1)
    {
        if((b-d==0)||(b-d==1))
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
                            if(neighbour(mn[s], n, x, n+1,size))
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

//遍历一个格子邻接的所有格子
vector<int> LookAround(int value, vector<int> mmin, int size, int color, bool **signal,Hex **a,int i, int j)
{
    for(int n=j-1; n<j+1; n++)
    {
        for(int m=0;m<size;m++)
        {
            if(neighbour(i, j, m, n, size))
            {
                if(a[m][n].color==2)
                {
                    if(signal[m][n]==false)
                    {
                        signal[m][n]=true;
                        if(a[m][n].td != -1)
                        {
                            if(mmin[0] == -1)
                            {
                                mmin[0] = a[m][n].td;
                            }
                            else
                                if(a[m][n].td<mmin[0])
                                {
                                    mmin[1] = mmin[0];
                                    mmin[0] = a[m][n].td;
                                }
                                else
                                    if(a[m][n].td==mmin[0])
                                    {
                                        mmin[1] = mmin[0];
                                    }
                                    else
                                    {
                                        if(mmin[1]==-1||mmin[1]>a[m][n].td)
                                        {
                                            mmin[1] = a[m][n].td;
                                        }
                                    }
                        }
                    }
                }
                else
                    if((m!=i)||(n!=j))
                    {
                        if(a[m][n].color==color)
                        {
                            mmin = LookAround(value, mmin, size, color, signal, a, m, n);
                        }
                    }
            }
        }
    }
    return mmin;
}

//计算当前格子双距离
void Value(int color, int size, Hex **a)
{
    //遍历邻居
    for(int j=1;j<size; j++)
    {
        for(int i=0;i<size;i++)
        {
            int value = -1;
            vector<int> Miin(2,-1);
            //申请动态数组
            bool **signal = new bool*[size];
            for(int i = 0; i < size; i++)
            {
                signal[i] = new bool [size];
            }
            
            if(a[i][j].color==2)
            {
                Miin = LookAround(value, Miin, size, color, signal, a, i, j);
                if(Miin[1]==-1)
                {
                    a[i][j].td = -1;
                }
                else
                    a[i][j].td = Miin[1]+1;
                
            }
            
            //删除动态数组
            for(int i=0; i<size;i++)
            {
                delete[] signal[i];
            }
            delete[] signal;
        }
    }
}

//计算每一条边的双距离之前的坐标转换
//0:blue,1:red;
void ChangePosition(int size, Hex **h)
{
    //int color = 1;
    //红边初边
    //创建临时数组转换坐标
    Hex **temp = new Hex*[size];
    for(int i=0;i<size;i++)
    {
        temp[i] = new Hex[size];
    }
    first(1, size, h);
    Value(1, size, h);
    //红边对边
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            h[i][j].td_r = h[i][j].td;
            temp[size-1-i][size-1-j].color = h[i][j].color;
        }
    }
    first(1, size, temp);
    Value(1, size, temp);
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            h[i][j].td_r += temp[size-i-1][size-1-j].td;
        }
    }
    //删除临时数组
    for(int i=0; i<size;i++)
    {
        delete[] temp[i];
    }
    delete[] temp;
    
    //蓝边初边
    //创建临时数组转换坐标
    Hex **tempb = new Hex*[size];
    for(int i=0;i<size;i++)
    {
        tempb[i] = new Hex[size];
    }
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            tempb[j][i].color = h[i][j].color;
        }
    }
    first(0, size, tempb);
    Value(0, size, tempb);
    
    //蓝边对边
    Hex **tempbb = new Hex*[size];
    for(int i=0;i<size;i++)
    {
        tempbb[i] = new Hex[size];
    }
    //
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            h[i][j].td_b = tempb[j][i].td;
            tempbb[size-1-j][size-1-i].color = h[i][j].color;
        }
    }
    first(0, size, tempbb);
    Value(0, size, tempbb);
    //删除tempb临时数组
    for(int i=0; i<size;i++)
    {
        delete[] tempb[i];
        for(int j=0;j<size;j++)
        {
            h[i][j].td_b += tempbb[size-1-j][size-1-i].td;
        }
    }
    delete[] tempb;
    //删除临时数组
    for(int i=0; i<size;i++)
    {
        delete[] tempbb[i];
    }
    delete[] tempbb;
}


int main()
{
    string read;
    int thex;
    int they;
    int board_size;
    //读取棋盘大小
    board_size=5;
    //创建数组存取当前棋盘下的棋子并初始化color为2
    int **occupy = new int*[board_size];
    for(int i=0;i<board_size;i++)
    {
        occupy[i] = new int[board_size];
    }
    for(int i=0;i<board_size;i++)
    {
        for(int j=0; j<board_size;j++)
        {
            occupy[i][j] = 2;
        }
    }
    
    while(true)
    {
        //读取先手后手
        //？？？
        //读取棋子
        cin>>read;
        thex = (int)read[0]-65;
        if((int)read[2]!=0)
        {
            they = ((int)read[1]-48)*10+(int)read[2]-49;
        }
        else
        {
            they = (int)read[1]-49;
        }
        occupy[thex][they]=0;
        
        //创建当前棋盘状态
        Hex **origin = new Hex*[board_size];
        for(int i=0;i<board_size;i++)
        {
            origin[i] = new Hex[board_size];
        }
        //填入棋子
        for(int i=0;i<board_size;i++)
        {
            for(int j=0;j<board_size;j++)
            {
                origin[i][j].color = occupy[i][j];
            }
        }
        
        int *potential = new int[3];
        potential[0] = 99;
        //test
        ChangePosition(board_size, origin);
        for(int i=0;i<board_size;i++)
        {
            for(int j=0;j<board_size;j++)
            {
                if(origin[i][j].color == 2)
                {
                    if(potential[0]>origin[i][j].td_b+origin[i][j].td_r)
                    {
                        potential[0]=origin[i][j].td_b+origin[i][j].td_r;
                        potential[1]=i;
                        potential[2]=j;
                    }
                }
            }
        }
        //输出字符串
        cout<<(char)(potential[1]+65)<<","<<potential[2];
        thex = potential[1];
        they = potential[2];
        occupy[thex][they] = 1;
        delete[] potential;
        //删除当前棋盘状态
        for(int i=0; i<board_size;i++)
        {
            delete[] origin[i];
        }
        delete[] origin;
    }
    return 0;
}
