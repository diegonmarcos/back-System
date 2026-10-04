/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_headarray.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:43:05 by dinepomu          #+#    #+#             */
/*   Updated: 2025/01/31 20:38:26 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylibc.h"

/*
typedef struct s_node_
{
	char				*key;
	int					value;
	struct s_node_	*next;
}						t_node_;
*/
/* unsigned int	hash(const char *key, int size)
{
	unsigned int	hash;
	int				c;

	hash = 5381;
	while ((c = *key++))
		hash = ((hash << 5) + hash) + c;
	return (hash % size);
}

t_node_	*create_node(const char *key, int value)
{
	t_node_	*new_node;

	new_node = (t_node_ *)malloc(sizeof(t_node_));
	if (new_node == NULL)
	{
		fprintf(stderr, "Error: Memory allocation failed for node\n");
		return (NULL);
	}
	new_node->key = strdup(key);
	if (new_node->key == NULL)
	{
		fprintf(stderr, "Error: Memory allocation failed for key\n");
		free(new_node);
		return (NULL);
	}
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

void	insert(t_node_ **table, int size, const char *key, int value)
{
	unsigned int	index;
	t_node_		*new_node;

	index = hash(key, size);
	new_node = create_node(key, value);
	if (new_node == NULL)
		return ;
	if (table[index] == NULL)
		table[index] = new_node;
	else
	{
		new_node->next = table[index];
		table[index] = new_node;
	}
}

int	get(t_node_ **table, int size, const char *key)
{
	unsigned int	index;
	t_node_		*current;

	index = hash(key, size);
	current = table[index];
	while (current != NULL)
	{
		if (strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (-1);
}

void	free_hashtable(t_node_ **table, int size)
{
	int			i;
	t_node_	*current;
	t_node_	*temp;

	if (table == NULL)
		return ;
	i = 0;
	while (i < size)
	{
		current = table[i];
		while (current != NULL)
		{
			temp = current;
			current = current->next;
			free(temp->key);
			free(temp);
		}
		i++;
	}
	free(table);
} */

/* int	main(void)
{
	int			size;
	t_node_	**table;

	size = 10;
	table = (t_node_ **)calloc(size, sizeof(t_node_ *));
	if (table == NULL)
	{
		fprintf(stderr, "Error: Memory\n");
		return (1);
	}
	insert(table, size, "apple", 1);
	insert(table, size, "banana", 2);
	insert(table, size, "cherry", 3);
	insert(table, size, "date", 4);
	insert(table, size, "e", 5);
	printf("Value of apple: %d\n", get(table, size, "apple"));
	printf("Value of banana: %d\n", get(table, size, "banana"));
	printf("Value of cherry: %d\n", get(table, size, "cherry"));
	printf("Value of date: %d\n", get(table, size, "date"));
	printf("Value of e: %d\n", get(table, size, "e"));
	printf("Value of grape: %d\n", get(table, size, "grape"));
	free_hashtable(table, size);
	return (0);
} */
