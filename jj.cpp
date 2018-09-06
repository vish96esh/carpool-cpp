#include<iostream>
using namespace std;
/////----------structure defnition/
struct minimum
{int v,p,roll,dis;
};
struct minimum *mo;
struct dis
{
int v,b,x;
};
struct dis *d,*d1;
///--------------global variables definition------------
int n,e,s,ct=0,p1,p2,p3,p4,p5,p6,lo;
int g[9][9] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
                      {4, 0, 8, 0, 0, 0, 0, 11, 0},
                      {0, 8, 0, 7, 0, 4, 0, 0, 2},
                      {0, 0, 7, 0, 9, 14, 0, 0, 0},
                      {0, 0, 0, 9, 0, 10, 0, 0, 0},
                      {0, 0, 4, 0, 10, 0, 2, 0, 0},
                      {0, 0, 0, 14, 0, 2, 0, 1, 6},
                      {8, 11, 0, 0, 0, 0, 1, 0, 7},
                      {0, 0, 2, 0, 0, 0, 6, 7, 0}
                     };
void printsol();
////--------------------to find minimum from d structre---------------
int mini()
{int mi=1000,md,i;
for(i=0;i<n;i++)
{if(d[i].b!=1 &&d[i].v<mi )
{mi=d[i].v;
md=i;
}
}
return md;
}

//-------------find minimum from d1 structure----------------------
int mini2()
{int mi=1000,md=0,i;
for(i=0;i<n;i++)
{if(d1[i].b!=1 &&d1[i].v<mi)
{mi=d1[i].v;
md=i;
}
}
return md;
}

//=====================to find minimum distance from point to another===============================
int diks(int start,int endp)
{
int i,j,u,p;
    for(i=0;i<n;i++)
    {
        d1[i].v=1000;
        d1[i].b=0;
    }
    d1[start].v=0;

    for(i=0;i<n-1;i++)
    {
    u=mini2();
        d1[u].b=1;
    for(j=0;j<n;j++)
    {
    if((d1[j].b!=1)  && g[u][j] && (d1[u].v!=1000) && (d1[u].v+g[u][j]<d1[j].v) &&!d1[j].x)
{d1[j].v=d1[u].v+g[u][j];
if(j==endp)
    p=d1[j].v;
}
}
}
return p;
}

//=====================to find minimum distance from point to another================================
void dik(int s)
{int i,u,j;
for(i=0;i<n-1;i++)
{
u=mini();
d[u].b=1;
for(j=0;j<n;j++)
{
    if((d[j].b!=1)  && g[u][j] && (d[u].v!=1000) && (d[u].v+g[u][j]<d[j].v) )
{d[j].v=d[u].v+g[u][j];
}
}
}
}

//===================to find three minimum among the chosen one================
void min3()
{
int c=0,i,p=-1,m=1000;
while(c<3)
{
    m=1000;
for(i=0;i<n;i++)
{
if(m>d[i].v &&(mo[0].v!=d[i].v) && (mo[1].v!=d[i].v)&&(mo[2].v!=d[i].v)&&i!=s && i!=e &&d[i].x!=1)
{m=d[i].v;
p=i;
}
}
mo[c].v=m;
mo[c].p=p;
c++;
}
}

