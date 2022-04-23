NAME		:= pipex

SRCDIR		:= ./srcs/
OBJDIR		:= ./objs/
VPATH		:= $(SRCDIR):$(SRCDIR)$(UTILDIR)

SRCS		:= main.c
SRCS		:= $(addprefix $(SRCDIR), $(SRCS))
OBJS		:= $(addprefix $(OBJDIR), $(notdir $(SRCS:.c=.o)))
DEPENDS		:= $(addprefix $(OBJDIR), $(notdir $(SRCS:.c=.d)))

INCLUDE 	:= -I./includes/ -I./includes/defs/

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

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(DEBUG) $(OBJS) -o $@
			@echo $(C_GREEN)"=== Make Done ==="$(C_DEFAULT)$(C_REST)

.PHONY:		clean
clean:
			$(RM) $(OBJS)
			$(RM) $(DEPENDS)

.PHONY:		fclean
fclean:		clean
			$(RM) $(NAME)

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
