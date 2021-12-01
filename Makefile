NAME		=	so_long

SRCS		=	main.c\
				gnl/get_next_line.c\
				gnl/get_next_line_utils.c\
				parser/load_map.c\
				parser/parser.c

RED			=	"\033[1;31m"
BLUE		=	"\033[1;34m"
YELLOW		=	"\033[1;33m"
WHITE		=	"\033[1;37m"
GREEN		=	"\033[1;32m"
PURPLE		=	"\033[1;35m"
GRAY		=	"\033[1;30m"
END			=	"\033[0m"

OBJS		=	$(SRCS:%.c=%.o)
DFILES		=	$(wildcard $(SRCS:%.c=%.d))
INCLUDE		=	-I./ -I./mlx/

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -f

LIB = mlx/libmlx.a #libft/libft.a

.PHONY:		all clean fclean re

all:		libs $(NAME)

%.o:		%.c
			$(CC) $(CFLAGS) $(INCLUDE) -MMD -c -g $< -o $@

$(NAME):	$(OBJS)
			$(CC) $(INCLUDE) $(LIB) -o $(NAME) $(OBJS) -framework OpenGL -framework AppKit 
# Для связи с требуемым внутренним API macOS
#@echo ${PURPLE}"< Compiled pipex >\n"${END}
#@echo ${PURPLE}"< Done >\n"${END}

include $(DFILES)

libs:
			make -C mlx
# make -C libft

clean:
			@make -C $(dir $(LIB)) clean
			@$(RM) $(OBJS) $(DFILES)
			@echo ${YELLOW}"\n< Cleaning succeed >\n"${END}

fclean:		clean
			make -C $(dir $(LIB)) fclean
			@$(RM) $(NAME)
			@echo ${YELLOW}"< All created files were deleted >\n"${END}

re:			fclean all
			@echo ${YELLOW}"< Remake done >\n"${END}
