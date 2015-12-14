#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <getopt.h>

/*function to decrypt the encrypted file*/
int rot13_decrypt ( int i, char * buffer, int fp2)
{
    int ret         =       -1;
    int j_index     =       0;
    int chr1        =       0;
    int val         =       0;
    int diff        =       0;
    int char2       =       0;
    char char1;
    
    for(j_index = 0; j_index <= i; j_index++)
    {
        chr1 = *(buffer + j_index);
        char1 = *(buffer + j_index);
        
        if (chr1 < 13)
        {
            diff = 13 - chr1;
            val = 256 - diff;
        }
        else
        {
            val = chr1 - 13;
        }
        char1 = val;
        
        size_t size = sizeof(char1);
        /*writing to decrypting file*/
        ret = write (fp2, &char1, size);
        if(ret == 0)
        { 
            printf("writing error..!!");
            ret = -1;
            goto out;
        } 
    }
    ret  = 0;
    
    out:
    return ret;
}

int rot13_encrypt (char * buffer, int i ,int fp2)
{
    int j_index     =   0;
    int chr1        =   0;
    int val         =   0;
    int ret         =   -1;
    char char1;
    //printf("%d\n",i);
    for(j_index = 0;j_index <=i;j_index++)
    {
        
        chr1 = *(buffer + j_index);
        char1 = *(buffer + j_index);
        
        val = (chr1 + 13) % 255;
        
        char1 = val;
        
        size_t size = sizeof (char1);
        ret = write (fp2, &char1, size);
        if (ret == 0)
        {
            ret = -1;
            printf ("\t Writing Error\n");
            goto out;
        }
    }
    ret = 0;
        
        out:
            return ret;
}

/*to check for original file and decrypted file*/
int validation( int i ,char * buffer3, char * buffer4)
{
    int j_index     =   0;
    int chr1        =   0;
    int chr2        =   0;
    int ret         =   -1;
    
    for( j_index = 0; j_index <= i; j_index++ )
    {
        chr1 = *(buffer3 + j_index);
        chr2 = *(buffer4 + j_index);
        /*comparing ascii values of each byte in buffer of original file & decrypted file*/
        if( chr1 != chr2 )
        {
            printf("invalid decryption");
            ret = -1;
            goto out;
        }
    }
    ret = 0;
    out:
        return ret;
}

