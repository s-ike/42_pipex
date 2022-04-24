#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#include "ft_error.h"
#include "def_pipex.h"
#include "def_error.h"

int
	main(int ac, char **av)
{
	extern char	**environ;

	if (ac != ARG_NUM)
	{
		ft_puterror_and_exit_failure(ft_puterror, ERR_INVAL);
	}

	int	fds[PIPE_NUM];

	if (pipe(fds) < 0)
	{
		ft_puterror_and_exit_failure(ft_putperror, "pipe");
	}

	pid_t	pid = fork();
	if (pid < 0)
	{
		ft_puterror_and_exit_failure(ft_putperror, "fork");
	}
	else if (pid == 0)
	{
		close(fds[PIPE_R]);

		int	fd;
		if ((fd = open(av[ARG_FILE1], O_RDONLY, 0666)) < 0)
		{
			ft_puterror_and_exit_failure(ft_putperror, av[ARG_FILE1]);
		}

		dup2(fds[PIPE_W], STDOUT_FILENO);
		dup2(fd, STDIN_FILENO);
		close(fds[PIPE_W]);
		close(fd);

		char	*argv[2];
		argv[0] = av[ARG_CMD1];
		argv[1] = NULL;
		execvp(av[ARG_CMD1], argv);
		ft_puterror_and_exit_failure(ft_putperror, av[ARG_CMD1]);
	}
	if (wait(NULL) != pid)
	{
		ft_puterror_and_exit_failure(ft_putperror, "wait");
	}
	{
		close(fds[PIPE_W]);

		dup2(fds[PIPE_R], STDIN_FILENO);
		close(fds[PIPE_R]);

		int	fd;
		if ((fd = open(av[ARG_FILE2], O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0)
		{
			ft_puterror_and_exit_failure(ft_putperror, av[ARG_FILE2]);
		}

		dup2(fd, STDOUT_FILENO);
		close(fd);

		char	*argv[2];
		argv[0] = av[ARG_CMD2];
		argv[1] = NULL;

		execvp(av[ARG_CMD2], argv);
		ft_puterror_and_exit_failure(ft_putperror, av[ARG_CMD2]);
	}
	return (EXIT_FAILURE);
}