//==================to find the last one to be visited among the three========================
int sol()
{
//=================to swape the contents================
       min3();
    int f=0,i,m=1000;

    for(i=0;i<3;i++)
    {
        if(m>diks(mo[i].p,e))
        {

            m=diks(mo[i].p,e);
        f=i;}
    }
    return f;
}
void swape(int c)
{
//================to find the distance of the selected three===================
    int t;
    if(c==1)
    {t=p1;
    p1=p2;
    p2=t;
    }
    if(c==2)
    {
        t=p1;
        p1=p5;
        p5=t;
    }


}
void dis3()
{
//===================checking the possibilities========================
        ct=diks(s,p1);
    mo[p3].dis=diks(p1,p2);
    mo[p4].dis=diks(p2,p5);
    mo[p6].dis=diks(p5,e);
    mo[p4].dis+=mo[p6].dis;
    mo[p3].dis+=mo[p4].dis;
    ct+=mo[p3].dis;
}
int  check()
{
   int a,b,c;
    a=b=c=0;
      if(diks(p1,e)+10>=mo[p3].dis)
    return 1;
    swape(1);
    a=mo[p3].dis;
    b=mo[p4].dis;
    c=mo[p6].dis;
    dis3();
       if(diks(p1,e)+10>=mo[p3].dis)
    return 1;
    mo[p3].dis=a;
    mo[p4].dis=b;
    mo[p6].dis=c;
        swape(1);
        ct=0;
             if(diks(p1,e)+10>=(diks(p1,p2)+diks(p2,e)))
        {
            ct=diks(s,p1);
            mo[p3].dis=diks(p1,p2);
            mo[p4].dis=diks(p2,e);
            ct+=mo[p4].dis;
            mo[p3].dis+=mo[p4].dis;
            a=ct;
            b=mo[p3].dis;
            c=mo[p4].dis;
        }
        if(diks(p1,e)+10>=(diks(p1,p5)+diks(p5,e)))
        {
            ct=diks(s,p1);
            mo[p3].dis=diks(p1,p5);
            mo[p6].dis=diks(p5,e);
            ct+=mo[p6].dis;
            mo[p3].dis+=mo[p6].dis;
            if(a>ct && a!=0)
            {
                ct=a;
                mo[p3].dis=b;
                mo[p4].dis=c;
                return 2;
            }
            else if(a<ct && a!=0)
                return 3;
        }
        swape(2);
               if(diks(p1,e)+10>=(diks(p1,p5)+diks(p5,e)))
        {
            ct=diks(s,p1);
            mo[p3].dis=diks(p1,p5);
            mo[p6].dis=diks(p5,e);
            ct+=mo[p6].dis;
            mo[p3].dis+=mo[p6].dis;
            if(a>ct && a!=0)
            {
                ct=a;
                mo[p3].dis=b;
                mo[p4].dis=c;
              return 2;
            }
            else if(a<ct && a!=0)
                return 3;
        }
        swape(2);

            swape(1);
            if(diks(p2,e)+10>=(diks(p2,p1)+diks(p1,e)))
        {
            ct=diks(s,p2);
            mo[p3].dis=diks(p2,p2);
            mo[p4].dis=diks(p2,e);
            ct+=mo[p4].dis;
            mo[p3].dis+=mo[p4].dis;
            a=ct;
            b=mo[p3].dis;
            c=mo[p4].dis;
                    }
        swape(1);
                 if(diks(p1,e)+10>=(diks(p1,p5)+diks(p5,e)))
        {
            ct=diks(s,p1);
            mo[p3].dis=diks(p1,p5);
            mo[p6].dis=diks(p5,e);
            ct+=mo[p6].dis;
            mo[p3].dis+=mo[p6].dis;
            if(a>ct && a!=0)
            {
                ct=a;
                mo[p3].dis=b;
                mo[p4].dis=c;
                return 2;
            }
            else if(a<ct && a!=0)
                return 3;
        }
        swape(2);
        if(diks(p1,e)+10>=(diks(p1,p5)+diks(p5,e)))
        {
            ct=diks(s,p1);
            mo[p3].dis=diks(p1,p5);
            mo[p6].dis=diks(p5,e);
            ct+=mo[p6].dis;
            mo[p3].dis+=mo[p6].dis;
            if(a>ct && a!=0)
            {
                ct=a;
                mo[p3].dis=b;
                mo[p4].dis=c;
                   return 2;
            }
            else if(a<ct && a!=0)
                return 3;
        }
        swape(2);
        return 0;

    }

    int fare()
    {
        int r=10,bf=80;
        double f1=0,f2=0,f3=0,f=0,ac=0,bc=0,cc=0,s=0;
        int a=check();
        if(a==1)
        {
           int  d1=mo[p3].dis-3;
            int d2=mo[p4].dis-3;
            int d3=mo[p6].dis-3;
            f1=bf+d1*r+1.2*d1;
            f2=bf+d2*r+1.2*d2;
            f3=bf+d3*r+1.2*d3;
            f=f1+f2+f3;
        int cr=mo[p3].dis-2;
        double t=1.5*cr;
       double fr=.5*t+cr*12+120;
        s=f-fr;
        ac=f1/f*s;
        bc=f2/f*s;
        cc=f3/f*s;
        int n2=(diks(mo[p3].p,e)+diks(mo[p4].p,e)+diks(mo[p6].p,e))*6;
        double ig=f-n2;
        int n1=ct*6;
      double ff=f1-ac+f2-bc+f3-cc-n1;
      if(ig-ff>0)
       {
        cout<<"first passenger fare individual   "<<f1<<"distance travelled by "<<mo[p3].dis<<endl;
        cout<<"second passenger fare individual   "<<f2<<"distance travelled by "<<mo[p4].dis<<endl;
        cout<<"third passenger fare individual  "<<f3<<"distance travelled by "<<mo[p6].dis<<endl;
        cout<<"fare "<<f<<endl;
        cout<<"final car pooling rate "<<endl;
        cout<<"first passenger fare individual  "<<f1-ac<<"distance travelled by "<<mo[p3].dis-3<<endl;
        cout<<"second passenger fare individual  "<<f2-bc<<"distance travelled by "<<mo[p4].dis-3<<endl;
        cout<<"third passenger fare individual  "<<f3-cc<<"distance travelled by "<<mo[p6].dis-3<<endl;
        cout<<"total fare "<<f1-ac+f2-bc+f3-cc<<endl;
        cout<<" company saved"<<ig-ff<<endl;
       return 1;
       }
       else
        return 0;
        }
        else if(a==2)
        {
           int d1=mo[p3].dis-3;
           int  d2=mo[p4].dis-3;
            f1=bf+d1*r+1.2*d1;
            f2=bf+d2*r+1.2*d2;
            f=f1+f2;
        int cr=mo[p3].dis-2;
        double t=1.5*cr;
       double fr=.5*t+cr*12+120;
       double s=f-fr;
       double ac=f1/f*s;
       double bc=f2/f*s;
       int n2=(diks(mo[p3].p,e)+diks(mo[p4].p,e))*6;
        double ig=f-n2;
        int n1=ct*6;
      double ff=f1-ac+f2-bc-n1;
      if(ig-ff>0)
        {cout<<"first passenger fare individual   "<<f1<<"distance travelled by "<<mo[p3].dis<<endl;
        cout<<"second passenger fare individual   "<<f2<<"distance travelled by "<<mo[p4].dis<<endl;
        cout<<"fare "<<fr<<" final car pooling rate for 2 passenger"<<endl;
        cout<<"first passenger fare individual  "<<f1-ac<<"distance travelled by "<<mo[p3].dis-3<<endl;
        cout<<"second passenger fare individual  "<<f2-bc<<"distance travelled by "<<mo[p4].dis-3<<endl;
         cout<<"total fare "<<f1-ac+f2-bc<<endl;
         cout<<"company saved "<<ig-ff<<endl;
        return 1;
        }
        else return 0;
        }
        else if(a==3)
        {
            int d1=mo[p3].dis-3;
           int  d2=mo[p6].dis-3;
            f1=bf+d1*r+1.2*d1;
            f2=bf+d2*r+1.2*d2;
            f=f1+f2;
        int cr=mo[p3].dis-2;
        double t=1.5*cr;
       double fr=.5*t+cr*12+120/2;
       double s=f-fr;
       double ac=f1/f*s;
       double bc=f2/f*s;
       int n2=(diks(mo[p3].p,e)+diks(mo[p6].p,e))*6;
        double ig=f-n2;
        int n1=ct*6;
      double ff=f1-ac+f2-bc-n1;
      if(ig-ff>0)
        {cout<<"first passenger fare individual   "<<f1<<"distance travelled by "<<mo[p3].dis<<endl;
        cout<<"second passenger fare individual   "<<f2<<"distance travelled by "<<mo[p6].dis<<endl;
        cout<<"fare "<<fr<<" final car pooling rate for 2 passenger"<<endl;
        cout<<"first passenger fare individual  "<<f1-ac<<"distance travelled by "<<mo[p3].dis-3<<endl;
        cout<<"second passenger fare individual  "<<f2-bc<<"distance travelled by "<<mo[p6].dis-3<<endl;
         cout<<"total fare "<<f1-ac+f2-bc<<endl;
          cout<<" company saved "<<ig-ff<<endl;
        return 1;
        }
        else return 0;
        }
        else
            cout<<"car pooling not available"<<endl;
            return 0;
           }

