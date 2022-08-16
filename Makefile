NAME		:= pipex

SRCDIR		:= ./srcs/
OBJDIR		:= ./objs/
VPATH		:= $(SRCDIR):$(SRCDIR)$(UTILDIR)

SRCS		:= main.c \
				ft_error.c \
				ft_execute.c \
				ft_free.c \
				ft_get_cmd_path.c
SRCS		:= $(addprefix $(SRCDIR), $(SRCS))
OBJS		:= $(addprefix $(OBJDIR), $(notdir $(SRCS:.c=.o)))
DEPENDS		:= $(addprefix $(OBJDIR), $(notdir $(SRCS:.c=.d)))

LIBDIR		:= ./libft
LIBPATH		:= $(LIBDIR)/libft.a
LFLAGS		:= -L${LIBDIR} -lft

INCLUDE 	:= -I./includes/ -I./includes/defs/  -I$(LIBDIR)

CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror -MMD -MP

ifdef MEM
DEBUG		:= -fsanitize=address
else
DEBUG		:=
endif

RM			:= rm -f
C_GREEN		:= "\033[32m"
C_DEFAULT	:= "\033[39m"
C_RESET		:= "\033[m"


$(OBJDIR)%.o:	%.c
			@if [ ! -d $(OBJDIR) ]; then \
				echo ";; mkdir $(OBJDIR)"; mkdir $(OBJDIR); \
			fi
			$(CC) $(CFLAGS) $(DEBUG) $(INCLUDE) -c $< -o $@

.PHONY:		all
all:		$(NAME)

$(NAME):	$(LIBPATH) $(OBJS)
			$(CC) $(CFLAGS) $(DEBUG) $(OBJS) $(LFLAGS) -o $@
			@echo $(C_GREEN)"=== Make Done ==="$(C_DEFAULT)$(C_REST)

$(LIBPATH):	init
			$(MAKE) bonus -C $(LIBDIR)

.PHONY:		init
init:		## git clone --recursive https://this_repository
			git submodule update --init

.PHONY:		clean
clean:
			$(RM) $(OBJS)
			$(RM) $(DEPENDS)
			$(MAKE) clean -C $(LIBDIR)

.PHONY:		fclean
fclean:		clean
			rm -rf $(OBJDIR)
			$(RM) $(NAME)
			$(MAKE) fclean -C $(LIBDIR)

.PHONY:		re
re:			fclean $(NAME)

.PHONY:		bonus
bonus:		$(NAME)

.PHONY:		leaks
leaks:
			$(MAKE) CFLAGS="$(CFLAGS) -D LEAKS=1" LEAKS=TRUE

.PHONY:		mem
mem:
			$(MAKE) MEM=TRUE

-include	$(DEPENDS)
