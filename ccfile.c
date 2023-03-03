#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

/*
    Function for opening a file
    Function for parsing a the string file
    Function to break cc word up to a list
    Function to sort list down to an alphabetic order
    Function to create new file
        * specifying path to create new file
    Function to write back sorted list into new file 
 */

/* 
    input   : file 
    output  : listed woven words
*/

static int break_cc_file_down(char *in_path, char *out_path) {

    // ret val
    int ret = 1;

    // character handling
    char c;
    char ch;

    // file pointer
    FILE *infptr;
    FILE *outfptr;

    // buffer allocation
    char *word = NULL;
    char **word_list = NULL;

    // file creating and opening
    infptr = fopen(in_path, "r");
    if(infptr == NULL) {
        printf("input file [%s] doesn't exist", in_path);
        return ret = 0;
    }
    outfptr = fopen(out_path, "w");
    if(outfptr == NULL) {
        printf("output file [%s] doesn't exist", out_path);
        return ret = 0;
    }

    // counters
    int word_list_size = 0;
    int word_size = 0;
    int word_nb = 0;

    // handle file string
    c = fgetc(infptr);

    // intput file string handling
    while(c != EOF) 
    {
        word_size = 0;

        if(isupper(c)) {
            word_nb++;
            word_size++;
            word = (char *)realloc(word, word_size * sizeof(char));
            if (word == NULL) {
                    /*error handling*/
                    printf("error word re-allocation\n");
					return ret = 0;
            }
            strncat(word, &c, 1);
            c = fgetc(infptr);

            while(!isupper(c) && c != EOF) 
            {
                word_size++;
                word = (char *)realloc(word, word_size * sizeof(char));
                if (word == NULL) {
                        /*error handling*/
                        printf("error word re-allocation\n");
			    		return ret = 0;
                }
                strncat(word, &c, 1);
                c = fgetc(infptr);
            }
            word_size++;
            word = (char *)realloc(word, word_size * sizeof(char));
            if (word == NULL) {
                    /*error handling*/
                    printf("error word re-allocation\n");
		    		return ret = 0;
            }
            strncat(word, "\0", 1);
            printf("word : %s\n", word);

            /* Write back word into list */
            word_list_size += word_size;
            // word list buffering
            word_list = (char **)realloc(word_list, word_list_size * sizeof(char*));
            if (word_list == NULL) {
                    /*error handling*/
                    printf("error word list re-allocation\n");
					return ret = 0;
            }
            word_list[word_nb-1] = (char *)realloc(word_list[word_nb-1], (strlen(word)+1) * sizeof(char));
            if (word_list[word_nb-1] == NULL) {
                    /*error handling*/
                    printf("error current word into list re-allocation\n");
					return ret = 0;
            }
            strcpy(word_list[word_nb-1], word);

            // clear word buffer
            memset(word, 0, sizeof(*word));
        }
    }

    // alphabetic sorting of listed word
    for(int i = 0;i < word_nb; i++) 
    {
        for(int j = i + 1;j < word_nb; j++)
        {
            if(strcmp(word_list[i], word_list[j]) > 0) {
                strcpy(word, word_list[i]);
                strcpy(word_list[i], word_list[j]);
                strcpy(word_list[j], word);
            }
        }
    }

    // word list output
    for(int a = 0; a < word_nb; a++)
    {
        printf("Listed word : %s\n", word_list[a]);
    }

    /* Write back alphbetic listed word into output file */
    for(int a = 0; a < word_nb; a++) 
    {
        for(int b = 0; b < strlen(word_list[a]); b++)
        {
            // fill up output file
            //printf("[%c]", word_list[a][b]);
            ch = fputc(word_list[a][b], outfptr);
        }
        // jump line
        ch = fputc('\n', outfptr);
    }
    
    printf("\n");

    // free word buffer
    free(word);
    free(word_list);

    // file closing
    fclose(infptr);
    fclose(outfptr);

    return 1;
}

