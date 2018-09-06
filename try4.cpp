#include<iostream>
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

typedef struct customer
{
    int id;
    int cost;
    int dis;
    int y;
    point *s;
    point *d;
}customer;

customer *pas;

class cab
{
    public:
        customer *cust[2];
        int top;
        int dis;
        int cd[2][2];
        cab()
        {
            top=-1;
            dis=0;
            /*cust[0]->y=0;
            cust[1]->y=0;
            cust[0]->dis=0;
            cust[1]->dis=0;
            cust[0]->cost=30;
            cust[1]->cost=30;*/
        }

        void push(customer *c)
        {
            if(top==1)
                return;
            top++;
            /*cust[top].cost=c.cost;
            cust[top].d=c.d;
            cust[top].dis=c.dis;
            cust[top].id=c.id;
            cust[top].s=c.s;
            cust[top].y=c.y;*/
            cust[top]=c;
        }

        void pop(customer *c)
        {
           int i;
           if(top==-1)
                return;
           for(i=0;i<top;i++)
           {
               if(cust[i]->id==c->id)
               {
                   if(cd[i][0]>pas[cust[i]->id].cost)
                    {
                        pas[cust[i]->id].cost=cd[i][0];
                        pas[cust[i]->id].dist=cd[i][1];
                    }
                   top--;
                   if(i==0)
                    {
                        /*cust[i].id=cust[i+1].id;
                        cust[i].cost=cust[i+1].cost;
                        cust[i].dis=cust[i+1].cost;
                        cust[i].y=cust[i+1].y;
                        cust[i].s=cust[i+1].s;
                        cust[i].d=cust[i+1].d;*/
                        cust[i]=cust[i+1];
                    }
                    break;
               }
           }
        }
};

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

void dijkstra(int graph[LEN][LEN], int src, int dist[LEN][2])
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
    int dist[LEN][2];
    dijkstra(adj,s->p,dist);
    return dist[d->p][0];
}

void calc_profit(int tdist)
{
    int cost_to_car;
    //cost_to_passenger[]
    int profit_by_car;
    int *profit_by_passenger;
    int sum=0;
    profit_by_passenger=new int[n];
    cost_to_car=((tdist-3)*11)+50
    for(i=0;i<n;i++)
    {
        sum+=pas[i].cost;
        profit_by_passenger[i]=((calc_dist(pas[i].s, pas[i].d)-3)*11 + 50)-pas[i].cost;
    }
    profit_by_car=sum-cost_to_car;
}

int move(point *s1, cab c, int count, point *S,dist[LEN][2])
{
    path[count]=s1;
    c.dis+=dist[s1->p][0];
    int z,i;
    point *s;
    s=new point[n];
    for(i=0;i<n;i++)
        s[i]=S[i];

    //calculating cost and distance for each customer
    for(i=0;i<=c.top;i++)
    {
        z=c.cust[i]->dis;
        c.cust[i]->dis+=dist[s1->p][0];
        if(c.cust[i]->dis>=calc_dist(c.cust[i]->s,c.cust[i]->d)+10)
            return -1;
        if(c.cust[i]->dis<=3)
            continue;
        if(c.cust[i]->y==0)
        {
            c.cust[i]->cost+=4.5*(2-(c.top+1))*(dist[s1->p][0]-(3-z);
            c.cust[i]->y=1;
        }
        else
            c.cust[i]->cost+=4.5*(2-(c.top+1))*dist[s1->p][0];
    }

    //picking or dropping a passenger
    if(s1->type=='s')
    {
        c.push(pas[s1->index]);
        s[s1->index].visit=1;
    }
    else
    {
        c.pop(pas[s1->index]);
        s[s1->index].visit=2;
    }

    //calculating points where the cab can visit next
    point **v;
    v=new point*[n];
    int ctr=0;
    for(i=0;i<n;i++)
    {
        if(s[i].visit==0)
            v[ctr++]=&s[i];
        else if(s[i].visit==1)
            v[ctr++]=&d[i];
    }
    //if all the points are covered
    if(ctr==0)
        return calc_profit();
    int dist1[LEN][2];
    dijkstra(adj,s1,dist1);
    int pos, small=INT_MAX;

    if(c.top==-1)
    {
        //if cab is empty, htne go to the nearest customer
        for(i=0;i<ctr;i++)
        {
            if(dist1[v[i]->p][0]<small)
            {
                small=dist1[v[i]->p][0];
                pos=i;
            }
        }
        return move(c,v[pos],count+1,dist1)
    }

    else if(c.top==0)
    {
        //if only one passenger in the cab
        int cost,big=0;
        for(i=0;i<ctr;i++)
        {
            cost=move(c,v[i],count+1,dist1);
            if(cost>big)
            {
                big=cost;
                pos=i;
            }
        }
        return move(c,v[pos],count+1,dist1);
    }

    else
    {
        int cost,big=0;
        for(i=0;i<ctr;i++)
        {
            if(v[i]->type=='s')
                continue;
            cost=move(c,v[i],count+1,dist1);
            if(cost>big)
            {
                big=cost;
                pos=i;
            }
        }
    }
}

int main()
{

    int source=rand()%V;
    int small=INT_MAX,pos;
    for(i=0;i<n;i++)
        v[ctr++]=&s[i];
    dijkstra(adj,source);
    for(i=0;i<ctr;i++)
    {
        if(dist[v[i]->p]<small)
        {
            small=dist[v[i]->p];
            pos=i;
        }
    }
    //s[v[pos]->index].visit=1;
    move(v[pos]);

}
