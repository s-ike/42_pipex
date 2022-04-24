#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#include "ft_error.h"
#include "def_pipex.h"
#include "def_error.h"

static void
	child_process(char **argv, char **environ, int fds[PIPE_NUM])
{
	int	fd;

	(void)environ;
	close(fds[PIPE_R]);
	if ((fd = open(argv[ARG_FILE1], O_RDONLY, 0666)) < 0)
	{
		ft_puterror_and_exit_failure(ft_putperror, argv[ARG_FILE1]);
	}

	dup2(fds[PIPE_W], STDOUT_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fds[PIPE_W]);
	close(fd);

	char	*av[2];
	av[0] = argv[ARG_CMD1];
	av[1] = NULL;
	execvp(argv[ARG_CMD1], av);
	ft_puterror_and_exit_failure(ft_putperror, argv[ARG_CMD1]);
}

static void
	parent_process(char **argv, char **environ, int fds[PIPE_NUM])
{
	(void)environ;
	close(fds[PIPE_W]);

	dup2(fds[PIPE_R], STDIN_FILENO);
	close(fds[PIPE_R]);

	int	fd;
	if ((fd = open(argv[ARG_FILE2], O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0)
	{
		ft_puterror_and_exit_failure(ft_putperror, argv[ARG_FILE2]);
	}

	dup2(fd, STDOUT_FILENO);
	close(fd);

	char	*av[2];
	av[0] = argv[ARG_CMD2];
	av[1] = NULL;

	execvp(argv[ARG_CMD2], av);
	ft_puterror_and_exit_failure(ft_putperror, argv[ARG_CMD2]);
}

static void
	main_process(char **argv, char **environ)
{
	int	fds[PIPE_NUM];
	pid_t	pid;

	if (pipe(fds) < 0)
	{
		ft_puterror_and_exit_failure(ft_putperror, "pipe");
	}
	pid = fork();
	if (pid < 0)
	{
		ft_puterror_and_exit_failure(ft_putperror, "fork");
	}
	else if (pid == 0)
	{
		child_process(argv, environ, fds);
	}
	if (wait(NULL) != pid)
	{
		ft_puterror_and_exit_failure(ft_putperror, "wait");
	}
	parent_process(argv, environ, fds);
}

int
	main(int argc, char **argv)
{
	extern char	**environ;

	if (argc != ARG_NUM)
	{
		ft_puterror_and_exit_failure(ft_puterror, ERR_INVAL);
	}
	main_process(argv, environ);
	return (EXIT_FAILURE);
}
