# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ktaplin <ktaplin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/24 14:52:33 by ktaplin           #+#    #+#              #
#    Updated: 2023/06/14 14:23:29 by ktaplin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
F	= 	error \
		ft_atoi \
		init \
		life \

SRC = $(foreach f, $(F), $(f).c)

GFLAG = -Wall -Wextra -Werror
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@gcc $(OBJ) main.c -o $(NAME) $(GFLAG)

.c.o:
	@gcc $(GFLAG) -o $@ -c $<

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all