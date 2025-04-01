/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:51:51 by jorgutie          #+#    #+#             */
/*   Updated: 2025/04/02 00:51:52 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

// Extract variable name (in the input string) after $
// skip numbers and _ 
char	*extract_var_name(const char *str)
{
	int		i;
	char	*var_name;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	var_name = ft_substr(str, 0, i);
	return (var_name);
}

// The replacement of the original str from input to the value of ENV-VAR
// Handle memory failure-> Normal case: Replace with value
// If value is NULL, just remove the $VAR
char	*replace_var(char *input, char *var, char *value, int pos)
{
	char	*before;
	char	*after;
	char	*new_str;
	char	*final_str;
	int		var_len;

	var_len = ft_strlen(var);
	before = ft_substr(input, 0, pos);
	after = ft_strdup(input + pos + var_len + 1);
	if (!before || !after)
		return (NULL);
	if (value)
		new_str = ft_strjoin(before, value);
	else
		new_str = ft_strdup(before);
	free(before);
	final_str = ft_strjoin(new_str, after);
	free(input);
	free(new_str);
	free(after);
	return (final_str);
}

// Removal of the external quotes (single and double)
void	remove_external_quotes(t_token *token)
{
	char	*new_value;
	int		len;

	if (!token || !token->value)
		return ;
	len = ft_strlen(token->value);
	if ((token->value[0] == '"' && token->value[len - 1] == '"')
		|| (token->value[0] == '\'' && token->value[len - 1] == '\''))
	{
		new_value = ft_substr(token->value, 1, len - 2);
		free(token->value);
		token->value = new_value;
	}
}
