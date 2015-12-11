
#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>

/*byte and file descripter received to write to file*/
void rot13_encrypt(char c1,int fp1)
{
   int c,d,k,u,x,y,z,flag=0;
   /*byte character ascii value*/
   int v=c1; 
   char xx1,xx2,xx3,xx4;
   /*for a alphabets a-z (here 109 is 'm' & 122 is 'z'
    for alphabets greator than 'm' (i.e, 13th character)*/
   if(v>109&&v<123)
   {           
       /*difference b/w 'z' and current byte character*/
       d=122-v; 
       /*difference b/w 'm' and current character*/
       u=v-109; 
       /*in simple it is like finding diff b/w 'm' to current character*/
       k=v-d;
       /*and adding it to 96 (i.e to start from 'a')*/
       xx1=k-u; 
       size_t s2=sizeof(xx1);
       
           /*writing a converted character to file*/
           write(fp1,&xx1,s2);
           /* to check whether character is alphabetical or not*/
           flag=1;
       
   }
   /*for characters 'a'-'m'*/
   if(v>96&&v<110)
   {
       /*add 13 */
       xx2=v+13;
       size_t s4=sizeof(xx2);
       
           /*writing a converted character to file*/
           write(fp1,&xx2,s4);
           /* to check whether character is alphabetical or not*/
           flag=1;
   }
   /*for characters A-Z*/
   if(v>64&&v<91)
   {
       /* for character greator than 'M'*/
       if(v>77)
       {
           /* as same as above*/
           x=90-v;
           y=v-77;
           z=v-x;
           xx3=z-y;
           size_t s3=sizeof(xx3);
        
           /*writing a converted character to file*/
           write(fp1,&xx3,s3);
           /* to check whether character is alphabetical or not*/
           flag=1;
       }
       else
       {
           /*add 13*/
           xx4=v+13;
           size_t s5=sizeof(xx4);
           
           /*writing a converted character to file*/
           write(fp1,&xx4,s5);
           /* to check whether character is alphabetical or not*/
           flag=1;
       
       }
   }
   
   /*for characters other than alphabetics*/
   if(flag==0)
   {
           size_t s6=sizeof(c1);
           write(fp1,&c1,s6);
       
   }
}



