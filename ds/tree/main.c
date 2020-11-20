#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct  {
	int id;
}data_t;

struct node_st {
	data_t data;
	struct node_st *left;
	struct node_st *right;
};

// 插入
int tree_insert(struct node_st **root, const data_t *d)
{
	struct node_st *new = NULL;

	if (*root == NULL) {
		new = malloc(sizeof(*new));
		if (NULL == new)
			return -1;
		memcpy(&new->data, d, sizeof(data_t));
		new->left = new->right = NULL;
		*root = new;
		return 0;
	}

	if ((*root)->data.id >= d->id)
		return tree_insert(&(*root)->left, d);
	else
		return tree_insert(&(*root)->right, d);
}

// 中序遍历
void tree_mid_traval(const struct node_st *root)
{
	if (root == NULL)
		return;

	tree_mid_traval(root->left);
	printf("%d\n", root->data.id);
	tree_mid_traval(root->right);
}

// destroy
void tree_destroy(struct node_st **root)
{
	if (*root == NULL)
		return;
	tree_destroy(&(*root)->left);
	tree_destroy(&(*root)->right);
	printf("%d 将被销毁\n", (*root)->data.id);
	free(*root);
	*root = NULL;
}

// 画树
void tree_show(const struct node_st *root, int level)
{
	if (root == NULL)
		return ;
	tree_show(root->right, level+1);
	for (int i = 0; i < level; i++) {
		printf("    ");
	}
	printf("%d\n", root->data.id);
	tree_show(root->left, level+1);
}

static struct node_st **__find(struct node_st **root, int id)
{
	if (root == NULL)	
		return NULL;
	if ((*root)->data.id == id)
		return root;
	if ((*root)->data.id < id) {
		__find(&(*root)->right, id);
	} else {
		__find(&(*root)->left, id);
	}
}

static struct node_st *maxNode(struct node_st *root)
{
	if (root->right == NULL)
		return root;
	maxNode(root->right);
}

static void __delete(struct node_st **root)
{
	struct node_st *l, *r, *cur;

	l = (*root)->left;
	r = (*root)->right;
	cur = *root;

	if (l != NULL) {
		*root = l;
		maxNode(l)->right = r;
	} else {
		*root = r;
	}
	cur->left = cur->right = NULL;
	free(cur);
}

// 删
int tree_delete(struct node_st **root, int id)
{
	struct node_st **f;	

	f = __find(root, id);
	if (NULL == f)
		return -1;

	__delete(f);

	return 0;
}

int main(int argc, char *argv[])
{
	struct node_st *tree = NULL;
	data_t dt;

	if (argc < 2)
		return 1;

	for (int i = 0; argv[1][i]; i++) {
		dt.id = argv[1][i]-'0';
		tree_insert(&tree, &dt);
	}

	tree_show(tree, 0);

//	tree_mid_traval(tree);
	
	printf("***************delete*********************\n");

	tree_delete(&tree, 6);
	tree_show(tree, 0);

	tree_destroy(&tree);

	return 0;
}

