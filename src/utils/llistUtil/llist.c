#include <stdlib.h>
#include "llist.h"

/// @brief Create a new empty linked list.
/// @return The new linked list sentinel 
LL_Sentinel* LL_Create()
{
    LL_Sentinel* sentinel = malloc(sizeof(LL_Sentinel));

    if (sentinel == NULL)
    {
        return NULL;
    }

    sentinel->length = 0;
    sentinel->head = NULL;

    return sentinel;
}

/// @brief Free the list and all elements of the list.
/// @warning Only list objects are freed, data must be freed independently!
/// @param ll The list to dispose of
void LL_Dispose(LL_Sentinel* ll)
{
    LL_Item* next = ll->head;
    for (LL_Item* ptr = ll->head; ptr; ptr = next)
    {
        next = ptr->next;

        free(ptr);
    }

    free(ll);
}

/// @brief Create a new Linked list item.
/// @param data The data to add to the new item
/// @return The new linked list item
LL_Item* LL_CreateItem(void* data)
{
    LL_Item* item = malloc(sizeof(LL_Item));

    if (item == NULL)
    {
        return NULL;
    }

    item->data = data;
    item->next = NULL;

    return item;
}

/// @brief Create a new linked list item and add it to the end of the specified linked list.
/// @param ll The linked list to append to
/// @param data The data to add to the new item
/// @return If element has been appended successfully the function will return 1 otherwise 0
int LL_Append(LL_Sentinel* ll, void* data)
{
    LL_Item* item = LL_CreateItem(data);

    if (item == NULL)
    {
        return 0;
    }

    if (!ll->head)
    {
        ll->head = item;
    }
    else
    {
        LL_Item* ptr;
        for (ptr = ll->head; ptr->next; ptr = ptr->next)
        {}

        ptr->next = item;
    }

    ll->length++;

    return 1;
}

/// @brief Create a new linked list item and add it to the specified linked list at the specified index.
/// @param ll The linked list to insert to
/// @param data The data to give the new item
/// @param index The index to add the item to
/// @return If element has been inserted successfully the function will return 1 otherwise 0
int LL_Insert(LL_Sentinel* ll, void* data, unsigned int index)
{
    if (index > ll->length)
    {
        return 0;
    }

    LL_Item* item = LL_CreateItem(data);

    if (item == NULL)
    {
        return 0;
    }

    if (index == 0)
    {
        item->next = ll->head->next;
        ll->head = item;
    }
    else
    {
        LL_Item* ptr = ll->head;

        for (unsigned int i = 1; ptr && i < index; ptr = ptr->next, i++)
        {}

        if (!ptr)
        {
            return 0;
        }

        item->next = ptr->next;
        ptr->next = item;
    }

    ll->length++;

    return 1;
}

void* LL_RemoveAt(LL_Sentinel* ll, unsigned int index)
{
    if (index > ll->length)
    {
        return NULL;
    }

    LL_Item* item;

    if (index == 0)
    {
        item = ll->head;
        ll->head = ll->head->next;
    }
    else
    {
        LL_Item* ptr = ll->head;

        for (unsigned int i = 1; ptr->next && i < index; ptr = ptr->next, i++)
        {}

        if (!ptr->next)
        {
            return NULL;
        }

        item = ptr->next;
        ptr->next = item->next;
    }

    ll->length--;

    void* data = item->data;

    free(item);
    
    return data;
}

/// @brief Get the data at the specified index.
/// @param ll The list to get from
/// @param index The index of the item to get
/// @return The data at the specified index
void* LL_Get(LL_Sentinel* ll, unsigned int index)
{
    if (index >= ll->length)
    {
        return NULL;
    }

    LL_Item* ptr = ll->head;

    for (unsigned int i = 0; ptr && i < index; i++, ptr = ptr->next) { }

    if (!ptr)
    {
        return NULL;
    }

    return ptr->data;
}

/// @brief Call The func parameter function on each data on the specified linked list.
/// @param ll The linked list to iterate over
/// @param func The function to call on each data of the linked list
void LL_ForEach(LL_Sentinel* ll, void (*func)(void*, void*), void* data)
{
    for (LL_Item* ptr = ll->head; ptr; ptr = ptr->next)
    {
        func(ptr->data, data);
    }
}

/// @brief Return if the list contains one or more element(s) that satifies the comparatorFunc.
/// @param ll The list to search in
/// @param comparatorFunc The criteria to satisfy
/// @return 1 if at least one element has been found, 0 otherwise
int LL_Contains(LL_Sentinel* ll, int (*comparatorFunc)(void*, void*), void* data)
{
    for (LL_Item* ptr = ll->head; ptr; ptr = ptr->next)
    {
        if (comparatorFunc(ptr->data, data))
        {
            return 1;
        }
    }

    return 0;
}

/// @brief Return the index of the first element that satisfy the comparatorFunc.
/// @param ll The list to search in
/// @param comparatorFunc The criteria to satisfy
/// @return Return the index of the element if found, -1 otherwise
int LL_IndexOf(LL_Sentinel* ll, int (*comparatorFunc)(void*, void*), void* data)
{
    LL_Item* ptr = ll->head;

    for (int i = 0; ptr; ptr = ptr->next, i++)
    {
        if (comparatorFunc(ptr->data, data))
        {
            return i;
        }
    }

    return -1;
}
