/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:52:59 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/09/18 11:06:02 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
	{
		printf("Error: fatal usage\n");
		printf("Usage: %s <Map>\n", av[0]);
		return (1);
	}
	ft_memset(&game, 0, sizeof(t_game));
	game.map.config_file_path = av[1];
	game.map.ceiling_color = -1;
	game.map.floor_color = -1;
	if (!init_game(&game))
	{
		cleanup_game(&game);
		return (1);
	}
	if (!run_game(&game))
	{
		cleanup_game(&game);
		return (1);
	}
	return (0);
}