int main (int argc, char * argv [])
{
    int i_index         =       0;
    int ret             =       -1;
    int fp              =       NULL;
    int fp1             =       NULL;
    int fp2             =       NULL;
    int fp3             =       NULL;
    int k_index         =       0;
    int nxt_option      =       0;
    
    char c      =   NULL;
    char *c1;
    char c2     =   NULL;
    const char* origin =   NULL;
    const char* file   =   NULL;
    
    char * buffer3;
    
    //buffer3 = (char*) calloc (1026, sizeof (char));
    
    char * buffer4;
    
    /*command line i/p*/
    const char* const short_options = "e:d:v:o:";
    
    const struct option long_options[] = {
    {"encrypt",     1,  NULL,   'e'},
    {"decrypt",     1,  NULL,   'd'},
    {"validation",  1,  NULL,   'v'},
    {"original",    1,  NULL,   'o'},
    { NULL,         0,  NULL,   0}
        };
        
    const char* output_filename = NULL;
        
        mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    do{
            nxt_option = getopt_long (argc, argv, short_options, long_options, NULL);
    
        switch (nxt_option)
        {
            case 'e':
                /*encrypted data will be stored in "encrypt" file
                open "encrypt" file*/
                fp1 = open("encrypt", O_CREAT | O_RDWR | O_APPEND | O_TRUNC, mode);
                /*loop to read each byte from file untill EOF*/
                if (fp1 == -1)
                {
                    printf ("\nerror in opening a file\n");
                    ret = -1;
                    goto out;
                }
                output_filename = optarg;
            
                /*opening a i/p file*/ 
                fp = open (output_filename ,O_RDONLY);
                
                if (fp == -1)
                {
                    printf("\nFile not exists..!!");
                    ret = -1;
                    goto out;
                }
                
                char *buffer;
                buffer = (char*) calloc (1026, sizeof (char));
                size_t size;
                
                /*reading a file & storing in buffer*/
                while (read (fp, &c, sizeof (c)) > 0)
                {
                    if (i_index < 1025)
                    {
                        *(buffer + i_index) = c;
                        i_index++;
                    }
                /*if buffer full passes buffer to encrypt function*/
                    else
                    {
                        *(buffer + i_index) = c;
                        ret = rot13_encrypt ( buffer, i_index, fp1 );
                        free(buffer);
                        i_index=0;
                        buffer = (char*)calloc(1026,sizeof(char));
                    }
                }
                /*to pass the last remaining values while coming out of loop*/
                ret = rot13_encrypt ( buffer, i_index-1, fp1);
                close(fp1);
                close(fp);
                printf("\nsuccessfully encrypted\n");
                break;
            
        case 'd':
                /*decrypted data will be stored in "decrypt" file
                open "decrypt" file*/
                fp2 = open ("decrypt", O_CREAT | O_RDWR | O_APPEND | O_TRUNC, mode);
                /*loop to read each byte from file untill EOF*/
                if(fp2 == -1)
                {
                    printf("\nerror in opening a file\n");
                    ret = -1;
                    goto out;
                }
                output_filename = optarg;
                
                /*opening a i/p source file*/ 
                fp = open (output_filename, O_RDONLY);
                if(fp == -1)
                {
                    printf("\nFile not exists..!!");
                    ret = -1;
                }
                /*opening a encrypted file*/
                char *buffer3;
                buffer3 = (char*) calloc (1026, sizeof (char));
                
                /*reading a source file & encrpted file to storing in buffer*/
                while ( read (fp, &c, sizeof (c)) > 0 )
                {
                    if (k_index < 1025)
                    {
                        *(buffer3 + k_index) = c;
                        k_index++;
                    }
                    /*if buffer full passes buffer to decrypt function*/
                    else
                    {
                        *(buffer3 + k_index) = c;
                        ret = rot13_decrypt ( k_index, buffer3, fp2);
                        free (buffer3);
                        
                        k_index = 0;
                        buffer3 = (char*)calloc(1026,sizeof(char));
                        
                    }
                    
                }
                /*to pass the last remaining values while coming out of loop*/
                ret = rot13_decrypt ( k_index-1, buffer3, fp2);
                
                close(fp2);
                close(fp);
                printf("\nsuccessfully decrypted\n");
                 break;
                 
        case 'v':
                 if(argc != 5)
                {
                    printf("\nInvalid no of parameters..!\n");
                    ret = -1;
                    goto out;
                }
                 
                 file = optarg;
                 
                 fp = open (file , O_RDONLY);
                 fp2 = open (origin, O_RDONLY);
                 
                 if(fp == -1)
                {
                    printf("\nFile not exists..!!");
                    ret = -1;
                    goto out;
                }
                
                if(fp2 == -1)
                {
                    printf("\nFile not exists..!! 11");
                    ret = -1;
                    goto out;
                }
                buffer3 = (char*) calloc (1026, sizeof (char));
                buffer4 = (char*) calloc (1026, sizeof (char));
                 while ( read (fp, &c, sizeof (c)) > 0 && read (fp2, &c2, sizeof(c2)) > 0)
                {
                    if (k_index < 1025)
                    {
                        *(buffer3 + k_index) = c;
                        *(buffer4 + k_index) = c2;
                        k_index++;
                    }
                    /*if buffer full passes buffer to validation function*/
                    else
                    {
                        *(buffer3 + k_index) = c;
                        *(buffer4 + k_index) = c2;
                        ret = validation ( k_index, buffer4, buffer3);
                        free (buffer3);
                        free (buffer4);
                        k_index = 0;
                        buffer3 = (char*)calloc(1026,sizeof(char));
                        buffer4 = (char*)calloc(1026,sizeof(char));
                    }
                    
                }
                /*to pass the last remaining values while coming out of loop*/
                ret = validation ( k_index-1, buffer4, buffer3);
                close(fp2);
                close(fp);
                printf("\nsuccessfully validated\n");
                break;
                 
        case 'o':
                 
                 origin = optarg;
                 break;
        case -1:
                  break;
    }
    }while ( nxt_option != -1 );
    ret = 0;
    
    out:
        return ret;
}