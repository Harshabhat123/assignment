//Bloom_Filter
//size of universal set is 20 i.e from 1-20
//subset & array size is 5
//hash function is no/4
#include<stdio.h>

int sub_set[5];
int a[5];

void input()
{
    int i,e,l,m,b;
    
    for(i=0;i<5;i++)
        a[i]=0;
        i=0;
        while(i<5)//generating random numbers to subset
        {
           m=0;
           l=rand()%19;
           for(b=0;b<5;b++)//to ensure that no is already nt in subset
           {
               if(l==sub_set[b])
                   m++;
           }
           if(m==0)//if generated no is new random no then matches
           {
             sub_set[i]=l;
             e=sub_set[i];
             a[e%4]=1;//insert 1 to array a by a hash fun 
             i++;
           }
        }
        printf("\nsubset:");
    for(i=0;i<5;i++)
        printf(" %d ",sub_set[i]);
        
        printf("\n");
        
        printf("\nArray:");
    for(i=0;i<5;i++)
        printf("%d ",a[i]);
        
        printf("\n");
}

int main()
{
    printf("Bloom Filter\nThis pgm takes i/p automatically with rand() function\n");
    printf("universal set elements are frm 1-20\n");
    int i,k,j,count,z;
    int xx=0;
    double abc;
    int universe[20];
    
    for(i=0;i<20;i++)// inserting value to universal set
        universe[i]=i;
        
        input();//call fun 2 get elements fr subset
        
    printf("\nFind elements in universal set\n");
    for(i=0;i<20;i++)//to check responsible no fr false result in subset
    {
        count=0;
        for(j=0;j<5;j++)//to check whether no is not in subset
        {
            if(universe[i]==sub_set[j])
                count++;
        }
            if(count==0)//no present only in universal set
          {
            k=universe[i]%4;
            if(a[k]==1)//if true false result
                {
                    printf("\n");
                    printf("\nfalse result 'present'.!!->%d",universe[i]);
                    for(z=0;z<5;z++)//find responsible no's in subset
                    {
                        if(sub_set[z]%4==k)
                            printf("\nResponsible element in sub-set is->%d",sub_set[z]);
                    }
                    xx++;
                }
          }
    }
    abc=xx/15.0;
    printf("\nFalse positive probability here is:%f\n",abc);
    return 0;
 }
