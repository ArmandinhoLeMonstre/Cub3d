/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:15:01 by armitite          #+#    #+#             */
/*   Updated: 2025/01/12 18:40:18 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr_g(const char *s, int c)
{
	int		i;
	char	p;

	i = 0;
	p = c;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == p)
			return ((char *) &s[i + 1]);
		i++;
	}
	if (s[i] == p)
		return ((char *) &s[i + 1]);
	return (0);
}

char	*ft_fin(char *stash, int fd)
{
	int		counter;
	char	*buffer;

	if (!stash)
		return (NULL);
	while (ft_strchr_g(stash, '\n') == 0)
	{
		buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer)
			return (free(stash), stash = NULL, NULL);
		counter = read(fd, buffer, BUFFER_SIZE);
		if (counter == 0 && ft_strlen(stash) > 0)
		{
			free(buffer);
			break ;
		}
		else if (counter == 0)
			return (free(buffer), free(stash), NULL);
		buffer[counter] = 0;
		stash = ft_strjoin(stash, buffer);
		if (!stash)
			return (free(buffer), NULL);
		free(buffer);
	}
	return (stash);
}

char	*ft_oneline(char *stash, char *res, int x)
{
	int		i;

	if (!stash)
		return (NULL);
	i = 0;
	if (ft_strchr_g(stash, '\n') || ft_strchr_g(stash, '\0'))
	{
		if (ft_strchr_g(stash, '\n'))
			x = ft_strlen(stash) - ft_strlen(ft_strchr_g(stash, '\n'));
		else
			x = ft_strlen(stash);
		res = malloc((x + 1) * sizeof(char));
		if (!res)
			return (NULL);
		while (i < x)
		{
			res[i] = stash[i];
			i++;
		}
	}
	res[i] = 0;
	return (res);
}

char	*get_next_line(int fd)
{
	char		*res;
	static char	*stash;
	char		*temp;

	res = 0;
	if (BUFFER_SIZE < 1 || BUFFER_SIZE > 2147483646)
		return (NULL);
	if (fd < 0 || read(fd, 0, 0) < 0)
		return (free(stash), stash = NULL, NULL);
	if (!stash)
		stash = ft_strdup("");
	stash = ft_fin(stash, fd);
	res = ft_oneline(stash, res, 0);
	if (!res)
		return (free(stash), stash = NULL, NULL);
	temp = ft_strdup(ft_strchr_g(stash, '\n'));
	free(stash);
	if (temp == 0)
		stash = NULL;
	else
		stash = temp;
	return (res);
}

// int	main()
// {
// 	int fd;
// 	int i;
// 	i = 0;
// 	fd = open("txt.txt", O_RDONLY);
// 	printf("la vraie : %s", get_next_line(fd));
// 	// printf("-------------------------------------\n");
// 	//system("leaks a.out");
// 	// printf("la vraie : %s", get_next_line(fd));
// 	// printf("-------------------------------------\n");
// 	// printf("la vraie : %s", get_next_line(fd));
// 	// printf("-------------------------------------\n");
// 	// printf("la vraie : %s", get_next_line(fd));
// 	// printf("-------------------------------------\n");
// 	// printf("la vraie : %s", get_next_line(fd));
// 	// printf("-------------------------------------\n");
// 	// printf("la vraie : %s", get_next_line(fd));
// 	// printf("-------------------------------------\n");
// 	// printf("la vraie : %s", get_next_line(fd));
// 	// printf("-------------------------------------\n");
// 	// printf("la vraie : %s", get_next_line(fd));
// 	// printf("-------------------------------------\n");
// 	//system("leaks a.out");
// }