/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 15:07:02 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/09/05 10:44:44 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

/**
 * Free visited matrix
 */
void	free_visited_matrix(int **visited, size_t height)
{
	int	i;

	if (!visited)
		return ;
	i = 0;
	while (i < (int)height)
	{
		if (visited[i])
			free(visited[i]);
		i++;
	}
	free(visited);
}

/**
 * Check if position was visited
 */
int	is_visited(int **visited, int x, int y)
{
	return (visited[y][x]);
}

/**
 * Mark position as visited
 */
void	mark_visited(int **visited, int x, int y)
{
	visited[y][x] = 1;
}
