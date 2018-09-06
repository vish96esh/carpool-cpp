#include <iostream>
#include <stdlib.h>
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

int minKey(int key[LEN], bool mstSet[LEN])
{
    int min = INT_MAX, min_index;
    for (int v = 0; v < LEN; v++)
    {
        if (mstSet[v] == false && key[v] < min)
        {
            min = key[v];
            min_index = v;
        }
    }
   return min_index;
}

void reconstruct(int parent[LEN], int key[LEN])
{
    int i,j;
    for(i=0;i<LEN;i++)
    {
        for(j=0;j<LEN;j++)
            adj[i][j]=-1;
    }
    for(i=0;i<LEN;i++)
        adj[i][i]=0;
    for(i=0;i<LEN;i++)
    {
        if(parent[i]==-1)
            continue;
        adj[i][parent[i]]=key[i];
        adj[parent[i]][i]=key[i];
    }
}

void prim(int graph[LEN][LEN])
{
     int parent[LEN];
     int key[LEN];
     bool mstSet[LEN];
     for (int i = 0; i < LEN; i++)
     {
        key[i] = INT_MAX;
        mstSet[i] = false;
     }
     key[0] = 0;
     parent[0] = -1;
     int i,j,u;
     for (i = 0; i < LEN-1; i++)
     {
        u = minKey(key, mstSet);
        mstSet[u] = true;
        for (j = 0; j < LEN; j++)
        {
            if (graph[u][j]!=-1 && mstSet[v] == false && graph[u][j] <  key[j])
            {
                parent[j]  = u;
                key[j] = graph[u][j];
            }
        }
     }
     reconstruct(parent,key);
}

int main()
{
    int n,i;
    int *s[2],*d[2];
    prim(adj);
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
    int *v,ctr=0;
    v=new int[n];
    int source=rand()%8+1;




    for(i=0;i<n;i++)
    {
        if(s[1][i]==0)
            v[ctr++]=s[0][i];
        else if(d[1][i]==0)
            v[ctr++]=d[0][i];
    }
    source=findMin(v,source);





}
