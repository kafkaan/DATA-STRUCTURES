/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

#include <stdio.h>
#include <stdlib.h>

struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode *invertTree(struct TreeNode *root)
{
    if (root == NULL)
    {
        return NULL;
    }

    // Inversion gauche ↔ droite avec une variable temporaire
    struct TreeNode *temp = root->left;
    root->left = root->right;
    root->right = temp;

    // Appel récursif sur les sous-arbres maintenant inversés
    invertTree(root->left);
    invertTree(root->right);

    return root;
}
