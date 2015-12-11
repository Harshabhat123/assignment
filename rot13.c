
#include<stdio.h>
#include<fcntl.h>

void rot13(char c1,int fp1,int option,char c2)//byte and file descripter received to write to file
{
   int c,d,k,u,x,y,z,flag=0;
   int v=c1; //byte character ascii value
   char xx1,xx2,xx3,xx4;
   if(v>109&&v<123)//for a alphabets a-z (here 109 is 'm' & 122 is 'z'
   {           // for alphabets greator than 'm' (i.e, 13th character)
       d=122-v; //difference b/w 'z' and current byte character
       u=v-109; //difference b/w 'm' and current character
       k=v-d;   //in simple it is like finding diff b/w 'm' to current character
       xx1=k-u; //and adding it to 96 (i.e to start from 'a')
       size_t s2=sizeof(xx1);
       
       if(option==2)//if decrypting
       {
           if(xx1==c2)//check whether original character & decrypted r same
           {
               write(fp1,&xx1,s2);//writing a converted character to file
               flag=1;// to check whether character is alphabetical or not
           }
           else
           {
               printf("\nInvalid decryption..!!");
               return;
           }
       }
       else//if not decrypting
       {
           write(fp1,&xx1,s2);//writing a converted character to file
           flag=1;// to check whether character is alphabetical or not
       }
       
       
   }
   if(v>96&&v<110)//for characters 'a'-'m'
   {
       xx2=v+13;//add 13 
       size_t s4=sizeof(xx2);
       if(option==2)//if decrypting
       {
           if(xx2==c2)//check whether original character & decrypted r same
           {
               write(fp1,&xx2,s4);//writing a converted character to file
               flag=1;// to check whether character is alphabetical or not
           }
           else
           {
               printf("\nInvalid decryption..!!");
               return;
           }
       }
       else
       {
           write(fp1,&xx2,s4);//writing a converted character to file
           flag=1;// to check whether character is alphabetical or not
       }
   }
   
   if(v>64&&v<91)//for characters A-Z
   {
       if(v>77)// for character greator than 'M'
       {
           x=90-v;// as same as above
           y=v-77;
           z=v-x;
           xx3=z-y;
           size_t s3=sizeof(xx3);
           if(option==2)//if decrypting
       {
           if(xx3==c2)//check whether original character & decrypted r same
           {
               write(fp1,&xx3,s3);//writing a converted character to file
               flag=1;// to check whether character is alphabetical or not
           }
           else
           {
               printf("\nInvalid decryption..!!");
               return;
           }
       }
       else
       {
           write(fp1,&xx3,s3);//writing a converted character to file
           flag=1;// to check whether character is alphabetical or not
       }
       }
       else
       {
           xx4=v+13;//add 13
           size_t s5=sizeof(xx4);
           if(option==2)//if decrypting
       {
           if(xx4==c2)//check whether original character & decrypted r same
           {
               write(fp1,&xx4,s5);//writing a converted character to file
               flag=1;// to check whether character is alphabetical or not
           }
           else
           {
               printf("\nInvalid decryption..!!");
               return;
           }
       }
       else
       {
           write(fp1,&xx4,s5);//writing a converted character to file
           flag=1;// to check whether character is alphabetical or not
       }
       }
   }
   
   if(flag==0)//for characters other than alphabetics
   {
       if(option==2)//if decrypting
       {
           if(c1==c2)//check whether original character & decrypted r same
           {
               size_t s6=sizeof(c1);
               write(fp1,&c1,s6);
           }
           else
           {
               printf("\nInvalid decryption..!!");
               return;
           }
       }
       else//if not decrypting
       {
           size_t s6=sizeof(c1);
           write(fp1,&c1,s6);
       }
       
   }
}



void main(int argc,char *argv[])
{
    int fp,fp1,fp2,fp3,option;
    unsigned char c,c1;
    char file_name[15];
    if(argc!=2)
    {
        printf("\n Please enter path of file..!!\n");
        return;
    }
    
    fp=open(argv[1],O_RDONLY);//opening a file to read
    if(fp==-1)
    {
        printf("\nFile not exists..!!");
        return;
    }
    
    A:printf("\nEnter u r Option: 1)encrypt 2)Decrypt\n");
    scanf("\n%d",&option);
    if(option!=1&&option!=2)
    {
        printf("\ninvalid option..!!");
        goto A;//go back to correct input
    }
    
        if(option==1)//encryption
        {
            mode_t mode=S_IRUSR| S_IWUSR | S_IRGRP | S_IROTH;//encrypted data will be stored in "encrypt" file
            fp1=open("encrypt",O_CREAT|O_RDWR|O_APPEND|O_TRUNC,mode);//open "encrypt" file
            while(read(fp,&c,sizeof(c))>0)//loop to read each byte from file untill EOF
            {
                rot13(c,fp1,option,'a');//send each byte for encryption & last character is dummy(i.e, 'a')
            }                           //to match for actual syntax of function
            close(fp1);
            printf("\nSuccessfully encrypted..!\n");
        }
        else//decryption
        {
            printf("\nenter original file name:");
            scanf("%s",&file_name);
            
            fp3=open(file_name,O_RDONLY);//open original file
            if(fp3==-1)
            {
                printf("\nFile not exists..!!");
                return;
            }
            
            mode_t mode1=S_IRUSR| S_IWUSR | S_IRGRP | S_IROTH;//decrypted data will be stored in "decrypt" file
            fp2=open("decrypt",O_CREAT|O_RDWR|O_APPEND|O_TRUNC,mode1);//open decrypt file
            while(read(fp,&c,sizeof(c))>0&&read(fp3,&c1,sizeof(c1)>0))//loop to read each byte from file untill EOF
            {                                                       //even we r reading original file character
                rot13(c,fp2,option,c1);//send each byte for decryption with original file character
            }
            close(fp2);
            printf("\nSuccessfully decrypted..!\n");
        }

    close(fp);

}
