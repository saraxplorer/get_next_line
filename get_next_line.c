/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/20 21:50:56 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/01/22 19:05:38 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "get_next_line.h"

char	*read_concate(int fd, char *buffer, char *storage)
{
	int		read_result;
	char	*char_temp;

	read_result = 1;
	while (read_result != 0)
	{
		read_result = read(fd, buffer, BUFFER_SIZE);
		if (read_result == -1)
			return (0);
		else if (read_result == 0)
			break ;
		buffer[read_result] = '\0';
		if (!storage)
			storage = ft_strdup("");
		char_temp = storage;
		storage = ft_strjoin(char_temp, buffer);
		free(char_temp);
		char_temp = NULL;
		if (ft_strchr (buffer, '\n'))
			break ;
	}
	return (storage);
}

char	*remaining_after_n(char *line)
{
	size_t	count;
	char	*remaining;

	count = 0;
	while (line[count] != '\n' && line[count] != '\0')
		count++;
	if (line[count] == '\0')
		return (0);
	remaining = ft_substr(line, count + 1, ft_strlen(line) - count);
	if (remaining != NULL && *remaining == '\0')
	{
		free(remaining);
		remaining = NULL;
	}
	line[count + 1] = '\0';
	return (remaining);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*storage;

	if (fd < 0 || BUFFER_SIZE <= 0 || read (fd, NULL, 0) == -1)
	{
		if (storage != 0)
		{
			free (storage);
			storage = NULL;
		}
		return (0);
	}
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (0);
	line = read_concate(fd, buffer, storage);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	storage = remaining_after_n(line);
	return (line);
}

// int	main(void)
// {
// 	char	*line;
// 	int		count;
// 	int		fd1;
// 	int		fd2;
// 	int		fd3;
// 	fd1 = open("example.txt", O_RDONLY);
// 	fd2 = open("example1.txt", O_RDONLY);
// 	fd3 = open("example2.txt", O_RDONLY);
// 	count = 1;
// 	while (count < 2)
// 	{
// 		line = get_next_line(fd1);
// 		printf("line [%d]: %s", count, line);
// 		free(line);
// 		 if (line && line[strlen(line) - 1] == '\n') {
//             printf(" - Includes newline character\n");
//         } else {
//             printf(" - Does not include newline character\n");
//         }
// 		line = get_next_line(fd2);
// 		printf("line [%02d]: %s", count, line);
// 		free(line);
// 		if (line && line[strlen(line) - 1] == '\n') {
//             printf(" - Includes newline character\n");
//         } else {
//             printf(" - Does not include newline character\n");
//         }
// 		line = get_next_line(fd3);
// 		printf("line [%02d]: %s", count, line);
// 		free(line);
// 		if (line && line[strlen(line) - 1] == '\n') {
//             printf(" - Includes newline character\n");
//         } else {
//             printf(" - Does not include newline character\n");
//         }
// 		count++;
// 	}
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// 	return (0);
// }