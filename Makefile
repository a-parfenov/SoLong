NAME		=	so_long
NAME_BONUS	=	so_long_bonus

SRCS_NAME	=	./srcs/parser.c \
		 		./srcs/main.c \
				./srcs/map.c \
 				./srcs/utils.c\
 				./srcs/utils2.c


B_SRCS_NAME	=	./srcs_bonus/parser.c \
		 		./srcs_bonus/main.c \
				./srcs_bonus/map.c \
 				./srcs_bonus/utils.c\
 				./srcs_bonus/utils2.c\
				./srcs_bonus/itoa.c\
				./srcs_bonus/draw.c

GNL_SRCS	=	./gnl/get_next_line.c\
				./gnl/get_next_line_utils.c

RED			=	"\033[1;31m"
BLUE		=	"\033[1;34m"
YELLOW		=	"\033[1;33m"
WHITE		=	"\033[1;37m"
GREEN		=	"\033[1;32m"
PURPLE		=	"\033[1;35m"
GRAY		=	"\033[1;30m"
END			=	"\033[0m"

OBJS_NAME		=	$(SRCS_NAME:.c=.o)
B_OBJS_NAME		=	$(B_SRCS_NAME:.c=.o)
GNL_OBJS		= 	$(GNL_SRCS:.c=.o)

DFILES		=	$(wildcard $(SRCS_NAME:%.c=%.d))
INCLUDE		=	-I./mlx/

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g
RM			=	rm -f

MLX = mlx/libmlx.a

.PHONY:		all clean fclean re libs bonus

all:		libs $(NAME)


$(NAME):	$(GNL_OBJS) $(OBJS_NAME)
			$(CC) $(INCLUDE) $(MLX) $(GNL_OBJS) $(OBJS_NAME) -o $(NAME)  -framework OpenGL -framework AppKit 

$(OBJS_NAME): $(SRCS_NAME) 
			$(CC) $(CFLAGS) $(INCLUDE) -MMD -c $(SRCS_NAME)
			@mv *.o ./srcs
			@mv *.d ./srcs



bonus:		libs $(NAME_BONUS)
$(NAME_BONUS): $(GNL_OBJS) $(B_OBJS_NAME)
			$(CC) $(INCLUDE) $(MLX) $(GNL_OBJS) $(B_OBJS_NAME) -o $(NAME_BONUS)  -framework OpenGL -framework AppKit 

$(B_OBJS_NAME): $(B_SRCS_NAME) 
			$(CC) $(CFLAGS) $(INCLUDE) -MMD -c $(B_SRCS_NAME)
			@mv *.o ./srcs_bonus
			@mv *.d ./srcs_bonus

$(GNL_OBJS): $(GNL_SRCS) 
			$(CC) $(CFLAGS) $(INCLUDE) -MMD -c $(GNL_SRCS)
			@mv *.o ./gnl
			@mv *.d ./gnl

include $(DFILES)

libs:
		make -C mlx

clean:
		@make -C $(dir $(MLX)) clean
		@$(RM) ./srcs/*.o ./srcs/*.d ./srcs_bonus/*.o ./srcs_bonus/*.d ./gnl/*.o ./gnl/*.d
		@echo ${YELLOW}"\n< Cleaning succeed >\n"${END}

fclean:	clean
		make -C $(dir $(MLX)) fclean
		@$(RM) -f $(NAME)
		@$(RM) -f $(NAME_BONUS)
		@echo ${YELLOW}"< All created files were deleted >\n"${END}

re:		fclean all
		@echo ${YELLOW}"< Remake done >\n"${END}
