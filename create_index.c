#include "inverted_search.h"

void create_Hash_table(hash_t *HT)
{
    for(int i = 0; i < 27; i++)
    {
        HT[i].index = i;
        HT[i].link = NULL;
    }
}

// Check if a file is already in the database
int is_file_in_database(const char *filename)
{
    
    FILE *fptr = fopen(FILE_DB, "r");
    if (!fptr)
    {
        return 0; // If file doesn't exist, assume filename is not stored
    }

    char stored_filename[256];
    while (fgets(stored_filename, sizeof(stored_filename), fptr))
    {
        stored_filename[strcspn(stored_filename, "\n")] = 0; // Remove newline
        if (strcmp(stored_filename, filename) == 0)
        {
            fclose(fptr);
            return 1; // File found
        }
    }
    fclose(fptr);
    return 0; // File not found
}

// Function to add filenames to the database file (only when "Save Database" is selected)
void save_filenames_to_database(file_name *head)
{
    FILE *fptr = fopen(FILE_DB, "a");
    if (!fptr)
    {
        perror("Error opening database file");
        return;
    }

    file_name *temp = head;
    while (temp)
    {
        if (!is_file_in_database(temp -> data)) // Avoid duplicate entries
        {
            fprintf(fptr, "%s\n", temp->data);
        }
        temp = temp->link;
    }

    fclose(fptr);
    printf("Database filenames saved successfully!\n");
}

// Function to check if a file is empty
int is_file_empty(const char *filename)
{
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
        return 1;

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);

    fclose(fp);

    return size == 0;
}