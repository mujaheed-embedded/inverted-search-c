/*

Name : MUJAHEED AHMED
Description : The goal of this project is to develop a search engine that uses an inverted index to efficiently retrieve relevant documents
based on keyword queries. An inverted index maps words to the documents they appear in,
allowing fast lookups and ranking results based on relevance.


*/

#include "inverted_search.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("ERROR :: Please enter at least one valid file name.\n");
        return 0;
    }

    file_name *head = NULL;
    hash_t arr[27];

    if (file_validation(argv, argc, &head) == FAILURE)
    {
        printf("ERROR :: No valid files found. Program terminated due to invalid input.\n");
        return 0;
    }

    create_Hash_table(arr);

    int operation;
    int create_flag = 0;
    int update_flag = 0;
    char option;
    char word[20];
    char filename[20];

    do
    {
        printf("\n1. Create DATABASE\n");
        printf("2. Display\n");
        printf("3. Update DATABASE\n");
        printf("4. Search\n");
        printf("5. Save DATABASE\n\n");
        printf("Enter the option : ");
        scanf("%d", &operation);

        switch (operation)
        {
            case 1:
                if (create_flag == 0)
                {
                    create_database(head, arr);
                    create_flag = 1;
                }
                else
                {
                    printf("ERROR :: A database has already been created. Cannot create another one.\n");
                }
                break;

            case 2:
                display(arr);
                break;

            case 3:
                if (update_flag == 0 && create_flag != 1)
                {
                    printf("Please enter the file name to update the database: ");
                    scanf("%19s", filename);

                    if (strstr(filename, ".") != NULL &&
                        strcmp(strstr(filename, "."), ".txt") == 0)
                    {
                        FILE *fptr = fopen(filename, "r");

                        if (fptr == NULL)
                        {
                            printf("ERROR :: File does not exist.\n");
                        }
                        else
                        {
                            fclose(fptr);
                            update_database_from_file(arr, filename);
                            update_flag = 1;
                        }
                    }
                    else
                    {
                        printf("ERROR :: The file name is not valid.\n");
                    }
                }
                else if (create_flag == 1)
                {
                    printf("Database already created. You cannot update it now.\n");
                }
                else
                {
                    printf("ERROR :: The database has already been updated. Cannot update it again.\n");
                }
                break;

            case 4:
                printf("Please enter the word you want to search for: ");
                scanf("%19s", word);
                search(arr, word);
                break;

            case 5:
                printf("Please enter the file name to save the database: ");
                scanf("%19s", filename);

                if (strstr(filename, ".") != NULL &&
                    strcmp(strstr(filename, "."), ".txt") == 0)
                {
                    save_database(arr, filename);
                    save_filenames_to_database(head);
                }
                else
                {
                    printf("ERROR :: The file name is not valid.\n");
                }
                break;

            default:
                printf("Enter proper choice\n");
                break;
        }

        printf("\nDo you want to continue? Press [y/Y for Yes, Any key to exit]: ");
        scanf(" %c", &option);

    } while (option == 'y' || option == 'Y');
    free_all(head, arr);
    return 0;
}

int file_validation(char *argv[], int count, file_name **head)
{
    for (int i = 1; i < count; i++)
    {
        if (argv[i] != NULL)
        {
            if (strstr(argv[i], ".") != NULL)
            {
                if (strcmp(strstr(argv[i], "."), ".txt") == 0)
                {
                    FILE *fptr = fopen(argv[i], "r");

                    if (fptr == NULL)
                    {
                        printf("%-15s does not exist.\n", argv[i]);
                    }
                    else
                    {
                        fseek(fptr, 0, SEEK_END);
                        long res = ftell(fptr);

                        if (res == 0)
                        {
                            printf("%-15s are not having any contents.\n", argv[i]);
                        }
                        else
                        {
                            file_name *temp = *head;
                            int flag = 0;

                            while (temp != NULL)
                            {
                                if (strcmp(temp->data, argv[i]) == 0)
                                {
                                    printf("%-15s is a duplicate file.\n", argv[i]);
                                    flag = 1;
                                    break;
                                }

                                temp = temp->link;
                            }

                            if (is_file_in_database(argv[i]))
                            {
                                fprintf(stderr,
                                        "%-15s is already stored in the database. Skipping this file...\n",
                                        argv[i]);
                                flag = 1;
                            }

                            if (flag == 0)
                            {
                                insert_at_last(head, argv[i]);
                            }
                        }

                        fclose(fptr);
                    }
                }
            }
        }
    }

    if (*head == NULL)
    {
        printf("INFO : List is empty\n");
        return FAILURE;
    }

    return SUCCESS;
}

int insert_at_last(file_name **head, char data[])
{
    file_name *new = malloc(sizeof(file_name));

    if (!new)
    {
        return FAILURE;
    }

    strcpy(new->data, data);
    new->link = NULL;

    if (*head == NULL)
    {
        *head = new;
        return SUCCESS;
    }

    file_name *temp = *head;

    while (temp->link != NULL)
    {
        temp = temp->link;
    }

    temp->link = new;

    return SUCCESS;
}
