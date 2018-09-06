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

int dist[LEN][2];
int n;

typedef struct point
{
    int p;
    int visit;
    int index;
    char type;
}point;

point *s,*d;

class car
{
    public:
        point *pas[2];
        int top
        void push(point *p)
        {
            if(top==1)
                return;
            top++;
            pas[top]=p;
        }
}

//car c;



int min(int dist[LEN][2])
{
   int m = INT_MAX, min_index;
   for (int v = 0; v < LEN; v++)
   {
     if (dist[v][1] == 0 && dist[v][0] <= m)
     {
        m = dist[v][0];
        min_index = v;
     }
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

int calc_dist(point *s, point *d)
{
    dijkstra(adj,s->p);
    return dist[d->p];
}

int calc_fare(int d)
{
    if(d<=3)
        return 50;
    else
        return 50+((d-3)*11);
}

point *arr[4];

int bfs(int s1, int d1, int n, int d)
{

}


int move(int d)
{
    int i,sum=0;
    for(i=0;i<3;i++)
    {
        x=func(arr[i],arr[i+1]);
        if(x==-1)
            return -1;
        sum+=x;
    }
    return sum;
}

int max_cost(point *s1, point *d1, point *s2, point *d2)
{
    dist1=calc_dist(s1,d1);
    dist2=calc_dist(s2,d2);
    x1=calc_fare(dist1);
    x2=calc_fare(dist2);
    arr[0]=s1;
    arr[1]=s2;
    arr[2]=d1;
    arr[3]=d2;
    x3=bfs(s1->p,d1->p,3,dist1);
    arr[0]=s1;
    arr[1]=s2;
    arr[2]=d2;
    arr[3]=d1;
    x4=bfs(s1->p,d1->p,4,dist1);
    /*arr[0]=s2->p;
    arr[1]=d1->p;
    arr[2]=d2->p;
    x5=bfs(s2->p,d2->p,3,dist2);
    */
    if(x3!=-1 && x3<=x1+5)
    {

    }

}

int findMin(int dist[LEN][2],point **v,int n)
{
    int i,small=INT_MAX,pos,temp,big=0;
    point *s1,*s2,*d1,*d2;
    //int x=calc_current_cust();
    cout<<"CUST: "<<c.top+1<<endl;
    for(i=0;i<n;i++)
    {
        if(c.top==-1)
        {
            //if car is empty then the car goes to the point which is closest to it.
            if(dist[v[i]->p]<small)
            {
                small=dist[v[i]->p];
                pos=i;
            }
        }

        else if(c.top==1)
        {
            //if car is full then the car goes to that drop off point which has the maximum profit
            if(v[i]->p==d[c.pas[c.top]->index]->p)
            {
                pos=i;
                break;
            }
        }

        else
        {
            /*if only one customer in the car, then algorithm decides which customer is to be picked next for maximum profit
            (if it can given the limitation that a customer can be de-routed for only 5 extra kms), else drops off that passenger*/
            if(v[i]->type=='s')
            {
                s1=c.pas[c.top];
                s2=v[i];
                d1=d[c.pas[c.top]->index];
                d2=d[v[i]->index];
                cost=max_cost(s1,d1,s2,d2);
                if(cost==-1)
                    continue;
                if(cost>big)
                {
                    big=cost;
                    pos=i;
                }
            }
            else
            {
                if(d[c.pas[c.top]->index]->p==v[i]->p)
                    temp=i;
            }
        }
    }
    if(c.top==0 && big==0)
        return temp;
    return pos;
}

/*
int calc_dist(int s, int d)
{
    dijkstra(adj,s);
    return dist[d][0];
}
*/

void findMin(car c, point *p, point *s, point *d)
{
    int i,ctr=0;
    point **v;
    v=new point*[n];
    for(i=0;i<n;i++)
    {
        if(s[i].visit==0)
            v[ctr++]=&s[i];
        else if(s[i].visit==1)
            v[ctr++]=&d[i];
    }
    for(i=0;i<ctr;i++)
    {

    }
}

int main()
{
    car c;
    c.top=-1;    //initially the car is empty
    int i;
    cout<<"Enter n\n";
    cin>>n;
    s=new point[n];
    d=new point[n];
    for(i=0;i<n;i++)
    {
        cout<<"Customer "<<i+1<<":\n";
        cout<<"Enter source: ";
        cin>>s[i].p;
        s[i].visit=0;
        s[i].type='s';
        s[i].index=i;
        cout<<"Enter dest: ";
        cin>>d[i].p;
        d[i].visit=0;
        d[i].type='d';
        d[i].index=i;
        //diff[i]=calc_dist(s[i],d[i]);
    }
    point **v;
    int u,ctr=0;
    //cout<<"TEST"<<endl;
    v=new point*[n];
    //cout<<"TEST"<<endl;
    int source=rand()%8+1;
    dijkstra(adj,source);
    //cout<<source<<endl;
    point **path,count=0;
    path=new point*[(2*n)+1];
    //path[count++]=source;
    ctr=0;
    /*for(i=0;i<n;i++)
    {
        if(s[i].visit==0)
            v[ctr++]=&s[i];
        else if(s[i].visit==1)
            v[ctr++]=&d[i];
    }*/
    for(i=0;i<n;i++)
        v[ctr++]=&s[i];
    cout<<"V:\n";
        //if(ctr==0)
        //break;
    for(i=0;i<ctr;i++)
        cout<<v[i]->p<<" ";
    int pos,small=INT_MAX;
    for(i=0;i<ctr;i++)
    {
        if(dist[v[i]->p]<small)
        {
            small=dist[v[i]->p];
            pos=i;
        }
    }
    s[v[pos]->index].visit=1;
    c.push(v[pos]);
    findMin(c,v[pos])










        //dijkstra(adj,source);
        //cout<<"Dijkstra:\n";
        //for(i=0;i<LEN;i++)
          //  cout<<dist[i][0]<<" ";
        //cout<<endl;
        //u=findMin(v,ctr);




        cout<<u<<" "<<v[u]->p<<endl;
        path[count++]=v[u]->p;
        v[u]->visit=1;
        if(v[u]->type=='d')
        {
            c.top--;
            s[v[u]->index].visit=2;
        }
        else
        {
            s[v[u]->index].visit=1;
            c.top++;
            c.pas[c.top]=v[u];
        }
        source=v[u]->p;
    }
    while(ctr!=0);
    for(i=0;i<count;i++)
        cout<<path[i]<<" ";
    return 0;
}


