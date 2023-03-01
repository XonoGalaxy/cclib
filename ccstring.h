#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

/*
 * breaks_camel_case_up() - return broken string up to a word list
 * Split words on a string laid out with camel case pattern
 * One pass string parsing function
 */
static char** breaks_camel_case_up(char input[])
{

        // character handler
        char c;
        // flags
        int word_list_end = 0;
        // counter
        int idx = 0;
        int word_nb = 0;
        int ch_nb = 0;
        // cache
        int word_list_size; 
        int word_size;

        // buffer allocation
        char **word_list;
        word_list = (char **)malloc(sizeof(char*));
        if (word_list == NULL) {
                /*error handling*/
                printf("error word list allocation\n");
        }
        *word_list = (char *)malloc(sizeof(char));
        if (*word_list == NULL) {
                /*error handling*/
                printf("error current word into list allocation\\n");
        }
        char *word = (char *)malloc(sizeof(char));
        if (word == NULL) {
                /*error handling*/
                printf("error word allocation\n");
        }

        // parsing input string
        while (word_list_end != 1)
        {

        	// handle character
        	c = input[idx];

                if (isupper(c)) {

                    	// handle new word
                    	word_nb++;
                    	// handle character
                    	idx++;
                    	ch_nb++;
                    	c = input[idx];
                    	// parse new word
                    	while (!isupper(c) && c != '\0')
                    	{
                    	        idx++;
                    	        ch_nb++;
                    	        // handling character's input
                    	        c = input[idx];
                    	};
	
                    	// cache the word size : ch_nb + 1 to consider '\0' that ends up
                    	word_size = ch_nb + 1;

                    	// word buffering
                    	word = (char *)realloc(word, word_size * sizeof(char));
                    	if (word == NULL) {
                    	        /*error handling*/
                    	        printf("error word re-allocation\n");
                    	}

                    	for(int p = 0; p < word_size - 1; p++) 
                    	{
                    	    strncat(word, &input[idx-ch_nb+p], 1);
                    	}

                    	// ends word up
                    	strcat(word, "\0");

                    	// cache the word list size for each word occurence
                    	for(int q = 0; q < strlen(word) + 1; q++) 
                    	{
                    	    word_list_size += sizeof(word[q]);
                    	}

                    	// word list buffering
                    	word_list = (char **)realloc(word_list, word_list_size * sizeof(char));
                    	if (word_list == NULL) {
                    	        /*error handling*/
                    	        printf("error word list re-allocation\n");
                    	}
                    	word_list[word_nb-1] = (char *)realloc(word_list[word_nb-1], word_size * sizeof(char));
                    	if (word_list[word_nb-1] == NULL) {
                    	        /*error handling*/
                    	        printf("error current word into list re-allocation\n");
                    	}

                    	strcpy(word_list[word_nb-1], word);

                    	// reset word
                    	memset(word, 0, sizeof(*word));
                    	// reset character number of the word
                    	ch_nb = 0;

                } else if (c == '\0') {
                        word_list_end = 1;
                }
        };

		// free buffer
        free(word);

		// handle output
        return word_list;
}