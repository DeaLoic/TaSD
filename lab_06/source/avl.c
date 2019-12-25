#include <stdlib.h>
#include "avl.h"
#include "bst.h"
#include "universal.h"

int height(bst_node_t *p)
{
	return p ? p->height : 0;
}

int b_factor(bst_node_t *p)
{
	return height(p->r_son) - height(p->l_son);
}

void fix_height(bst_node_t *p)
{
	int hl = height(p->l_son);
	int hr = height(p->r_son);
	p->height = (hl > hr ? hl : hr) + 1;
}

bst_node_t *rotate_right(bst_node_t *p) // правый поворот вокруг p
{
	bst_node_t *q = p->l_son;
	p->l_son = q->r_son;
	q->r_son = p;
	fix_height(p);
	fix_height(q);
	return q;
}

bst_node_t *rotate_left(bst_node_t *q) // левый поворот вокруг q
{
	bst_node_t *p = q->r_son;
	q->r_son = p->l_son;
	p->l_son = q;
	fix_height(q);
	fix_height(p);
	return p;
}

bst_node_t *balance(bst_node_t *p) // балансировка узла p
{
	fix_height(p);
	if (b_factor(p) == 2)
	{
		if (b_factor(p->r_son) < 0)
        {
            p->r_son = rotate_right(p->r_son);
        }
		return rotate_left(p);
	}
	if (b_factor(p) == -2)
	{
		if (b_factor(p->l_son) > 0)
        {
            p->l_son = rotate_left(p->l_son);
        }
		return rotate_right(p);
	}
	return p; // балансировка не нужна
}

void balance_full(bst_node_t *p)
{
	p->l_son = balance(p->l_son);
	p->r_son = balance(p->r_son);
	p = balance(p);
}
bst_node_t *insert(bst_node_t *p, int data, int *cmp) // вставка ключа k в дерево с корнем p
{
    if (!p)
	{
		*cmp += 1;	
		return create_bst_node(data);
	}
		
	if (data < p->data)
	{
		*cmp += 1;
		p->l_son = insert(p->l_son, data, cmp);
	}
	else if (data > p->data)
	{
		*cmp += 2;
		p->r_son = insert(p->r_son, data, cmp);
	}
	return balance(p);
}

bst_node_t *find_min(bst_node_t *p) // поиск узла с минимальным ключом в дереве p 
{
	return p->l_son ? find_min(p->l_son) : p;
}

bst_node_t *remove_min(bst_node_t *p) // удаление узла с минимальным ключом из дерева p
{
	if (p->l_son == 0)
    {
        return p->r_son;
    }
	p->l_son = remove_min(p->l_son);
	return balance(p);
}

bst_node_t *remove_avl(bst_node_t *p, int data) // удаление ключа k из дерева p
{
	if ( !p ) return 0;
	if (data < p->data)
    {
        p->l_son = remove_avl(p->l_son, data);
    }
	else if (data > p->data)
    {
		p->r_son = remove_avl(p->r_son, data);	
    }
    else 
	{
		bst_node_t *q = p->l_son;
		bst_node_t *r = p->r_son;
		delete_bst_node(p);
		if ( !r ) return q;
		bst_node_t *min = find_min(r);
		min->r_son = remove_min(r);
		min->l_son = q;
		return balance(min);
	}
    return balance(p);
}

void fill_tree_avl(bst_t *tree, FILE *source)
{
    int *cur_digit = (int*)malloc(sizeof(int));
	int cmp = 0;
    while (fscanf(source, "%d", cur_digit) == 1)
    {
        tree->root = insert(tree->root, *cur_digit, &cmp);
        cur_digit = (int*)malloc(sizeof(int));
    }
    free(cur_digit);
}

void empty_dest()
{

};

void balance_bst_to_avl(bst_node_t *root, bst_t *avl)
{
	int cmp = 0;
    if (root)
    {
        balance_bst_to_avl(root->l_son, avl);
        balance_bst_to_avl(root->r_son, avl);
        avl->root = insert(avl->root, root->data, &cmp);
        if (root->father)
        {
            if (root->father->l_son == root)
            {
                root->father->l_son = NULL;
            }
            else
            {
                root->father->r_son = NULL;
            }
            
        }
        delete_bst_node(root);
    }
}