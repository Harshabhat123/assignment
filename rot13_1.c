#include<stdio.h>
main()
{
    int no,i,j,temp=0,small=0,k,temp1=0,temp2=0,t;
    float avg=0.0,sum=0.0;
    printf("hi..fcfs pgm\n");
    printf("plz enter no of process:");
    scanf("%d",&no); 
    int b[no],w[no],b1[no],p[no];
    printf("\nenter time quantity");
    scanf("%d",&t);
    printf("plz enter burst time & priority of each process.. :)\n");
    for(i=0;i<no;i++)
    {
        printf("p%d:",i+1);
        scanf("%d",&b[i]);
        p[i]=i;
        b1[i]=b[i];
        w[i]=0;
    }
    
    for(i=0;i<no-1;i++)
    {
        small=i;
        for(j=i+1;j<no;j++)
        {
            if(b1[small]>b1[j])
                small=j;
        }
        temp=b1[small];
        b1[small]=b1[i];
        b1[i]=temp;
        temp1=p[small];
        p[small]=p[i];
        p[i]=temp1;
    }
    //printf("\n%d",p[no-1]);
    
 ff:for(i=0;i<no;i++)
    {
        if(b[i]!=0)
        {
            sum=0;
            if(b[i]<t)
            {
                sum=b[i];
                b[i]=0;
                
            }
            else
            {
                sum=t;
                b[i]=b[i]-t;
            }
            
        }
        for(j=0;j<no;j++)
        {
            if(j!=i&&b[j]>0)
            {
                w[j]=w[j]+sum;
            }
        }
    }
    if(b[p[no-1]]!=0)
        goto ff;
        
        for(i=0;i<no;i++)
            printf("%d\t",w[i]);
    /*for(i=0;i<no-1;i++)
    {
        small=i;
        for(j=i+1;j<no;j++)
        {
            if(p[small]>p[j])
                small=j;
        }
        temp=p[small];
        p[small]=p[i];
        p[i]=temp;
        
        temp1=b1[small];
        b1[small]=b1[i];
        b1[i]=temp1;
        
        temp2=b[small];
        b[small]=b[i];
        b[i]=temp2;
    }
    /*for(k=0;k<no;k++){
        printf("%d\t%d",b1[k],b[k]);
    printf("\n");}*/
    /*w[0]=0;
    for(i=1;i<no;i++)
    {
        w[i]=b[i-1]+w[i-1];
        sum=sum+w[i];
    }
    avg=sum/no;
    printf("burst\tprocess\tpriority\twaiting\n");
    for(i=0;i<no;i++)
    {
        printf("%d\t%d\t%d\t%d",b[i],b1[i]+1,p[i],w[i]);
        printf("\n");
    }
    printf("\navg w-t is %f",avg);*/

}