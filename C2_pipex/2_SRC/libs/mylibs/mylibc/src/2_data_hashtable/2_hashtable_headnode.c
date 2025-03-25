/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_headnode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 20:00:35 by dinepomu          #+#    #+#             */
/*   Updated: 2025/01/31 20:19:39 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include <stdio.h>
#include <stdlib.h>
#include <string.h>
 */
/*
typedef struct s_hash_node
{
	char *key;
	int value;
	struct s_hash_node *next;
} t_hash_node;

typedef struct s_hash_table
{
	int size;
	t_hash_node **table;
} t_hash_table;

unsigned int hash(const char *key, int size)
{
	unsigned int hash = 5381;
	int c;

	while ((c = *key++))
		hash = ((hash << 5) + hash) + c;
	return (hash % size);
}

t_hash_table *create_hash_table(int size)
{
	t_hash_table *ht;

	ht = (t_hash_table *)malloc(sizeof(t_hash_table));
	if (ht == NULL) {
		fprintf(stderr, "Error: Memory allocation failed for hash table\n");
		return (NULL);
	}
	ht->size = size;
	ht->table = (t_hash_node **)calloc(size, sizeof(t_hash_node *));
	if (ht->table == NULL) {
		fprintf(stderr, "Error: HasMap ALloc\n");
		free(ht);
		return (NULL);
	}
	return (ht);
}

t_hash_node *create_node(const char *key, int value)
{
	t_hash_node *new_node;

	new_node = (t_hash_node *)malloc(sizeof(t_hash_node));
	if (new_node == NULL) {
		fprintf(stderr, "Error: Memory allocation failed for node\n");
		return (NULL);
	}
	new_node->key = strdup(key);
	if (new_node->key == NULL) {
		fprintf(stderr, "Error: Memory allocation failed for key\n");
		free(new_node);
		return (NULL);
	}
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

void insert(t_hash_table *ht, const char *key, int value)
{
	unsigned int index;
	t_hash_node *new_node;

	index = hash(key, ht->size);
	new_node = create_node(key, value);
	if (new_node == NULL)
		return;
	if (ht->table[index] == NULL)
		ht->table[index] = new_node;
	else {
		new_node->next = ht->table[index];
		ht->table[index] = new_node;
	}
}

int get(t_hash_table *ht, const char *key)
{
	unsigned int index;
	t_hash_node *current;

	index = hash(key, ht->size);
	current = ht->table[index];
	while (current != NULL) {
		if (strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (-1);
}

void free_hash_table(t_hash_table *ht)
{
	int i;
	t_hash_node *current;
	t_hash_node *temp;

	if (ht == NULL)
		return;
	i = 0;
	while (i < ht->size) {
		current = ht->table[i];
		while (current != NULL) {
			temp = current;
			current = current->next;
			free(temp->key);
			free(temp);
		}
		i++;
	}
	free(ht->table);
	free(ht);
}
*/
/*
int main(void) {
	t_hash_table *ht;

	ht = create_hash_table(10);
	if (ht == NULL)
		return (1);
	insert(ht, "apple", 1);
	insert(ht, "banana", 2);
	insert(ht, "cherry", 3);
	insert(ht, "date", 4);
	insert(ht, "e", 5);
	printf("Value of apple: %d\n", get(ht, "apple"));
	printf("Value of banana: %d\n", get(ht, "banana"));
	printf("Value of cherry: %d\n", get(ht, "cherry"));
	printf("Value of date: %d\n", get(ht, "date"));
	printf("Value of e: %d\n", get(ht, "e"));
	printf("Value of grape: %d\n", get(ht, "grape"));
	free_hash_table(ht);
	return (0);
}
*/