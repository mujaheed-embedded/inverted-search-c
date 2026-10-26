#include "inverted_search.h"

void save_database(hash_t *arr, char *file)
{
    FILE *fptr = fopen(file, "w");  //open the file
    if (fptr == NULL)   //Error handling
    {
        perror("Error occurred while opening a file");
        return;
    }

    int flag = 0;

    for (int i = 0; i < 27; i++)    //Check the file is empty or not
    {
        if (arr[i].link != NULL)
        {
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        fprintf(fptr, "DATABASE is empty\n");
        fclose(fptr);
        return;
    }

    for (int i = 0; i < 27; i++)
    {
        if (arr[i].link != NULL)
        {
            main_node *main_temp = arr[i].link;

            while (main_temp)
            {
                // Write the start of the line with a #
                fprintf(fptr, "#");

                // Write index, word, and file count with semicolons
                fprintf(fptr,"%d;%s;%d", i, main_temp->word, main_temp->file_count);

                sub_node *sub_temp = main_temp->sublink;
                
                // Write file names and word counts with semicolons
                while (sub_temp)
                {
                    fprintf(fptr,";%s;%d;", sub_temp->filename, sub_temp->word_count);
                    sub_temp = sub_temp->link;
                }

                // End the line with a #
                fprintf(fptr, "#\n");

                main_temp = main_temp->link;
            }
        }
    }
    fclose(fptr);
    printf("Database successfully saved to %s\n", file);
}