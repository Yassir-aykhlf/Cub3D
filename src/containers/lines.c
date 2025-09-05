/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:53:39 by lazmoud           #+#    #+#             */
/*   Updated: 2025/09/05 10:14:50 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	remove_new_line(char *line)
{
	size_t	size;

	if (!line)
		return ;
	size = strlen(line);
	while (size && line[(size - 1)] == '\n')
	{
		line[size - 1] = 0;
		size--;
	}
}

int	is_empty(char *line)
{
	size_t	char_index;

	if (!line || !*line)
		return (1);
	char_index = strlen(line);
	while (char_index && isspace(line[char_index - 1]))
		char_index--;
	return (char_index == 0);
}

void	push_line(t_lines *const lines, char *line)
{
	if (lines->size == lines->cap)
	{
		if (!lines->cap)
			lines->cap = 1;
		lines->items = ft_realloc(lines->items,
				(lines->cap * 2) * sizeof(char *),
				(lines->size) * sizeof(char *));
		lines->cap *= 2;
	}
	if (is_empty(line))
		free(line);
	else
	{
		remove_new_line(line);
		lines->items[lines->size++] = line;
	}
}

void	destroy_lines(t_lines *const lines)
{
	size_t	k;

	if (lines->items)
	{
		k = 0;
		while (k < lines->size)
		{
			if (lines->items[k])
				free(lines->items[k]);
			lines->items[k] = NULL;
			k++;
		}
		free(lines->items);
		lines->items = NULL;
	}
}
