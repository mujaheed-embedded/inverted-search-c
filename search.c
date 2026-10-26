#include "inverted_search.h"

void search(hash_t *arr,char *word)
{
    int index = 0;
    //find the index
    if(word[0] >= 'a' && word[0] <='z')
    {
        index = word[0] - 'a';
    }
    else if(word[0] >= 'A' && word[0] <='Z')
    {
        index = word[0] - 'A';
    }
    else
    {
        index = 26;
    }
    //check index pointer is null or not
    if(arr[index].link == NULL)
    {
        printf("Data not found\n");
        return;
    }
    else{
        main_node *main_temp = arr[index].link;
        while(main_temp)
        {
            //Compare all main node data
            if(strcmp(main_temp -> word,word) == 0)
            {
                printf("String %s is present in %d files\n",word,main_temp -> file_count);
                sub_node *sub_temp = main_temp -> sublink;
                while(sub_temp)
                {
                    printf("In %s %d times\n",sub_temp -> filename,sub_temp -> word_count);
                    sub_temp = sub_temp -> link;
                }
                return;
            }
            main_temp = main_temp -> link;
        }
    }
    printf("Data not found\n");
    return;
}