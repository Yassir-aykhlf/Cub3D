/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 09:37:43 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/09/05 10:11:17 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	destroy_connection(void *mlx_ptr)
{
	if (mlx_ptr)
	{
		mlx_destroy_display(mlx_ptr);
		free(mlx_ptr);
	}
}

int	init_window(t_window *window, int width, int height, char *title)
{
	window->mlx_ptr = mlx_init();
	if (!window->mlx_ptr)
		return (0);
	window->width = width;
	window->height = height;
	window->window = mlx_new_window(window->mlx_ptr, width, height, title);
	if (!window->window)
	{
		destroy_connection(window->mlx_ptr);
		return (0);
	}
	return (1);
}

void	cleanup_window(t_window *window)
{
	if (window->window)
		mlx_destroy_window(window->mlx_ptr, window->window);
	destroy_connection(window->mlx_ptr);
}