void rot13_decrypt(char c1,int fp1,char c2)
{
   int c,d,k,u,x,y,z,flag=0;
   /*byte character ascii value*/
   int v=c1; 
   char xx1,xx2,xx3,xx4;
   /*for a alphabets a-z (here 109 is 'm' & 122 is 'z'
    for alphabets greator than 'm' (i.e, 13th character)*/
   if(v>109&&v<123)
   {           
       /*difference b/w 'z' and current byte character*/
       d=122-v; 
       /*difference b/w 'm' and current character*/
       u=v-109; 
       /*in simple it is like finding diff b/w 'm' to current character*/
       k=v-d;
       /*and adding it to 96 (i.e to start from 'a')*/
       xx1=k-u; 
       size_t s2=sizeof(xx1);
       
           /*check whether original character & decrypted r same*/
           if(xx1==c2)
           {
               /*writing a converted character to file*/
               write(fp1,&xx1,s2);
               /*to check whether character is alphabetical or not*/
               flag=1;
           }
           else
           {
               printf("\nInvalid decryption..!!");
               return;
           }
       
   }
   /*for characters 'a'-'m'*/
   if(v>96&&v<110)
   {
       /*add 13 */
       xx2=v+13;
       size_t s4=sizeof(xx2);
       
           /*check whether original character & decrypted r same*/
           if(xx2==c2)
           {
               /*writing a converted character to file*/
               write(fp1,&xx2,s4);
               /* to check whether character is alphabetical or not*/
               flag=1;
           }
           else
           {
               printf("\nInvalid decryption..!!");
               return;
           }
           
   }
   /*for characters A-Z*/
   if(v>64&&v<91)
   {
       /* for character greator than 'M'*/
       if(v>77)
       {
           /* as same as above*/
           x=90-v;
           y=v-77;
           z=v-x;
           xx3=z-y;
           size_t s3=sizeof(xx3);
           
           /*check whether original character & decrypted r same*/
           if(xx3==c2)
           {
               /*writing a converted character to file*/
               write(fp1,&xx3,s3);
               /* to check whether character is alphabetical or not*/
               flag=1;
           }
           else
           {
               printf("\nInvalid decryption..!!");
               return;
           }
       
       }
       else
       {
           /*add 13*/
           xx4=v+13;
           size_t s5=sizeof(xx4);
         
           /*check whether original character & decrypted r same*/
           if(xx4==c2)
           {
               /*writing a converted character to file*/
               write(fp1,&xx4,s5);
               /* to check whether character is alphabetical or not*/
               flag=1;
           }
           else
           {
               printf("\nInvalid decryption..!!");
               return;
           }
       
       }
   }
   
   /*for characters other than alphabetics*/
   if(flag==0)
   {
      
           /*check whether original character & decrypted r same*/
           if(c1==c2)
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
}



void main(int argc,char *argv[])
{
    int fp,fp1,fp2,fp3,option,i=0;
    unsigned char c,c1;
    char file_name[15];
    /*option to say whether encrypting or decrypting (i.e, 1 / 2)*/
    option=atoi(argv[2]);
    if(argc<3)
    {
        printf("\n Please enter path of file and option..!!\n");
        return;
    }
    /*opening a file to read*/
    fp=open(argv[1],O_RDONLY);
    if(fp==-1)
    {
        printf("\nFile not exists..!!");
        return;
    }
    
    
    if(option==1&&option==2)
    {
        printf("\ninvalid option..!!");
        return;
        
    }
    
    /*encryption*/
        if(option==1)
        {
            
            mode_t mode=S_IRUSR| S_IWUSR | S_IRGRP | S_IROTH;
            /*encrypted data will be stored in "encrypt" file
            open "encrypt" file*/
            fp1=open("encrypt",O_CREAT|O_RDWR|O_APPEND|O_TRUNC,mode);
            /*loop to read each byte from file untill EOF*/
            if(fp1==-1)
            {
                printf("\nerror in opening a file\n");
                return;
            }
            
            /*if reading a file failed*/
            /*if(read(fp,&c,sizeof(c))==0)
            {
                printf("File read failed..!!");
                return;
            }*/
            
            char *buffer;
                buffer = (char*)calloc(1026,sizeof(char));
                
            while(read(fp,&c,sizeof(c))>0)
            {
                /*send each byte for encryption & last character is dummy(i.e, 'a')
                to match for actual syntax of function*/
                
                size_t size=sizeof(buffer);
                if(size<1026)
                {
                    *(buffer+i)=c;
                }
                else
                    free(buffer);
                    i++;
                rot13_encrypt(c,fp1);
                
            }
            close(fp1);
            printf("\nSuccessfully encrypted..!\n");
        }
        /*decryption*/
        else
        {
            
            if(argc!=4)
            {
                printf("Original file name not provided..!!");
                return;
            }
            
            /*open original file*/
            fp3=open(argv[3],O_RDONLY);
            if(fp3==-1)
            {
                printf("\nFile not exists..!!");
                return;
            }
            
            mode_t mode1=S_IRUSR| S_IWUSR | S_IRGRP | S_IROTH;
            /*decrypted data will be stored in "decrypt" file
            open decrypt file*/
            fp2=open("decrypt",O_CREAT|O_RDWR|O_APPEND|O_TRUNC,mode1);
            
            /*if reading of encryted & original file failed*/
            /*if(read(fp,&c,sizeof(c))==0||read(fp3,&c1,sizeof(c1)==0))
            {
                printf("\nReading of file failed..!!");
                return;
            }*/
            
            /*loop to read each byte from file untill EOF
            even we r reading original file character*/
            while(read(fp,&c,sizeof(c))>0&&read(fp3,&c1,sizeof(c1)>0))
            {                                                       
                /*send each byte for decryption with original file character*/
                rot13_decrypt(c,fp2,c1);
                
                //printf("%c",c);
            }
            close(fp2);
            printf("\nSuccessfully decrypted..!\n");
        }

    close(fp);

}
