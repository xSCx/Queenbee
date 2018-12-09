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

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;

struct Hex
{
    //红色1，蓝色0
    int  color =2;
    int  td_r1 = 999;
    int  td_r2 = 999;
    int  td_b1 = 999;
    int  td_b2 = 999;
};

struct Dist
{
    int weight = 999;
    //int sweight = 999;
    bool wait = 1;
};



//判断相邻,true相邻，false不相邻
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

//计算两个格子间的距离
int weight(int color, int i, int j, int x, int y, int size, Hex **a)
{
    int weight = 999;
    if(neighbour(i,j,x,y,size))
    {
        if(a[x][y].color==2)
        {
            weight = 1;
        }
        else
            if(a[x][y].color == color)
            {
                weight=0;
            }
            else
            {
                weight=999;
            }
        
    }
    return weight;
}

//验证待查集是否为空
bool empty(Dist **d, int size)
{
    bool empty = true;
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            if(d[i][j].wait==1)
            {
                empty = false;
            }
        }
        
    }
    return empty;
}



//搜索到当前选定边的最短路径
int Dijkstra(int side, int color, int i, int j, int size, Hex **a)
{
    int value = 999;
    int svalue = 999;
    int min = 1000;
    int minx=0;
    int miny=0;
    Dist **dist = new Dist*[size];
    for(int m=0;m<size;m++)
    {
        dist[m] = new Dist[size];
    }
    dist[i][j].weight=0;
    //dist[i][j].sweight=1;
    
    while(!empty(dist, size))
    {
        //取出待查集中sweight最小的点
        for(int x=0;x<size;x++)
        {
            for(int y=0;y<size;y++)
            {
                if(dist[x][y].wait==true)
                {
                    if(dist[x][y].weight<min)
                    {
                        
                        min = dist[x][y].weight;
                        minx=x;
                        miny=y;
                    }
                }
            }
        }
        min = 1000;
        //
        dist[minx][miny].wait=false;
        for(int m=0;m<size;m++)
        {
            for(int n=0;n<size;n++)
            {
                //cout<<"debug"<<m<<","<<n<<endl;
                if((dist[minx][miny].weight+weight(color, minx, miny, m, n, size, a))<dist[m][n].weight)
                {
                    dist[m][n].weight=dist[minx][miny].weight+weight(color, minx, miny, m, n, size, a);
                }
                /*
                 else
                 if(!((dist[minx][miny].weight+weight(color, minx, miny, m, n, size, a))<dist[m][n].weight))
                 {
                 dist[m][n].sweight=dist[minx][miny].weight+weight(color, minx, miny, m, n, size, a);
                 }
                 */
            }
        }
    }
    
    //判断传送的双距离值
    if(color==1)
    {
        if(side ==1)
        {
            for(int x=0;x<size;x++)
            {
                if(dist[x][0].weight<value)
                {
                    value = dist[x][0].weight;
                }
                else
                    if(!(dist[x][0].weight>svalue))
                    {
                        svalue = dist[x][0].weight;
                    }
            }
        }
        else
        {
            for(int x=0;x<size;x++)
            {
                if(dist[x][size-1].weight<value)
                {
                    value = dist[x][size-1].weight;
                }
                else
                    if(!(dist[x][size-1].weight>svalue))
                    {
                        svalue = dist[x][size-1].weight;
                    }
            }
        }
    }
    else
    {
        if(side==1)
        {
            for(int x=0;x<size;x++)
            {
                if(dist[0][x].weight<value)
                {
                    value = dist[0][x].weight;
                }
                else
                    if(!(dist[0][x].weight>svalue))
                    {
                        svalue = dist[0][x].weight;
                    }
            }
        }
        else
        {
            for(int x=0;x<size;x++)
            {
                if(dist[size-1][x].weight<value)
                {
                    value = dist[size-1][x].weight;
                }
                else
                    if(!(dist[size-1][x].weight>svalue))
                    {
                        svalue = dist[size-1][x].weight;
                    }
            }
        }
    }
    
    
    //删除动态数组
    for(int m=0;m<size;m++)
    {
        delete[] dist[m];
    }
    delete[] dist;
    return  svalue+1;
}

void TwoDistance(int color, int size, Hex **a)
{
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            a[i][j].td_r1 = Dijkstra(1,1, i, j, size, a);
            a[i][j].td_r2 = Dijkstra(2,1, i, j, size, a);
            a[i][j].td_b1 = Dijkstra(1,0, i, j, size, a);
            a[i][j].td_b2 = Dijkstra(2,0, i, j, size, a);
        }
    }
}

