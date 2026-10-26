#include "inverted_search.h"

int update_database_from_file(hash_t *arr, const char *filename)
{
    FILE *fptr = fopen(filename, "r");

    if (fptr == NULL)
    {
        perror("Error opening file for updating database");
        return FAILURE;
    }

    char line[1024];

    while (fgets(line, sizeof(line), fptr))
    {
        if (line[0] != '#')
            continue;

        char *token = strtok(line, "#;");

        if (token == NULL)
            continue;

        int index = atoi(token);

        if (index < 0 || index > 26)
            continue;

        token = strtok(NULL, ";");

        if (token == NULL)
            continue;

        char word[100];
        strcpy(word, token);

        token = strtok(NULL, ";");

        if (token == NULL)
            continue;

        int file_count = atoi(token);

        main_node *main_temp = arr[index].link;
        main_node *main_prev = NULL;

        while (main_temp)
        {
            if (strcmp(main_temp->word, word) == 0)
                break;

            main_prev = main_temp;
            main_temp = main_temp->link;
        }

        if (main_temp == NULL)
        {
            main_temp = malloc(sizeof(main_node));

            if (main_temp == NULL)
            {
                fclose(fptr);
                return FAILURE;
            }

            strcpy(main_temp->word, word);
            main_temp->file_count = 0;
            main_temp->sublink = NULL;
            main_temp->link = NULL;

            if (main_prev == NULL)
                arr[index].link = main_temp;
            else
                main_prev->link = main_temp;
        }

        while ((token = strtok(NULL, ";#")) != NULL)
        {
            char file_name[100];

            strcpy(file_name, token);

            token = strtok(NULL, ";#");

            if (token == NULL)
                break;

            int word_count = atoi(token);

            sub_node *sub_temp = main_temp->sublink;
            sub_node *sub_prev = NULL;
            int file_found = 0;

            while (sub_temp)
            {
                if (strcmp(sub_temp->filename, file_name) == 0)
                {
                    sub_temp->word_count = word_count;
                    file_found = 1;
                    break;
                }

                sub_prev = sub_temp;
                sub_temp = sub_temp->link;
            }

            if (file_found == 0)
            {
                sub_node *new_sub = malloc(sizeof(sub_node));

                if (new_sub == NULL)
                {
                    fclose(fptr);
                    return FAILURE;
                }

                strcpy(new_sub->filename, file_name);
                new_sub->word_count = word_count;
                new_sub->link = NULL;

                if (sub_prev == NULL)
                    main_temp->sublink = new_sub;
                else
                    sub_prev->link = new_sub;

                main_temp->file_count++;
            }
        }

        if (main_temp->file_count < file_count)
            main_temp->file_count = file_count;
    }

    fclose(fptr);

    printf("Database successfully updated from %s\n", filename);

    return SUCCESS;
}