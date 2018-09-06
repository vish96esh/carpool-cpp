#include<iostream>
#include<stdlib.h>
#include<limits.h>
#define LEN 8
using namespace std;

int adj[LEN][LEN] = {{0,6,-1,45,-1,-1,23,56},
{6,0,-1,-1,-1,13,34,-1},
{-1,-1,0,82,7,-1,-1,8},
{45,-1,82,0,12,-1,-1,19},
{-1,-1,7,12,0,12,17,-1},
{-1,13,-1,-1,12,0,27,-1},
{23,34,-1,-1,17,27,0,-1},
{56,-1,8,19,-1,-1,-1,0}};

int *s[2],*d[2];
int dist[LEN][2];
int n;

int min(int dist[LEN][2])
{
   int m = INT_MAX, min_index;
   for (int v = 0; v < LEN; v++)
     if (dist[v][1] == 0 && dist[v][0] <= m)
     {
        m = dist[v][0];
        min_index = v;
     }
   return min_index;
}

void dijkstra(int graph[LEN][LEN], int src)
{
     int i,u,j;
     for(i=0;i<LEN;i++)
     {
        dist[i][0]=INT_MAX;
        dist[i][1]=0;
     }
     dist[src][0]=0;
     for(i=0;i<LEN-1;i++)
     {
       u=min(dist);
       dist[u][1]=1;
       for(j=0;j<LEN;j++)
       {
         if(!dist[j][1] && graph[u][j]!=-1 && dist[u][0] != INT_MAX && dist[u][0]+graph[u][j] < dist[j][0])
            dist[j][0]=dist[u][0]+graph[u][j];
       }
     }
}

int calc_current_cust()
{
    int i,ctr=0;
    for(i=0;i<n;i++)
    {
        if(s[1][i]==1)
            ctr++;
    }
    return ctr;
}

int findMin(int dist[LEN][2],int *v[2],int n)
{
    int i,small=INT_MAX,pos;
    char key;
    int x=calc_current_cust();
    cout<<"CUST: "<<x<<endl;
    if(x==3)
        key='d';
    for(i=0;i<n;i++)
    {
        if(key=='d'&&v[1][i]==0)
                continue;
        if(dist[v[0][i]][0]<small)
        {
            small=dist[v[0][i]][0];
            pos=i;
        }
    }
    return pos;
}

int main()
{
    int i;
    cout<<"Enter n\n";
    cin>>n;
    s[0]=new int[n];
    s[1]=new int[n];
    d[0]=new int[n];
    d[1]=new int[n];
    for(i=0;i<n;i++)
    {
        cout<<"Customer "<<i+1<<":\n";
        cout<<"Enter source: ";
        cin>>s[0][i];
        s[1][i]=0;
        cout<<"Enter dest: ";
        cin>>d[0][i];
        d[1][i]=0;
    }
    int *v[2],u,ctr=0;
    v[0]=new int[n];
    v[1]=new int[n];
    int source=rand()%8+1;
    cout<<source<<endl;
    int *path,count=0;
    path=new int[(2*n)+1];
    path[count++]=source;
    do
    {
        ctr=0;
        for(i=0;i<n;i++)
        {
            if(s[1][i]==0)
            {
                v[0][ctr]=s[0][i];
                v[1][ctr++]=0;
            }
            else if(s[1][i]==1)
            {
                v[0][ctr]=d[0][i];
                v[1][ctr++]=1;
            }
        }
        if(ctr==0)
            break;
        dijkstra(adj,source);
        for(i=0;i<LEN;i++)
            cout<<dist[i][0]<<" ";
        cout<<endl;
        u=findMin(dist,v,ctr);
        cout<<u<<" "<<v[0][u]<<endl;
        path[count++]=v[0][u];
        if(v[1][u]==0)
            s[1][v[0][u]]=1;
        else
        {
            d[1][v[0][u]]=1;
            s[1][v[0][u]]=2;
        }
    }
    while(ctr!=0);
    for(i=0;i<count;i++)
        cout<<path[i]<<" ";
    return 0;
}

