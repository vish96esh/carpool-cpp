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

int n;

typedef struct point
{
    int p;
    int index;
    char type;
}point;

point **path;

typedef struct customer
{
    int id;
    int cost;
    int dis;
    //int y;
    //int status;
    point s;
    point d;
}customer;

customer *pas;

class cab
{
    public:
        customer *cust[2];
        int top;
        int dis;

        cab()
        {
            top=-1;
            dis=0;
        }

        void push(customer *c)
        {
            if(top==1)
                return;
            top++;
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
                   top--;
                   if(i==0)
                        cust[i]=cust[i+1];
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

void dijkstra(int src, int dist[LEN][2])
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
         if(!dist[j][1] && adj[u][j]!=-1 && dist[u][0] != INT_MAX && dist[u][0]+adj[u][j] < dist[j][0])
            dist[j][0]=dist[u][0]+adj[u][j];
       }
     }
}

int calc_dist(point *s, point *d)
{
    int dist[LEN][2];
    dijkstra(s->p,dist);
    return dist[d->p][0];
}

int calc_profit(cab *c)
{
    int cost_by_car=50+(c->dis-3)*11;
    int *profit_by_pas;
    profit_by_pas=new int[n];
    int i,sum1=0,sum2=0;
    for(i=0;i<n;i++)
    {
        profit_by_pas[i]=(50+(calc_dist(pas[i]->s,pas[i]->d)-3)*11)-amt[i];
        sum1+=pas[i]->cost;
        sum2+=amt[i];
    }
    if(sum2>sum1)
    {
        for(i=0;i<n;i++)
            pas[i]->cost=amt[i];
    }
    return cost_by_car-sum2;
}

int move(point *s,int count, cab c,dist[LEN][2],int *sts, int flag)
{
    int i,*status;
    status=new int[n];
    for(i=0;i<n;i++)
        status[i]=*(sts+i);
    if(flag==1)
    {
        path[count]=s;
        c.dis+=dist[s->p][0];

        int z,rate;
        switch(c.top)
        {
            case 0:rate=9;
                break;
            case 1:rate=6;
                break;
        }

        for(i=0;i<=c.top;i++)
        {
            z=c.cust[i]->dis;
            c.cust[i]->dis+=dist[s->p][0];
            if(c.cd[i][1]>=calc_dist(c.cust[i]->s,c.cust[i]->d)+10)
                return -1;
        if(c.cd[i][1]<=3)
            continue;
        if(c.cd[i][2]==0)
        {
            c.cd[i][0]+=rate*(dist[s1->p][0]-(3-z));
            c.cd[i][2]=1;
        }
        else
            c.cd[i][0]+=rate*dist[s1->p][0];
    }

    if(s->type=='s')
    {
        c.push(&pas[s->index]);
        status[s->index]=1;
    }
    else
    {
        c.pop(&pas[s->index]);
        status[s->index]=2;
    }

    //calculating points where the cab can visit next
    point **v;
    v=new point*[n];
    int ctr=0;
    for(i=0;i<n;i++)
    {
        if(status[i]==0)
            v[ctr++]=&pas[i]->s;
        else if(status[i]==1)
            v[ctr++]=&pas[i]->d;
    }

    //if all the points are covered
    if(ctr==0)
        return calc_profit(&c);

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
        return move(v[pos],count+1,c,dist1,status,1)
    }

    else
    {
        //if only one passenger in the cab
        int cost,big=0;
        for(i=0;i<ctr;i++)
        {
            if(c.top==1 && v[i]->type=='s')
                continue;
            cost=move(v[i],count+1,c,dist1,status,0);
            if(cost>big)
            {
                big=cost;
                pos=i;
            }
        }
        return move(v[pos],count+1,c,dist1,status,1);
    }
}

int main()
{
    cab c;
    cout<<"Enter the no. of passengers: ";
    cin>>n;
    pas=new int[n];
    path=new point*[2*n];
    int *status;
    status=new int[n];
    cout<<"Enter the source and destination of the passengers:\n\n";
    int i;
    for(i=0;i<n;i++)
    {
        cout<<"Passenger "<<i+1<<"=>\nSource: ";
        cin>>pas[i]->s.p;
        pas[i]->s.type='s';
        pas[i]->s.index=i;
        cout<<"Dest: ";
        cin>>pas[i]->d.p;
        pas[i]->d.type='d';
        pas[i]->d.index=i;
        pas[i]->id=i;
        pas[i]->cost=pas[i]->dis=pas[i]->y=status[i]=0;
    }
    int src=rand()%LEN;
    int dist[LEN][2];
    dijkstra(src,dist);
    int small=INT_MAX,pos;
    for(i=0;i<n;i++)
    {
        if(dist[pas[i]->s.p][0]<small)
        {
            small=dist[pas[i]->s.p][0];
            pos=i;
        }
    }
    int x=move(&pas[pos]->s,0,c,dist,status);
    cout<<
}

