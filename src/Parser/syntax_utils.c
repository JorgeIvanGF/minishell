
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

// The replacement of the origina str from input to the value of ENV-VAR
static char	*replace_var(char *input, char *var, char *value, int pos)
{
	char	*before;
	char	*after;
	char	*new_str;
	char	*final_str;
	int		var_len;

	var_len = ft_strlen(var);
	before = ft_substr(input, 0, pos);
	after = ft_strdup(input + pos + var_len + 1);
	if (!before || !after) // Handle memory failure
		return (NULL);
	if (value) // Normal case: Replace with value
		new_str = ft_strjoin(before, value);
	else // If value is NULL, just remove the $VAR
		new_str = ft_strdup(before);
	free(before);
	final_str = ft_strjoin(new_str, after);
	free(input);
	//here only assign a string to the LOCAL input variable
	//input = ft_strjoin(new_str, after);
	free(new_str);
	free(after);
	return (final_str);
}

// Expand variables inside double quotes or outside quotes
// extra move to verify if is inside single quotes
static char	*expand_env_vars(char *input, char **env)
{
	int		i;
	char	*var;
	char	*value;
	int		in_single;
	char	*new_input;

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
			printf("var = %s\n", var);
			value = get_env_value(var, env); // fetch after the '='
			printf("value = %s\n", value);
			new_input = replace_var(input, var, value, i);
			printf("new_input = %s\n", new_input);
			free(var);
			if (value)
				free(value);
			if (!new_input) // If replacement failed, return NULL
				return (NULL);
			input = new_input;
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
			printf("expanded = %s\n", expanded);
			//printf("token_val_0 = %s\n", token->value);
			if (expanded)
			{
				//printf("token_val_1 = %s\n", token->value);
				//free(token->value);
				token->value = expanded;
				printf("token_val_2 = %s\n", token->value);
				i = -1; // to reprocess the new string formed 
				in_single = 0; //to reset the flag
			}
		//return;
		}
		i++;
	}
}