int main()
{
    int thex,they,Thex,They;
    int color;
    int size;
    string p;
    cin>>p;
    cin>>size;
    string read;
    if(p=="RED")
    {
        color=1;
    }
    else
    {
        color=0;
    }
    
    
    int occupy[size][size];
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            occupy[i][j] = 2;
        }
    }
    //occupy[1][0]=1;
    //occupy[0][4]=0;
    
    
    //开始下棋
    if(color == 1)
    {
        while(true)
        {
            //创建当前棋盘状态
            Hex **origin = new Hex*[size];
            for(int i=0;i<size;i++)
            {
                origin[i] = new Hex[size];
            }
            
            //将读到的棋子填入棋盘
            for(int i=0;i<size;i++)
            {
                for(int j=0;j<size;j++)
                {
                    origin[i][j].color = occupy[i][j];
                    //cout<<"("<<i<<","<<j<<")"<<origin[i][j].color<<","<<occupy[i][j]<<endl;
                }
            }
            //创建动态数组记录最小值坐标和最小值
            int *potential = new int[3];
            potential[0] = 99;
            //计算双距离
            TwoDistance(color, size, origin);
            for(int i=0;i<size;i++)
            {
                for(int j=0;j<size;j++)
                {
                    if(origin[i][j].color == 2)
                    {
                        if(potential[0]>origin[i][j].td_r1+origin[i][j].td_r2)
                        {
                            potential[0]=origin[i][j].td_r1+origin[i][j].td_r2;
                            potential[1]=i;
                            potential[2]=j;
                            //cout<<"("<<i<<","<<j<<")"<<origin[i][j].color<<","<<occupy[i][j]<<","<<potential[0]<<endl;
                        }
                    }
                }
            }
            //输出棋
            cout<<(char)(potential[1]+65)<<potential[2]<<endl;
            thex = potential[1];
            they = potential[2];
            occupy[thex][they] = 1;
            
            //读取棋子
            cin>>read;
            Thex = (int)read[0]-65;
            if(read.size()==3)
            {
                They = ((int)read[1]-48)*10+(int)read[2]-48;
            }
            else
            {
                They = (int)read[1]-48;
            }
            occupy[Thex][They]=0;
            //cout<<"("<<Thex<<","<<They<<")"<<occupy[Thex][They]<<endl;
            
            //删除当前棋盘状态
            for(int i=0;i<size;i++)
            {
                delete[] origin[i];
            }
            delete[] origin;
            delete[] potential;
        }
    }
    else
    {
        while(true)
        {
            //读取棋子
            cin>>read;
            thex = (int)read[0]-65;
            if(read.size()==3)
            {
                they = ((int)read[1]-48)*10+(int)read[2]-48;
            }
            else
            {
                they = (int)read[1]-48;
            }
            occupy[thex][they]=1;
            
            //创建当前棋盘状态
            Hex **origin = new Hex*[size];
            for(int i=0;i<size;i++)
            {
                origin[i] = new Hex[size];
            }
            
            //将读到的棋子填入棋盘
            for(int i=0;i<size;i++)
            {
                for(int j=0;j<size;j++)
                {
                    origin[i][j].color = occupy[i][j];
                }
            }
            
            //创建动态数组记录最小值坐标和最小值
            int *potential = new int[3];
            potential[0] = 99;
            //计算双距离
            TwoDistance(color, size, origin);
            for(int i=0;i<size;i++)
            {
                for(int j=0;j<size;j++)
                {
                    if(origin[i][j].color == 2)
                    {
                        if(potential[0]>origin[i][j].td_b1+origin[i][j].td_b2)
                        {
                            potential[0]=origin[i][j].td_b1+origin[i][j].td_b2;
                            potential[1]=i;
                            potential[2]=j;
                            //cout<<"("<<i<<","<<j<<")"<<origin[i][j].color<<","<<occupy[i][j]<<","<<potential[0]<<endl;
                        }
                    }
                }
            }
            
            //输出棋
            cout<<(char)(potential[1]+65)<<potential[2]<<endl;
            thex = potential[1];
            they = potential[2];
            occupy[thex][they] = 0;
            
            //删除当前棋盘状态
            for(int i=0;i<size;i++)
            {
                delete[] origin[i];
            }
            delete[] origin;
            delete[] potential;
        }
    }
    
    /*
     
     //创建当前棋盘状态
     Hex **origin = new Hex*[size];
     for(int i=0;i<size;i++)
     {
     origin[i] = new Hex[size];
     }
     origin[1][2].color = 1;
     //将读到的棋子填入棋盘
     for(int i=0;i<size;i++)
     {
     for(int j=0;j<size;j++)
     {
     origin[i][j].color = occupy[i][j];
     }
     }
     
     TwoDistance(color, size, origin);
     
     for(int i=0;i<size;i++)
     {
     for(int j=0;j<size;j++)
     {
     if(origin[j][i].color==2)
     {
     cout<<"("<<j<<","<<i<<")"<<origin[j][i].td_r1+origin[j][i].td_r2<<endl;
     }
     }
     }
     
     
     
     
     */
    
    return 0;
}
