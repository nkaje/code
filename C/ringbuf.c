#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define NUM_ELEMENTS 5
#define TOTAL_SLOTS  (NUM_ELEMENTS + 1)

struct com_stat {
    uint16_t command;
    uint16_t status;
};

struct circ_buf {
    struct com_stat *head;
    struct com_stat *tail;
    void *buf;
};

struct com_stat *buffer_end(struct circ_buf *cb)
{
    if (cb == NULL)
        return NULL;
    return (cb->buf + (TOTAL_SLOTS * sizeof(struct com_stat)));
}

int get_head_index(struct circ_buf *cb)
{
   return ((void *)cb->head - (void *)cb->buf)/(sizeof(struct com_stat));
}

int get_tail_index(struct circ_buf *cb)
{
   return ((void *)cb->tail - (void *)cb->buf)/(sizeof(struct com_stat));
}

int get_space(struct circ_buf *cb)
{
    int hi = get_head_index(cb);
    int ti = get_tail_index(cb);

    if ((ti - hi) == -1)
        return -ENOMEM;

    if (ti == hi)
        return NUM_ELEMENTS;
    if (ti > hi)
        return NUM_ELEMENTS - (ti - hi);
    else /* when hi > ti */
        return (hi - ti - 1);
}

int get_count(struct circ_buf *cb)
{
    return (NUM_ELEMENTS - get_space(cb));
}

int init_cb(struct circ_buf *cb)
{
    if (cb == NULL)
        return -ENOMEM;

    cb->buf = malloc((TOTAL_SLOTS) * sizeof(struct com_stat));
    if (cb->buf == NULL)
        return -ENOMEM;

    cb->head = (struct com_stat *)cb->buf;
    cb->tail = (struct com_stat *)cb->buf;
    return 0;
}

void free_cb(struct circ_buf *cb)
{
    free(cb->buf);
    cb->head = NULL;
    cb->tail = NULL;
}

void advance_head(struct circ_buf *cb)
{
    cb->head++;
    if (cb->head == buffer_end(cb))
        cb->head = (struct com_stat *)cb->buf;
}

void advance_tail(struct circ_buf *cb)
{
    cb->tail++;
    if (cb->tail == buffer_end(cb))
        cb->tail = (struct com_stat *)cb->buf;
}

int enqueue(struct circ_buf *cb, struct com_stat cs)
{
    int ret;
    if (cb == NULL || cb->buf == NULL)
        return -ENOMEM;

    /**
     * head == tail : cb is empty
     * tail = head - 1 : cb is full
     */
    ret = get_space(cb);
    if (ret <= 0)
        return -EINVAL;

    cb->tail = memcpy(cb->tail, &cs, sizeof(cs));
    advance_tail(cb);
    return 0;
}

int dequeue(struct circ_buf *cb, struct com_stat *cs)
{
    if (cb == NULL || cb->buf == NULL)
        return -ENOMEM;

    if (get_count(cb) == 0) {
        printf("cb empty\n");
        return 0;
    }

    cs = memcpy(cs, cb->head, sizeof(struct com_stat));
    advance_head(cb);
    return 0;
}

void dump_circ_buf(struct circ_buf *cb)
{
    struct com_stat *h, *t;

    h = cb->head;
    t = cb->tail;

    printf("begin dump\n");
    while (h != t)
    {
        printf("\t%x %x\n", h->command, h->status);
        h++;
        /* reset to beginning when physical buffer end is reached */
        if (h == buffer_end(cb))
            h = (struct com_stat *)cb->buf;
        if (h == cb->head)
            break;
    }
    printf("end dump\n");

}

int main()
{
    int ret, i;
    struct circ_buf cb;
    struct com_stat cs = {0, 0};

    ret = init_cb(&cb);
    if (ret) {
        printf("malloc error\n");
        return ret;
    }

    for (i=0; i<5; i++) {
        cs.command = i;
        cs.status = i+10;
        ret = enqueue(&cb, cs);
        if (ret) {
            printf("enqueue error %x %x, ret %d\n", cs.command, cs.status, ret);
            return -EINVAL;
        }
        memset((void *)&cs, 0, sizeof(struct com_stat));
    }

    printf("\nspace %d\n", get_space(&cb));
    printf("count %d\n", get_count(&cb));
    dump_circ_buf(&cb);

    cs.command = 0x15;
    cs.status = 0x20;
    printf("enqueue one more returned %d\n", enqueue(&cb, cs));

    for (i=0; i<3; i++) {
        if (dequeue(&cb, &cs)) {
            printf("dequeue error\n");
            break;
        }
        printf("dequeued %x %x\n", cs.command, cs.status);
        memset((void *)&cs, 0, sizeof(struct com_stat));
    }

    for (i=0; i<5; i++) {
        cs.command = 'p'+i;
        cs.status = i+50;
        ret = enqueue(&cb, cs);
        if (ret) {
            printf("enqueue error %x %x, ret %d\n", cs.command, cs.status, ret);
			break;
        }
        memset((void *)&cs, 0, sizeof(struct com_stat));
    }

    dump_circ_buf(&cb);
    free_cb(&cb);
    return 0;
}