void distance()
{
    int f,k=1,i;
    f=sol();
    for(i=0;i<3;i++)
    {
        if(f==i)
            mo[i].roll=3;
        else
            mo[i].roll=k++;
    }
    k=1,ct=0;
    mo[0].dis=mo[1].dis=mo[2].dis=0;
    while(k<=3)
    {for(i=1;i<=3;i++)
    {
        if(mo[i-1].roll==k)
        {
            if(k==1)
         {
             ct+=diks(s,mo[i-1].p);
         p1=mo[i-1].p;
         p3=i-1;
         }
        else if(k==2)
        {
            mo[p3].dis=diks(p1,mo[i-1].p);
            ct+=mo[p3].dis;
            p2=mo[i-1].p;
            p4=i-1;
               }
        else
        {
            p5=mo[i-1].p;
            p6=i-1;
             mo[i-1].dis+=diks(mo[i-1].p,e);
            mo[p4].dis+=diks(p2,mo[i-1].p);
            mo[p4].dis+=mo[i-1].dis;
            mo[p3].dis+=mo[p4].dis;
            ct+=mo[p4].dis;
       }

    }
    }
    k++;
    }
    cout<<p1<<p2<<p5<<" "<<p3<<p4<<p6<<endl;

}
//=======to print the solution========================
void printsol()
{
int i,a,c,b;

a=check();
b=fare();
    if(a==1 && b)
    {
    for(i=0;i<3;i++)
    cout<<"distance travelled by "<<mo[i].p<<"is"<<mo[i].dis<<endl;
    cout<<"car travelled distance "<<ct<<endl;
    c=1;
    }
    else if(a==2 && b)
    {
        cout<<"distance travelled by first passenger "<<p1<<"is "<<mo[p3].dis<<endl;
        cout<<"distance travelled by second  passenger "<<p2<<"is "<<mo[p4].dis<<endl;
        cout<<"car travelled distance "<<ct<<endl;

    c=2;
    }
    else if(a==3 && b)
    {
        cout<<"distance travelled by first passenger "<<p1<<"is "<<mo[p3].dis<<endl;
        cout<<"distance travelled by second  passenger "<<p5<<"is "<<mo[p6].dis<<endl;
        cout<<"car travelled distance "<<ct<<endl;
    c=3;
    }
    else
      {
       cout<<"sharing not available"<<cout;

      }
      if(c==1)
      {
          d[p1].x=1;
          d[p2].x=1;
          d[p5].x=1;
            lo=lo-3;
      }
      else if(c==2)
      {
          d[p1].x=1;
          d[p2].x=1;
            lo-=2;
      }
      else if(c==3)
      {
          d[p1].x=1;
          d[p5].x=1;
          lo-=2;
      }
    }
int main()
{int i,ch=1;
n=9;
lo=n;
d=new dis[n];
d1=new dis[n];
mo=new struct minimum[3];
while(ch && lo>3)
{
cout<<"enter the starting point"<<endl;
cin>>s;
cout<<"enter the destination"<<endl;
cin>>e;

for(i=0;i<n;i++)
{

d1[i].v=1000;
d1[i].b=0;
 if(d[i].x!=1)
          {d[i].v=1000;
            d[i].b=0;
      }
      else
        d[i].b=1;
}
d[s].v=0;

dik(s);
distance();
ch=0;
printsol();
cout<<"enter your choice"<<endl;
cin>>ch;

}
return 0;
}

