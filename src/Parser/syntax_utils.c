
#include "minishell.h"
#include "parsing.h"

// Remove external (single and double) quotes.
void	remove_external_quotes(t_token *token)
{
	char	*new_value;
	int		len;

	if (!token || !token->value)
		return;
	len = ft_strlen(token->value);
	if ((token->value[0] == '"' && token->value[len - 1] == '"')
		|| (token->value[0] == '\'' && token->value[len - 1] == '\''))
	{
		new_value = ft_substr(token->value, 1, len - 2);
		free(token->value);
		token->value = new_value;
	}
}
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

// The replacement of the origina str from input to the value of ENV-VAR
char	*replace_var(char *input, char *var, char *value, int pos)
{
	char	*before;
	char	*after;
	char	*new_str;
	int		var_len;

	var_len = ft_strlen(var);
	before = ft_substr(input, 0, pos);
	after = ft_strdup(input + pos + var_len + 1);
	new_str = ft_strjoin(before, value ? value : "");
	free(before);
	free(input);
	input = ft_strjoin(new_str, after);
	free(new_str);
	free(after);
	return (input);
}

// Expand variables inside double quotes or outside quotes
// extra move to verify if is inside single quotes
char	*expand_env_vars(char *input, char **env)
{
	int		i;
	char	*var;
	char	*value;
	int		in_single;

	if (!input || !env)
		return (NULL);
	i = 0;
	in_single = 0;
	while (input[i])
	{
		if (input[i] == '\'') // Flag to verify if is inside single quotes
			in_single = !in_single;
		else if (input[i] == '$' && !in_single)
		{
			var = extract_var_name(&input[i + 1]); // one position after ´$´
			value = get_env_value(var, env); // fetch after the '=' 
			input = replace_var(input, var, value, i);
			free(var);
			free(value);
			i--; // Adjust index after replacement
		}
		i++;
	}
	return (input);
}

// expand environment variables, but ignore inside single quotes
void expand_variables(t_token *token, char **env)
{
	char	*expanded;
	int		i;
	int		in_single;

	if (!token || !token->value)
		return;
	i = 0;
	in_single = 0; // flag to verify if inside single quotes
	while (token->value[i])
	{
		if (token->value[i] == '\'')
			in_single = !in_single;
		else if (token->value[i] == '$' && !in_single)
		{
			expanded = expand_env_vars(token->value, env);
			if (expanded)
			{
				free(token->value);
				token->value = expanded;
			}
		return;
		}
		i++;
	}
}




