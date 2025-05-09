/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode
{
    int val;
    struct ListNode *next;
};

/**
 * Add two numbers represented as linked lists.
 * The digits are stored in reverse order, and each of their nodes contains a single digit.
 * @param l1 The first linked list representing a non-negative integer
 * @param l2 The second linked list representing a non-negative integer
 * @return The sum of the two numbers as a linked list
 */
struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2)
{
    // Initialize the result list with a dummy head node
    struct ListNode *head = malloc(sizeof(struct ListNode));
    head->val = 0;
    head->next = NULL;
    // Create a pointer to the current node in the result list
    struct ListNode *current = head;
    // Initialize the carry to 0
    int carry = 0;
    // Loop over both input lists until both are empty and there is no carry
    while (l1 || l2 || carry)
    {
        // Calculate the sum of the digits and the carry
        int sum = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + carry;
        carry = sum / 10;
        // Create a new node for the result list and set its value
        struct ListNode *new_node = malloc(sizeof(struct ListNode));
        new_node->val = sum % 10;
        new_node->next = NULL;
        // Add the new node to the result list
        current->next = new_node;
        current = new_node;
        // Move to the next node in both input lists
        l1 = l1 ? l1->next : NULL;
        l2 = l2 ? l2->next : NULL;
    }
    // Return the result list without the dummy head node
    struct ListNode *result = head->next;
    free(head);
    return result;
}