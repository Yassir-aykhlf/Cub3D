/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:15:00 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/09/05 15:44:35 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	get_and_validate_token(t_lexer_state *lexer, t_token_type expected_type,
		t_token *token)
{
	init_token(token);
	get_next_token(lexer, token);
	if (token->type != expected_type)
	{
		cleanup_token(token);
		return (CUBE_FAILURE);
	}
	return (CUBE_SUCCESS);
}

int	get_rgb_component(t_lexer_state *lexer)
{
	t_token	token;
	int		value;

	if (get_and_validate_token(lexer, NUMBER, &token) == CUBE_FAILURE)
		return (CUBE_FAILURE);
	value = token.u_data.number_data;
	cleanup_token(&token);
	return (value);
}

int	skip_separator(t_lexer_state *lexer)
{
	t_token	token;

	if (get_and_validate_token(lexer, SEPARATOR, &token) == CUBE_FAILURE)
		return (CUBE_FAILURE);
	cleanup_token(&token);
	return (0);
}

int	parse_rgb_color(t_lexer_state *lexer)
{
	int	r;
	int	g;
	int	b;

	r = get_rgb_component(lexer);
	if (r == CUBE_FAILURE || skip_separator(lexer) == CUBE_FAILURE)
		return (CUBE_FAILURE);
	g = get_rgb_component(lexer);
	if (g == CUBE_FAILURE || skip_separator(lexer) == CUBE_FAILURE)
		return (CUBE_FAILURE);
	b = get_rgb_component(lexer);
	if (b == CUBE_FAILURE)
		return (CUBE_FAILURE);
	return ((r << 16) | (g << 8) | (b << 0));
}
