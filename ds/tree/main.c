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

	tree_mid_traval(tree);

	return 0;
}

