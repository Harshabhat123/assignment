#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>


#define MAX_VALUE 0xFF
#define BLOCK_SIZE 1024


typedef unsigned char uchar_t;
typedef signed char schar_t;
typedef enum boolean{
        _false = 0,
        _true
} boolean_t;


/**************************LOGGING*********************************************/
/*logging related types, macros and functions*/


 typedef enum log_level {
        log_error = -1,
        log_info = 0
        }log_level_t;
    
    
/* Function used for logging */
 void log_it (log_level_t log_level,
        const char      *file_name,
        const char      *function,
        int             line,
        const char      *fmt, ...)
 {
        FILE *stream    =   NULL;
        va_list arg_list;
        char *message   =   NULL;
    
    
        if (log_level == -1)
            stream = stderr;
        else if (log_level == 0)
            stream = stdout;
        
        
/* form the message */
        va_start (arg_list, fmt);
        vasprintf (&message, fmt, arg_list);
        va_end (arg_list);
    
        fprintf (stream, "%d %s %s : %s", line, file_name, function, message);
    
        free (message);
}



/* Macro used for logging */

#define LOG_IT(log_level, fmt...)\
do {\
        log_it (log_level, __FILE__, __FUNCTION__, __LINE__, ##fmt);\
} while(0)
    
    
    
/******************************************************************************/



int rot13_encrypt (uchar_t *buffer, ssize_t size, int des_fd)
{
        int j            =     0;
        int ret          =     -1;
        ssize_t i        =     0;
        
        if (!buffer) {
            LOG_IT (log_error, "Empty Buffer");
            goto out;
        }


        if (size == 0) {
            LOG_IT (log_error, "Buffer size is zero");
            goto out;
        }

        for (i = 0; i < size ; i++) {
            *(buffer + i) = (*(buffer+i) + 13) % 256;
        }


        ret = 0;
out:
        return ret;
}


int ro13_decrypt (uchar_t *buffer, ssize_t size, int des_fd)
{

        int         val          =       0;
        int         chr1         =       0;
        int         ret          =       -1;
        schar_t     diff         =       0;
        int         i            =       0;
    
    
        if (!buffer) {
                LOG_IT (log_error, "Empty Buffer");
                goto out;
        }


        if (size == 0) {
            LOG_IT (log_error, "Buffer size is zero");
            goto out;
        }

        for (i = 0; i < size ; i++) {
    
            chr1 = *(buffer+i);
        if(chr1 < 13)
        {
            diff = 13 - chr1;
            val = 256 - diff;
            *(buffer+i) = val;
        }
        else
        {
            *(buffer+i) = chr1 - 13;
        }
    }

        ret = 0;
out:
        return ret;
}


    /* function used for both encrypting and decrypting of file
    * char *src_file_name source file path
    * char *des_file_name destination file path
    * boolean_t do_encrypt if _true do encryption if not do decryption
    * returns 0 on success and -ve value on failure */

int crypt_rot13_file (const char *src_file_name, const char *des_file_name, boolean_t do_encrypt)
{
        int          ret     =   -1;
        int          i       =   0;
        int          src_fd  =   -1;
        int          des_fd  =   -1;
        uchar_t      buffer[1024]    =   {0};
        ssize_t      buffer_len          =   0;
    
    
        if (!src_file_name) {
            LOG_IT (log_error, "Empty source file name");
            goto out;
        }


        if (!des_file_name) {
            LOG_IT (log_error, "Empty destination file name");
            goto out;
        }


        src_fd = open (src_file_name, O_RDONLY);
    
        if (src_fd < 0) {
                LOG_IT (log_error, "Error opening source file %s : %s",
                src_file_name, strerror (errno));

            goto out;
        }


        des_fd = open (des_file_name, O_WRONLY | O_CREAT | O_APPEND,
        S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    
        if (des_fd < 0) {
                LOG_IT (log_error, "Error opening destination file %s : %s",
                des_file_name, strerror (errno));
    
                goto out;
        }

        while ( (ret = read (src_fd, buffer, BLOCK_SIZE)) > 0 ) 
        {
            if (ret < 0) 
            {
                    LOG_IT (log_error,"Error reading from source file %s : %s",src_file_name, strerror (errno));
                    goto out;
            }

            buffer_len = ret;
    
            ret = (do_encrypt) ? rot13_encrypt (buffer, buffer_len,des_fd) :
            ro13_decrypt (buffer, buffer_len,des_fd);


        if (ret) {
            LOG_IT (log_error, "Error %s the block",
            (do_encrypt) ? "encrypting" : "decrypting");
            goto out;
        }
        i=0;
    
        ret = write (des_fd, buffer, buffer_len);

        if (ret < 0)
        {
            LOG_IT (log_error,
            "Error writing to the destination file %s : %s",
            des_file_name, strerror (errno));

            goto out;
        }
    }

        ret = 0;
out:


/* Clean up on error */
        if (ret) 
        {
            ret = remove(des_file_name);
    
            if (ret) 
            {
                LOG_IT (log_error,
                "Error deleting destination file %s : %s",
                des_file_name, strerror (errno));
        
            }
        }

        if (src_fd >= 0) 
        {
            close (src_fd);
        }

        if (des_fd >= 0)
        {
            close (des_fd);
        }
        return ret;
    
 }




 int main(int argc, char *argv [])
 {
    
        int nxt_option      =       0;
        const char* const short_options     =   "e:d:o:";
    
        const struct option long_options[] = {
        {"encrypt",     1,  NULL,   'e'},
        {"decrypt",     1,  NULL,   'd'},
        {"original",    1,  NULL,   'o'},
        { NULL,         0,  NULL,   0}
            };
        
        
        int ret     =    -1;
        const char* origin  =       NULL;
        const char* file    =      NULL;
    
        do
        {
            nxt_option = getopt_long (argc, argv, short_options, long_options, NULL);
        
            switch (nxt_option)
            {
                case 'o':origin =   optarg;
                    
                        break;
                case 'e':
                        file    =   optarg;
                        ret     =   crypt_rot13_file (origin,file,true);
                        break;
                case 'd':
                        file    =   optarg;
                        ret     =    crypt_rot13_file (origin,file,false);
                        break;
                case -1:
                        break;
            }
        }while(nxt_option != -1);
    
    
 out:
        return ret;
 }