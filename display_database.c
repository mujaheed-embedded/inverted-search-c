#include "inverted_search.h"

int display(hash_t *arr)
{
    int flag = 0;
    for(int i = 0; i < 27; i++) //Check the database is empty or not
    {
        if(arr[i].link != NULL)
        {
        flag = 1;
        break;
        }
    }
    if(flag != 1){
    printf("DATABASE is empty\n");
    return 1;
    }
    main_node *main_temp;
    sub_node *sub_temp;
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < 27; i++) // Print the data
    {
        if (arr[i].link != NULL)
        {
            printf("[%-3d]", i);  // Print index inside brackets with proper space

            main_temp = arr[i].link;
            while (main_temp)
            {
                // Print the word
                printf(" %-15sfound in %-2d files  ", main_temp->word,main_temp -> file_count);
                sub_temp = main_temp->sublink;
                while (sub_temp)
                {
                    // Print file name and word count
                    printf("File: %-15s %-3d times    ", sub_temp->filename, sub_temp->word_count);
                    sub_temp = sub_temp->link;
                }

                printf("\n");
                printf("     ");  // Indentation for next line of the same main_temp
                main_temp = main_temp->link;
            }
            printf("\n");
        }
    }
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    return 1;
}
