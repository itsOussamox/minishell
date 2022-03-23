# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/08 13:16:18 by olabrahm          #+#    #+#              #
#    Updated: 2022/03/14 18:55:00 by olabrahm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
FLAGS=-Wall -Wextra -Werror
MANDATORY =	ft_isalpha ft_isdigit ft_isalnum ft_isascii \
			ft_isprint ft_strlen ft_memset ft_bzero ft_memcpy \
			ft_memmove ft_strlcpy ft_strlcat ft_toupper ft_tolower \
			ft_strchr ft_strrchr ft_strncmp ft_memchr ft_memcmp \
			ft_strnstr ft_atoi ft_calloc ft_strdup ft_substr ft_strjoin \
			ft_split ft_itoa ft_strmapi ft_striteri \
			ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd ft_strcmp ft_charjoin ft_lowerstr \
			ft_strjoin_osm ft_strtrim
BONUS=		ft_lstnew ft_lstadd_front ft_lstsize ft_lstlast ft_lstadd_back \
			ft_lstdelone ft_lstclear ft_lstiter ft_lstmap
OBJS=$(MANDATORY:=.o)
BNS_OBJS =$(BONUS:=.o)
NAME=libft.a
AR= ar rc

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)

bonus: all $(BNS_OBJS)
	@$(AR) $(NAME) $(BNS_OBJS)

%.o: %.c
	@$(CC) $(FLAGS) -c $? -o $@

clean:
	@rm -f $(OBJS) $(BNS_OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all