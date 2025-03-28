#ifndef LLIST_H
#define LLIST_H

typedef struct ll_item
{
    void* data;
    struct ll_item* next;
}LL_Item;

typedef struct
{
    unsigned int length;
    LL_Item* head;
}LL_Sentinel;

LL_Sentinel* LL_Create();
void LL_Dispose(LL_Sentinel* ll);

int LL_Append(LL_Sentinel* ll, void* data);
int LL_Insert(LL_Sentinel* ll, void* data, unsigned int index);
void* LL_RemoveAt(LL_Sentinel* ll, unsigned int index);
void* LL_Get(LL_Sentinel* ll, unsigned int index);

void LL_ForEach(LL_Sentinel* ll, void (*func)(void*, void*), void* data);
int LL_Contains(LL_Sentinel* ll, int (*comparatorFunc)(void*, void*), void* data);
int LL_IndexOf(LL_Sentinel* ll, int (*comparatorFunc)(void*, void*), void* data);

#endif