# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                           d          +:+ +:+         +:+      #
#    By: tlevel <tlevel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/30 18:10:51 by tlevel            #+#    #+#              #
#    Updated: 2021/10/05 18:07:19 by tlevel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME         = 							fractol

HEADER_LST	 =							fractol.h
HEADER_DIR   =							./includes
HEADER       =							$(addprefix $(HEADER_DIR)/, $(HEADER_LST))

SOURCE_DIR   =							./source
SOURCE_LST   = 							fractol.c\
										utils.c\
										library_fun.c\
										mandelbrot.c\
										julia.c\
										bonus.c\
										hooks.c
SOURCE		=							$(addprefix $(SOURCE_DIR)/, $(SOURCE_LST))


OBJ_DIR	     =							./objects
OBJ_LST      =							$(patsubst %.c, %.o, $(SOURCE_LST))
OBJECTS	   	 =							$(addprefix $(OBJ_DIR)/, $(OBJ_LST))

MLX_DIR      =							./minilibx/
MLX_HEADERS	 =							$(MLX_DIR)

FLAGS        =							-Wall -Wextra -Werror -g -Ofast
LIBX_FLAGS   =							-lmlx -framework OpenGL -framework AppKit

all: 									obj $(NAME)
										
obj:									
										@mkdir -p $(OBJ_DIR)
										
$(OBJ_DIR)/%.o : $(SOURCE_DIR)/%.c 		$(HEADER)
										gcc $(FLAGS) -I $(HEADER_DIR) -o $@ -c $< 
										
$(NAME): 								$(OBJECTS)
										gcc $(FLAGS) $(OBJECTS) $(LIBX_FLAGS) -o $@
				
clean:			
										@rm -rf $(OBJ_DIR)
			
fclean: 								clean
										@rm -rf $(NAME)

re: 									fclean all

.PHONY:									all clean fclean re
