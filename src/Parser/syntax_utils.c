
#include "minishell.h"
#include "parsing.h"

// Extract variable name (in the input string) after $
static char	*extract_var_name(const char *str)
{
	int		i;
	char	*var_name;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_')) // skip numbers and _
		i++;
	var_name = ft_substr(str, 0, i); // ****** VERIFY FREE (MALOC)
	return (var_name);
}

// Look for the environment variable 'var' in the env array
// and return a copy of its value (the part after the =)
static char	*get_env_value(char *var, char **env)
{
	int		i;
	char	*prefix;
	char	*value;

	i = 0;
	if (!var || !env)
		return (NULL);
	prefix = ft_strjoin(var, "="); // join the extracted 'name' with '=' to create the prefix
	while (env[i])
	{
		if (ft_strncmp(env[i], prefix, ft_strlen(prefix)) == 0) // if matches with the ENV-VAR
		{
			value = ft_strdup(env[i] + ft_strlen(prefix)); // to fetch the part after '='
			free(prefix);
			return (value);
		}
		i++;
	}
	free(prefix);
	return (NULL);
}

// When a '$' at index i, extracts the name
// retrieves its value from the ENV,
// replaces "$VAR" in the input string with the value, 
// frees temp memory,and returns the updated string
static char	*handle_dollar(char *input, int i, char **env)
{
	char	*var;
	char	*value;
	char	*new_input;

	var = extract_var_name(&input[i + 1]);
	value = get_env_value(var, env);
	new_input = replace_var(input, var, value, i);
	free(var);
	if (value)
		free(value);
	return (new_input);
}

// If the token is NOT originally DBQ, it toggles an in_single flag
// on encountering SGQ. When a '$' is found outside single quotes,
// it calls handle_dollar to expand the variable.
// Returns the updated input string after processing.
static char	*process_input(char *input, int is_dbq, char **env)
{
	int		i;
	int		in_single;
	char	*new_input;

	i = 0;
	in_single = 0;
	while (input[i])
	{
		// if (!is_dbq && input[i] == '\'') // if is DBQ this NEVER ENTER
		// 	in_single = !in_single;

		if (!is_dbq && input[i] == '\'')  // single quote encountered outside of double quotes
		{
			in_single = !in_single;
			i++;  // Advance past the quote to avoid processing it repeatedly
		}
		else if (input[i] == '$' && !in_single)
		{
			new_input = handle_dollar(input, i, env);
			if (!new_input)
				return (NULL);
			input = new_input;
		}
		else
			i++;
	}
	return (input);
}

static char	*expand_env_vars(char *input, char **env)
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
	return (process_input(input, is_dbq, env));
}

// Expands environment variables for tokens that are double-quoted (DBQ) or unquoted (WORD).
void expand_variables(t_token *token, char **env)
{
	char *expanded;

	if (!token || !token->value)
		return;
	if (token->type == DBQ || token->type == WORD)
	{
		expanded = expand_env_vars(token->value, env);
		if (expanded)
			token->value = expanded;
	}
}