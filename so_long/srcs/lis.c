#include "../push_swap.h"

void liss(int *v, int len, t_numb **stack)
{
	int i;
	struct node *p;
    struct node *n;

    n = (struct node*) malloc(sizeof(*n) * len);
	i = -1;
    while (++i < len)
        n[i].val = v[i];
    while (i-- > 0)
    {
        p = n + i;
        while (p++ < n + len)
        {
            if (p->val > n[i].val && p->len >= n[i].len)
            {
                n[i].next = p;
                n[i].len = p->len + 1;
            }
        }
    }
    p = n;
    while (++i < len)
		if (n[i].len > p->len) 
            p = n + i;
    tagger(stack, p, len);
}