#include "inverted_search.h"

void create_database(file_name *filelist, hash_t *arr)
{
    char word[100];
    file_name *file_temp = filelist;

    while (file_temp)
    {
        FILE *fptr = fopen(file_temp->data, "r");

        if (fptr == NULL)
        {
            printf("Error opening file %s\n", file_temp->data);
            file_temp = file_temp->link;
            continue;
        }

        while (fscanf(fptr, "%99s", word) == 1)
        {
            int index;

            if (word[0] >= 'a' && word[0] <= 'z')
                index = word[0] - 'a';
            else if (word[0] >= 'A' && word[0] <= 'Z')
                index = word[0] - 'A';
            else
                index = 26;

            if (arr[index].link == NULL)
            {
                create_main(word, arr, file_temp->data, index);
            }
            else
            {
                main_node *main_temp = arr[index].link;
                main_node *main_prev = NULL;
                int main_found = 0;

                while (main_temp)
                {
                    if (strcmp(main_temp->word, word) == 0)
                    {
                        main_found = 1;

                        sub_node *sub_temp = main_temp->sublink;
                        sub_node *sub_prev = NULL;
                        int sub_found = 0;

                        while (sub_temp)
                        {
                            if (strcmp(sub_temp->filename,
                                       file_temp->data) == 0)
                            {
                                sub_temp->word_count++;
                                sub_found = 1;
                                break;
                            }

                            sub_prev = sub_temp;
                            sub_temp = sub_temp->link;
                        }

                        if (sub_found == 0)
                        {
                            sub_node *new_sub = malloc(sizeof(sub_node));

                            if (new_sub == NULL)
                            {
                                fclose(fptr);
                                return;
                            }

                            new_sub->word_count = 1;
                            strcpy(new_sub->filename, file_temp->data);
                            new_sub->link = NULL;

                            if (sub_prev == NULL)
                                main_temp->sublink = new_sub;
                            else
                                sub_prev->link = new_sub;

                            main_temp->file_count++;
                        }

                        break;
                    }

                    main_prev = main_temp;
                    main_temp = main_temp->link;
                }

                if (main_found == 0)
                {
                    main_node *new_main = malloc(sizeof(main_node));

                    if (new_main == NULL)
                    {
                        fclose(fptr);
                        return;
                    }

                    new_main->file_count = 1;
                    strcpy(new_main->word, word);
                    new_main->link = NULL;

                    sub_node *new_sub = malloc(sizeof(sub_node));

                    if (new_sub == NULL)
                    {
                        free(new_main);
                        fclose(fptr);
                        return;
                    }

                    new_sub->word_count = 1;
                    strcpy(new_sub->filename, file_temp->data);
                    new_sub->link = NULL;

                    new_main->sublink = new_sub;

                    if (main_prev == NULL)
                        arr[index].link = new_main;
                    else
                        main_prev->link = new_main;
                }
            }
        }

        fclose(fptr);
        file_temp = file_temp->link;
    }

    printf("\nSuccessfully created database....\n");
}

int create_main(char word[], hash_t *arr, char *file, int index)
{
    main_node *new_main = malloc(sizeof(main_node));

    if (new_main == NULL)
        return FAILURE;

    sub_node *new_sub = malloc(sizeof(sub_node));

    if (new_sub == NULL)
    {
        free(new_main);
        return FAILURE;
    }

    new_main->file_count = 1;
    strcpy(new_main->word, word);
    new_main->link = NULL;

    new_sub->word_count = 1;
    strcpy(new_sub->filename, file);
    new_sub->link = NULL;

    new_main->sublink = new_sub;
    arr[index].link = new_main;

    return SUCCESS;
}