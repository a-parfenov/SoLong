NAME		=	so_long

SRCS		=	main.c\
				gnl/get_next_line.c\
				gnl/get_next_line_utils.c\
				parser.c\
				map.c\
				utils.c\
				utils2.c

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
INCLUDE		=	-I./mlx/

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g
RM			=	rm -f

MLX = mlx/libmlx.a

.PHONY:		all clean fclean re libs

all:		libs $(NAME)

%.o:		%.c
			$(CC) $(CFLAGS) $(INCLUDE) -MMD -c $< -o $@

$(NAME):	$(OBJS)
			$(CC) $(INCLUDE) $(MLX) -o $(NAME) $(OBJS) -framework OpenGL -framework AppKit 

include $(DFILES)

libs:
		make -C mlx

clean:
		@make -C $(dir $(MLX)) clean
		@$(RM) $(OBJS) $(DFILES)
		@echo ${YELLOW}"\n< Cleaning succeed >\n"${END}

fclean:	clean
		make -C $(dir $(MLX)) fclean
		@$(RM) $(NAME)
		@echo ${YELLOW}"< All created files were deleted >\n"${END}

re:		fclean all
		@echo ${YELLOW}"< Remake done >\n"${END}
