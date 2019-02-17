#include<stdio.h>
#define W 165
struct arr
{
    int a;
    int b[10];
};
void adjust(int *a,int *wt)
{
    int i,j,k;
    /*if weight of knapsack is less then or equal to required weight then function will not do anything*/
    if(a[10]<=W)
        return;
    /*if weights are greater then the required weight then it will guess a random no. between 0 to 9
    and if there are any 1 if first five positions then it will do the position corresponds to guessed no. as 0
    or if there are 1 present in positions 6 to 10 then it will make position of guessed no. as 0.this process will be done
    until total weight goes below the required weight */
    else
    {
        i= rand()%5;
        if(a[0]==1||a[1]==1||a[2]==1||a[3]==1||a[4]==1)
        {
            if(a[i]==1)
            {
                a[i]=0;
            }
        }
        else
        {
            if(a[6]==1||a[6]==1||a[7]==1||a[8]==1||a[9]==1)
            {
                a[i+5]=0;
            }
        }

        a[10]=weights(a,wt);
        adjust(a,wt);
    }
}

/*function calculating the total value of knapsack*/
int fitness(int *a,int *val)
{
    int i,p=0;
    for(i=0; i<10; i++)
    {
        if(a[i]==1)
        {
            p=p+val[i];
        }
    }
    return p;
}

/*function calculating the total weight of knapsack*/
int weights(int *a,int *wt)
{
    int i,p=0;
    for(i=0; i<10; i++)
    {
        if(a[i]==1)
        {
            p=p+wt[i];
        }
    }
    return p;
}
/*swapping the pointers*/
void swap(struct arr *xp, struct arr *yp)
{
    struct arr temp = *xp;
    *xp = *yp;
    *yp = temp;
}


void sort(struct arr *b)
{
    int i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 3-i; j++)
            if (b[j].a > b[j+1].a)
                swap(&b[j], &b[j+1]);
}

int min(int a,int b,int c,int sol[100][13])
{
    if(sol[a][11]<=sol[b][11])
    {
        if(sol[a][11]<=sol[c][11])
            return 0;
        else
            return 2;
    }
    else
    {
        if(sol[b][11]<=sol[c][11])
            return 1;
        else
            return 2;
    }
}

void cross(int sol[100][13],int *wt,int *val,int p,int q)
{
    int a,b;
    int m[12],n[12],j=0,i;
    int k=rand()%10;
    if(k!=0)
    {
        while(j<=k)
        {
            m[j]=sol[p][j];
            n[j]=sol[q][j];
            j++;
        }
        while(j<10)
        {
            n[j]=sol[p][j];
            m[j]=sol[q][j];
            j++;
        }
    }
    m[10]=weights(m,wt);
    m[11]=fitness(m,val);
    if(m[10]>W)
        m[11]=0;
    n[10]=weights(n,wt);
    n[11]=fitness(n,val);
    if(n[10]>W)
        n[11]=0;
    struct arr c[4];
    c[0].a=m[11];
    c[1].a=n[11];
    c[2].a=sol[p][11];
    c[3].a=sol[q][11];
    for(i=0; i<10; i++)
    {
        c[0].b[i]=m[i];
        c[1].b[i]=n[i];
        c[2].b[i]=sol[p][i];
        c[3].b[i]=sol[q][i];
    }
    sort(c);
    int x,y;
    if(sol[p][12]==sol[p+1][12])
    {
        if(sol[p+1][12]==sol[p+2][12])
        {


            a=p;
            b=p+1;
            k=p+2;
            x=min(a,b,k,sol)+p;
        }
        else
        {
            a=p-1;
            b=p;
            k=p+1;
            x=min(a,b,k,sol)+p-1;
        }
    }
    else
    {
        a=p-2;
        b=p-1;
        k=p;
        x=min(a,b,k,sol)+p-2;
    }
    if(sol[q][12]==sol[q+1][12])
    {
        if(sol[q+1][12]==sol[q+2][12])
        {
            a=q;
            b=q+1;
            k=q+2;
            y=min(a,b,k,sol)+q;
        }
        else
        {
            a=q-1;
            b=q;
            k=q+1;
            y=min(a,b,k,sol)+q-1;
        }
    }
    else
    {
        a=q-2;
        b=q-1;
        k=q;
        y=min(a,b,k,sol)+q-2;
    }
    int z;
    if(x<y)
        z=x;
    else
        z=y;
    if(c[3].a==m[11]&&c[2].a==n[11])
    {
        for(int i=0; i<10; i++)
        {
            sol[x][i]=m[i];
            sol[y][i]=n[i];
        }
    }
    if(c[3].a==n[11]&&c[2].a==m[11])
    {
        for(int i=0; i<10; i++)
        {
            sol[x][i]=m[i];
            sol[y][i]=n[i];
        }
    }
    if(c[3].a==m[11]&&c[2].a!=n[11])
    {
        if(c[2].a==sol[x][11])
        {
            for(int i=0; i<10; i++)
            {
                sol[y][i]=n[i];
            }

        }
    }
    if(c[3].a==m[11]&&c[2].a!=n[11])
    {
        if(c[2].a==sol[y][11])
        {
            for(int i=0; i<10; i++)
            {
                sol[x][i]=n[i];
            }

        }
    }
    if(c[3].a==n[11]&&c[2].a!=m[11])
    {
        if(c[2].a==sol[x][11])
        {
            for(int i=0; i<10; i++)
            {
                sol[y][i]=n[i];
            }

        }
    }
    if(c[3].a==n[11]&&c[2].a!=m[11])
    {
        if(c[2].a==sol[y][11])
        {
            for(int i=0; i<10; i++)
            {
                sol[x][i]=n[i];
            }
        }
    }
    if(c[2].a==n[11]&&c[3].a!=m[11])
    {
        if(c[3].a==sol[x][11])
        {
            for(int i=0; i<10; i++)
            {
                sol[y][i]=n[i];
            }

        }
    }
    if(c[2].a==n[11]&&c[3].a!=m[11])
    {
        if(c[3].a==sol[y][11])
        {
            for(int i=0; i<10; i++)
            {
                sol[x][i]=n[i];
            }
        }
    }
    if(c[2].a==m[11]&&c[3].a!=n[11])
    {
        if(c[3].a==sol[x][11])
        {
            for(int i=0; i<10; i++)
            {
                sol[y][i]=n[i];
            }

        }
    }
    if(c[2].a==m[11]&&c[3].a!=n[11])
    {
        if(c[3].a==sol[y][11])
        {
            for(int i=0; i<10; i++)
            {
                sol[x][i]=n[i];
            }

        }
    }

}

