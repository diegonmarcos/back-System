/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort_lsd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 20:11:30 by dinepomu          #+#    #+#             */
/*   Updated: 2025/01/31 20:19:39 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Assuming your t_list structure is defined as follows:
/* typedef struct s_list {
    int value;
    int index;
    struct s_list *prev;
    struct s_list *next;
} t_list;
 */

// Function to create a new node
/*
t_list *create_new_node(int value) {
    t_list *new_node = (t_list *)malloc(sizeof(t_list));
    if (!new_node) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }
    new_node->value = value;
    new_node->index = -1; // Initialize index to -1 (as in your selection sort)
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}
*/
// Function to merge two sorted sublists
/*
t_list *merge(t_list *first, t_list *second) {
    // If first list is empty, return second
    if (!first)
        return second;

    // If second list is empty, return first
    if (!second)
        return first;

    // Pick the smaller value
    if (first->value < second->value) {
        first->next = merge(first->next, second);
        first->next->prev = first;
        first->prev = NULL; // Redundant as first is head
        return first;
    } else {
        second->next = merge(first, second->next);
        second->next->prev = second;
        second->prev = NULL; // Redundant as second is head
        return second;
    }
}*/

// Function to split the doubly linked list into two halves
/*
t_list *split(t_list *head) {
    t_list *fast = head;
    t_list *slow = head;

    while (fast->next && fast->next->next) {
        fast = fast->next->next;
        slow = slow->next;
    }

    t_list *temp = slow->next;
    slow->next = NULL;
    if(temp)
        temp->prev = NULL; 
    return temp;
}*/

// Recursive function to perform merge sort
/*
t_list *merge_sort(t_list *head) {
    if (!head || !head->next) {
        return head;
    }

    t_list *second = split(head);

    // Recursively sort the two halves
    head = merge_sort(head);
    second = merge_sort(second);

    // Merge the sorted halves
    return merge(head, second);
}*/

// Function to assign index numbers after sorting
/* void assign_index_numbers(t_list *head) {
    int index = 0;
    while (head) {
        head->index = index++;
        head = head->next;
    }
}
 */
// Function to insert a new node at the beginning (for testing)
/* void insert_at_beginning(t_list **head_ref, int new_value) {
    t_list *new_node = create_new_node(new_value);
    new_node->next = *head_ref;
    if (*head_ref)
        (*head_ref)->prev = new_node;
    *head_ref = new_node;
} */
// Function to print the list (for testing)
/* void print_list(t_list *head) {
    while (head) {
        printf("Value: %d, Index: %d\n", head->value, head->index);
        head = head->next;
    }
    printf("\n");
} */

/* 
int main() {
    // Example usage:
    t_list *head = NULL;
    insert_at_beginning(&head, 5);
    insert_at_beginning(&head, 20);
    insert_at_beginning(&head, 4);
    insert_at_beginning(&head, 3);
    insert_at_beginning(&head, 30);
    insert_at_beginning(&head, 10);

    printf("Original List:\n");
    print_list(head);

    head = merge_sort(head);
    assign_index_numbers(head);

    printf("Sorted List with Indexes:\n");
    print_list(head);

    return 0;
} */