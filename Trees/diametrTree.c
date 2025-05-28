
#include <stdlib.h>

struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int maxDiameter = 0;

int diameterHelper(struct TreeNode *root)
{
    if (root == NULL)
        return 0;

    int left = diameterHelper(root->left);
    int right = diameterHelper(root->right);

    if (left + right > maxDiameter)
        maxDiameter = left + right;

    return 1 + (left > right ? left : right);
}

int diameterOfBinaryTree(struct TreeNode *root)
{
    maxDiameter = 0;  // Réinitialiser pour chaque appel
    diameterHelper(root);
    return maxDiameter;
}
