# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/20 13:00:01 by rmeriau           #+#    #+#              #
#    Updated: 2023/07/24 10:20:22 by rmeriau          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
NAME = pipex
BNAME = pipex_bonus

SOURCES = ./src/main.c ./src/ft_pipex_utils.c ./src/ft_free.c \
		./src/ft_fill_elems.c ./src/ft_process.c ./src/ft_here_doc.c \
		./src/new_ft_split.c

BSOURCES = ./src_bonus/main_bonus.c ./src_bonus/ft_pipex_utils_bonus.c ./src_bonus/ft_free_bonus.c \
		./src_bonus/ft_fill_elems_bonus.c ./src_bonus/ft_process_bonus.c ./src_bonus/ft_here_doc_bonus.c \
		./src_bonus/new_ft_split_bonus.c

OBJECTS = $(SOURCES:.c=.o)

BOBJECTS = $(BSOURCES:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
$(NAME): $(OBJECTS)
	make -C ./libft
	$(CC) $(CFLAGS) $(OBJECTS) -I ./pipex.h ./libft/libft.a -o $@

bonus: $(BNAME)

$(BNAME): $(BOBJECTS)
	make -C ./libft
	$(CC) $(CFLAGS) $(BOBJECTS) -I ./pipex_bonus.h ./libft/libft.a -o $@

clean:
	$(RM) $(OBJECTS)
	$(RM) $(BOBJECTS)
	make clean -C ./libft

fclean: clean
	$(RM) $(NAME)
	$(RM) $(BNAME)
	$(RM) ./libft/libft.a

re: fclean all