
#ifndef INVERTED_SEARCH_H
#define INVERTED_SEARCH_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>

#define FILE_DB "default.txt"

#define SUCCESS 0
#define FAILURE -1

typedef struct node
{
    char data[100];
    struct node *link;
} file_name;

typedef struct node1
{
    int file_count;
    char word[100];
    struct node2 *sublink;
    struct node1 *link;
} main_node;

typedef struct node2
{
    int word_count;
    char filename[100];
    struct node2 *link;
} sub_node;

typedef struct node3
{
    int index;
    struct node1 *link;
}hash_t;

int file_validation(char *argv[],int count,file_name **head);

int insert_at_last(file_name **head, char data[]);

void print_list(file_name *head);

void create_database(file_name *head,hash_t *arr);

void create_Hash_table(hash_t *HT);

int create_main(char word[],hash_t *arr,char *file,int index);

int display(hash_t *arr);

void search(hash_t *arr,char *word);

void save_database(hash_t *arr,char *file);

int update_database_from_file(hash_t *arr, const char *file);

void save_filenames_to_database(file_name *head);

int is_file_empty(const char *filename);

int is_file_in_database(const char *filename);

void free_all(file_name *head, hash_t *arr);

#endif