/*finding maximum of the given three values*/
int max(int a,int b,int c)
{
    if(a>b)
    {
        if(a>c)
            return 0;
        else
            return 2;
    }
    else
    {
        if(b>c)
            return 1;
        else
            return 2;
    }
}

void evolution(int sol[100][13],int *wt,int *val,int row,int col)
{
    int p=0,q=0;
    int k=row/3;
    for(int i=0; i<96; i=i+6)
    {
        p=max(sol[i][11],sol[i+1][11],sol[i+2][11]);
        p=p+i;
        q=max(sol[i+3][11],sol[i+4][11],sol[i+5][11]);
        q=q+3+i;
        cross(sol,wt,val,p,q);
    }
}
void mutation1(int *a,int *val,int *wt)
{
    int b[10];
    for(int i=0; i<10; i++)
    {
        b[i]=a[i];
    }
    int m=rand()%5;
    int n=rand()%5;
    n=n+5;
    int k;
    if(b[m]!=b[n])
    {
        k=b[m];
        b[m]=b[n];
        b[n]=k;
    }
    int f=fitness(b,val);
    int w=weights(b,wt);
    if(w<W && w>a[10] )
    {
        for(int i=0; i<10; i++)
        {
            a[i]=b[i];
        }
    }
}
void mutation(int *a,int *val,int *wt )
{
    int b[10];
    for(int i=0; i<10; i++)
    {
        b[i]=a[i];
    }
    int k=rand()%10;
    int f=fitness(b,val);
    int w=weights(b,wt);
    if(w<W && w>a[10] )
    {
        for(int i=0; i<10; i++)
        {
            a[i]=b[i];
        }
    }
}




void main()
{
    /*
    rows are initalised as 100 because
    population we are assuming is 100 and
    col is initialised as 10 because
    no. of weights available is 10
    */
    int k,loop;
    int p,q;
    int row=100,col=10;
    int val1[col];
    int wt[10]= {23,31,29,44,53,38,63,85,89,82};
    int val[10]= {92,57,49,68,60,43,67,84,87,72};
    int sol[row][col+3];
    int max=0;

    /*Creating copy of values array*/
    for(loop = 0; loop < col; loop++)
    {
        val1[loop] = val[loop];
    }

    /*Initialising solution space as 0*/
    for(int i = 0; i<100; i++)
    {
        for(int j=0; j<10; j++)
        {
            sol[i][j]=0;
        }
    }

    /*filling with random ones in solution space to create some solutions initially*/
    for(int i = 0; i<100; i++)
    {
        for(int j=0; j<10; j++)
        {
            k= rand()%10;
            sol[i][k]=1;
        }
    }

    /* calculating value and weights corresponding to every solution*/
    for(int i=0; i<100; i++)
    {
        int p,q;
        p=fitness(sol[i],val);
        q=weights(sol[i],wt);
        sol[i][11]=p;
        sol[i][10]=q;

    }

    int m=row/3;
    int n=0;
    for(int i=0; i<row; i=i+3)
    {
        sol[i][col+2]=n;
        sol[i+1][col+2]=n;
        sol[i+2][col+2]=n;
        n++;
    }

    for(int i=0; i<row; i++)
    {
        adjust(sol[i],wt);/*if resultant weight exceeds the capacity of knapsack then
                            function will adjust the weight of knapsack such that
                            it should be less the weight of knapsack*/
    }

    /*updating value of knapsack corresponding to changes samples*/
    for(int i=0; i<row; i++)
    {
        int p;
        p=fitness(sol[i],val);
        sol[i][col+1]=p;
    }
    for(loop=0; loop<800; loop++)
    {
        evolution(sol,wt,val,row,col);
        for(int i=0; i<100; i++)
        {
            mutation(sol[i],val,wt);
        }

        for(int i=0; i<100; i++)
        {
            p=fitness(sol[i],val);
            q=weights(sol[i],wt);
            sol[i][10]=q;
            sol[i][11]=p;
        }
    }

    for(loop=0; loop<800; loop++)
    {
        evolution(sol,wt,val,row,col);
        for(int i=0; i<100; i++)
        {
            mutation(sol[i],val,wt);
            mutation1(sol[i],val,wt);
        }
        for(int i=0; i<100; i++)
        {
            p=fitness(sol[i],val);
            sol[i][11]=p;
            q=weights(sol[i],wt);
            sol[i][10]=q;
        }
    }
    for(loop=0; loop<row; loop++)
    {
        if(max<sol[loop][11])
        {
            max=sol[loop][11];
        }
    }
    printf("max optimized value=%d",max);
}
