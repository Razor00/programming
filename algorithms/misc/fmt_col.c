/*
 * =====================================================================================
 *
 *       Filename:  fmt_col.c
 *
 *    Description:  adjust each line to n number of columns with eq adjustment
 *
 *        Version:  1.0
 *        Created:  Saturday 18 August 2012 06:28:33  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  madan (), madanpandiri@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <assert.h>
#include <ctype.h>

char word_arr[1024];

char *format(char *st, char *end, int w)
{
    int words   = 0, chr = 0;
    int is_word = 0;

    /*  remove ending white space */
    while (end >= st && !isspace(*end))
        end--;

    /*  remove starting white space */
    while (st <= end && isspace(*st))
        st++;
    
    char *orig_st = st;
    /*  count the number of words and characters required */
    while (st <= end) {
        is_word = 0;
        while (st <= end && !isspace(*st)) {
            chr++; 
            st++;
            is_word = 1;
        }
        if (is_word)
            words++;

        while (st <= end && isspace(*st))
            st++;
    }
    if (words > 2)
        words -= 2; //remove the first and last word

    int min_spaces      = words + 1;
    int total_spaces    = w - chr;
    int spaces_for_each = total_spaces/min_spaces;
    int rem_spaces      = total_spaces - (min_spaces * spaces_for_each);

#if 0
    printf("total_spaces: %d\n", total_spaces);
    printf("spaces for each: %d\n", spaces_for_each);
    printf("rem_space : = %d\n", rem_spaces);
    printf("min_spaces = %d \n", min_spaces);
#endif
    
    st = orig_st;
    int j = 0;
    while (st <= end) {
        is_word = 0;
        while (st <= end && !isspace(*st)) {
            word_arr[j++] = *st++;
            is_word = 1;
        }
    
        int i;
        if (is_word && words >= 0){
            int sp = spaces_for_each;
            if (rem_spaces) {
                sp++;
                rem_spaces--;
            }    
            for (i = 0; i < sp; i++) 
                word_arr[j++] = ' '; /*insert spaces as required*/
            words--;
        } 
        while (st <= end && isspace(*st))
            st++;
    }
    word_arr[j] = '\0';
    puts(word_arr);


    return end;
}

void format_col(char *buf, int tlen, int width)
{
    char * st = buf;
    char *end = st + width - 1;
    while (st < end) {
        st = format(st, end, width);
        end = st + width - 1;
        if (end  >= (buf + tlen))
            end = buf+tlen-1;
    }
}


int main(int argc, char *argv[])
{
    
    if (argc != 3) {
        printf("Usage: %s filename width\n", argv[0]);
        exit(0);
    }
    
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    
    struct stat st_buf;
    if (fstat(fd, &st_buf) < 0) {
        perror("Error fstat\n");
        exit(EXIT_FAILURE);
    }


    char *buf = mmap(NULL, st_buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (!buf) {
        perror("Error mapping \n");
        exit(EXIT_FAILURE);
    }
    int width = atoi(argv[2]);
    format_col(buf, st_buf.st_size, width);
}


