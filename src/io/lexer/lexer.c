/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:14:50 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/09/09 10:36:52 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

char	lexer_current_char(t_lexer_state *lexer)
{
	return (lexer_char_at(lexer, lexer->cursor));
}

void	skip_whitespace(t_lexer_state *lexer)
{
	if (lexer_exhausted(lexer))
		return ;
	while (lexer_current_char(lexer)
		&& isspace(lexer_current_char(lexer)))
		lexer->cursor++;
}

int	lexer_eol_reached(t_lexer_state *lexer)
{
	if ((lexer->line_index < lexer->lines->size)
		&& (lexer_current_char(lexer) == 0))
	{
		lexer->line_index++;
		lexer->cursor = 0;
		return (1);
	}
	return (0);
}

int	lexer_exhausted(t_lexer_state *lexer)
{
	return ((!lexer->lines->size)
		|| (lexer->line_index > lexer->lines->size - 1));
}

int	lexer_eof_reached(t_lexer_state *lexer)
{
	if (lexer_exhausted(lexer))
	{
		lexer->current->type = EOF_;
		return (1);
	}
	return (0);
}
