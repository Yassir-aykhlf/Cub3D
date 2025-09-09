/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:52:41 by lazmoud           #+#    #+#             */
/*   Updated: 2025/08/15 16:37:14 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	string_push(t_string *string, char item)
{
	if (!string)
		return (0);
	if (!string->items
		|| !string->cap || string->size + 1 >= string->cap)
	{
		if (!string->cap)
			string->cap = 1;
		string->items = ft_realloc(string->items,
				string->cap * 2,
				string->size);
		if (!string->items)
			return (0);
		string->cap *= 2;
	}
	string->items[string->size++] = item;
	string->items[string->size] = 0;
	return (1);
}

size_t	push_while(t_string *string, char *what,
		size_t start, int (*predicate)(int))
{
	size_t	len;

	len = 0;
	while (predicate(what[start + len]))
	{
		string_push(string,
			what[start + len]);
		len++;
	}
	return (len);
}
