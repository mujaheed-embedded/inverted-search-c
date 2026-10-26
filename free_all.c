#include "inverted_search.h"

void free_all(file_name *head, hash_t *arr)
{
    file_name *ftemp;

    while (head)
    {
        ftemp = head;
        head = head->link;
        free(ftemp);
    }

    for (int i = 0; i < 27; i++)
    {
        main_node *mtemp = arr[i].link;

        while (mtemp)
        {
            sub_node *stemp = mtemp->sublink;

            while (stemp)
            {
                sub_node *snext = stemp->link;
                free(stemp);
                stemp = snext;
            }

            main_node *mnext = mtemp->link;
            free(mtemp);
            mtemp = mnext;
        }

        arr[i].link = NULL;
    }
}