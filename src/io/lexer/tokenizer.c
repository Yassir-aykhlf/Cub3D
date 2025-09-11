/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:14:41 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/09/09 10:36:52 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	is_valid_map_character(int c)
{
	return ((c == ' ')
		|| (c == '1')
		|| (c == '0')
		|| (c == 'N')
		|| (c == 'S')
		|| (c == 'E')
		|| (c == 'W'));
}

static int	is_map_line(t_lexer_state *lexer)
{
	size_t	index;

	index = lexer->cursor;
	while (is_valid_map_character(lexer_char_at(lexer, index)))
		index++;
	return (lexer_char_at(lexer, index) == 0);
}

int	lexer_expect_token(t_lexer_state *lexer,
		t_token_type expected_type, t_token *token)
{
	t_token			temp;
	t_lexer_state	lexer_save;

	init_token(&temp);
	lexer_save = *lexer;
	get_next_token(lexer, &temp);
	if (expected_type == temp.type)
	{
		*token = temp;
		return (1);
	}
	*lexer = lexer_save;
	cleanup_token(&temp);
	return (0);
}

int	isdigits(t_lexer_state *lexer)
{
	size_t	index;

	index = lexer->cursor;
	while (isdigit(lexer_char_at(lexer, index)))
		index++;
	return ((lexer_char_at(lexer, index) == 0)
		|| lexer_char_at(lexer, index) == COMA);
}

void	get_next_token(t_lexer_state *lexer, t_token *token)
{
	lexer->current = token;
	if (lexer_eof_reached(lexer))
		return ;
	if (lexer_eol_reached(lexer))
	{
		get_next_token(lexer, token);
		return ;
	}
	if (!lexer->cursor && is_map_line(lexer))
	{
		lexer_read_map_line(lexer);
		return ;
	}
	skip_whitespace(lexer);
	if (lexer_current_char(lexer) == COMA)
	{
		lexer->current->type = SEPARATOR;
		lexer->cursor++;
		return ;
	}
	if (isdigits(lexer))
		lexer_read_number(lexer);
	else
		lexer_read_word(lexer);
}
