#include <stdio.h>
#include <stdint.h>

#define DEBUG 1

#define POOL_SIZE 24 /* 65536 - original value */
#define LIST_SIZE (POOL_SIZE/8)

typedef uint64_t item_t;

#define NUM_ITEMS (POOL_SIZE/(sizeof(item_t)))

static char mempool[POOL_SIZE];

struct list {
    struct list *next;
};
struct list *head;

item_t *allocator(void)
{
    if (head == NULL) {
        printf("No free mem\n");
        return NULL;
    }

    item_t *item = (item_t *)head;
    head = head->next;

   *item = ((item_t)(item) & 0xFFFF); /* Debug */
   printf("%s(): %lx\n", __func__, *item);

   return item;
}

int deallocator(item_t *item)
{
    struct list *list_item = (struct list *)item;

    if (item == NULL)
        return -1;

    printf("%s(): %lx\n", __func__, *item);
    list_item->next = head;
    head = list_item;

   return 0;
}

int init_list(void)
{
    struct list *ptr = NULL;

    head = (struct list *)&mempool[0];
    ptr = head;

    /* Initialized as all free */
    for (int i = 0; i < NUM_ITEMS; i++) {
        if (i == (NUM_ITEMS - 1)) {
            ptr->next = NULL;
        } else {
            ptr->next = (ptr + 1);
        }
        ptr = ptr->next;
    }
    printf("%s(): complete head %p\n", __func__, head);
    return 0;
}

static void dump_list()
{
    struct list *list;
    printf("\nfree list\t");
    for (list = head; (list != NULL); list = list->next)
        printf("%p --> ", list);
    printf("\n");
}

static void dump()
{
    item_t *item = (item_t *)&mempool[0];

    printf("\nlinear\t");
    for (int i = 0; i < NUM_ITEMS; i++, item++)
        printf("%lx\t", *item);
}

int main()
{
    item_t *item = NULL;
    item_t *item_a = NULL;
    item_t *item_b = NULL;
    item_t *item_c = NULL;

    if (init_list())
        return -1;

    dump(); dump_list();

    item = allocator();

    dump(); dump_list();

    item_a = allocator();

    dump(); dump_list();
    item_b = allocator();

    dump(); dump_list();

    /* out of memory here for 3 items */
    item_c = allocator();
    dump(); dump_list();
    deallocator(item_c);

    deallocator(item_a);
    dump(); dump_list();

    deallocator(item_b);
    dump(); dump_list();

    deallocator(item);
    dump(); dump_list();

    return 0;
}