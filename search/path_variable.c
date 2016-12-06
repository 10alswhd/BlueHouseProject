int	my_strncmp(char *s1, char *s2, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		if (s2[i] != s1[i])
			return (0);
		i++;
	}
	return (1);
}

char	*search_path_variable(char **envp)
{
	int	i;
	char	*path_var;
	
	i = -1;
	while (envp[i++])
		if (my_strncmp(envp[i], "PATH", 4) == 1)
			path_var = envp[i];
	return (path_var);
}
