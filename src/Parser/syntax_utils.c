/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:51:54 by jorgutie          #+#    #+#             */
/*   Updated: 2025/04/02 01:31:27 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

// Look for the environment variable 'var' in the env array
// and return a copy of its value (the part after the =)
// Join the extracted 'name' with '=' to create the prefix
// Check if matches with the ENV-VAR ->fetch the part after '='
char	*get_env_value(char *var, char **env)
{
	int		i;
	char	*prefix;
	char	*value;

	i = 0;
	if (!var || !env)
		return (NULL);
	prefix = ft_strjoin(var, "=");
	while (env[i])
	{
		if (ft_strncmp(env[i], prefix, ft_strlen(prefix)) == 0)
		{
			value = ft_strdup(env[i] + ft_strlen(prefix));
			free(prefix);
			return (value);
		}
		i++;
	}
	free(prefix);
	return (NULL);
}

static char	*handle_dollar(char *input, int i
	, char **env, t_minishell *minishell)
{
	char	*var;
	char	*value;
	char	*new_input;

	if (input[i + 1] == '?')
	{
		var = ft_strdup("?");
		value = ft_itoa(minishell->exit_code);
	}
	else
	{
		var = extract_var_name(&input[i + 1]);
		value = get_env_value(var, env);
	}
	new_input = replace_var(input, var, value, i);
	free(var);
	if (value)
		free(value);
	return (new_input);
}

// If the token is NOT originally DBQ, it toggles an in_single flag
// on encountering SGQ -> Advance past the quote to avoid processing
// it repeatedly -> When a '$' is found outside single quotes,
// it calls handle_dollar to expand the variable.
// Returns the updated input string after processing.
static char	*process_input(char *input, int is_dbq, char **env
	, t_minishell *minishell)
{
	int		i;
	int		in_single;
	char	*new_input;

	i = 0;
	in_single = 0;
	while (input[i])
	{
		if (!is_dbq && input[i] == '\'')
		{
			in_single = !in_single;
			i++;
		}
		else if (input[i] == '$' && !in_single)
		{
			new_input = handle_dollar(input, i, env, minishell);
			if (!new_input)
				return (NULL);
			input = new_input;
		}
		else
			i++;
	}
	return (input);
}

static char	*expand_env_vars(char *input, char **env, t_minishell *minishell)
{
	int		len;
	int		is_dbq;

	if (!input || !env)
		return (NULL);
	len = ft_strlen(input);
	if (len >= 2 && input[0] == '"' && input[len - 1] == '"')
		is_dbq = 1;
	else
		is_dbq = 0;
	return (process_input(input, is_dbq, env, minishell));
}

// Expands environment variables for tokens that are 
// double-quoted (DBQ) or unquoted (WORD).
void	expand_variables(t_token *token, char **env, t_minishell *minishell)
{
	char	*expanded;

	if (!token || !token->value)
		return ;
	if (token->type == DBQ || token->type == WORD)
	{
		expanded = expand_env_vars(token->value, env, minishell);
		if (expanded)
			token->value = expanded;
	}
}
