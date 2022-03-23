# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/11 09:24:43 by olabrahm          #+#    #+#              #
#    Updated: 2022/03/14 20:29:14 by olabrahm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
FLAGS= -Wall -Wextra -Werror
FILES= 	src/main utils/exits/ft_free_exit src/ft_prompt src/ft_execute utils/implement/ft_cd \
		utils/implement/ft_echo utils/env/ft_env utils/env/ft_env_export utils/env/ft_env_unset \
		utils/implement/ft_pwd utils/env/ft_setup_env utils/env/ft_lstutils utils/env/ft_split_env utils/parsing/ft_clean_args \
		utils/exits/ft_free_split_args utils/parsing/ft_split_args utils/env/ft_env_addfront \
		utils/exits/ft_exit utils/exits/ft_perror utils/env/ft_get_vars utils/execution/ft_execute_path \
		utils/execution/ft_save_io utils/execution/ft_execution utils/execution/ft_pipe \
		utils/parsing/ft_token utils/parsing/ft_parse_tree utils/args/ft_args \
		utils/parsing/ft_check_tokens utils/parsing/ft_check_syntax utils/parsing/ft_heredoc \
		utils/env/ft_add_backslash utils/env/ft_default_env utils/env/ft_update_env utils/execution/ft_free_setup \
		utils/parsing/ft_put_exitcode utils/parsing/ft_wildcard utils/parsing/ft_empty_line utils/args/ft_args2 \
		utils/parsing/ft_token2 utils/parsing/ft_check_token utils/parsing/ft_parse_tree2 utils/parsing/ft_check_tokens2 \
		utils/parsing/ft_add_splitted utils/implement/ft_put_cderror

OBJS= $(FILES:=.o)
NAME= minishell
INCLUDES=includes
READLINE=-lreadline
RM= rm -rf
LIBFT_PATH= libft/libft.a

.PHONY: all re clean fclean

all: $(NAME)

$(NAME): $(LIBFT_PATH) $(OBJS) 
	@$(CC) $(FLAGS) $(OBJS) $(LIBFT_PATH) -I $(INCLUDES) $(READLINE) $(LDFLAGS) -o $(NAME)
	@echo "\033[30;1m---> \033[0mMinishell V2.0 \033[32;1m [OK] \033[0m"

$(LIBFT_PATH): 
	@$(MAKE) -C libft

%.o: %.c includes/minishell.h
	@echo "Compiling " $(@F)
	@$(CC) $(FLAGS) -I $(INCLUDES) -c $< -o $@ $(CPPFLAGS)

clean:
	@$(RM) $(OBJS)
	@$(MAKE) clean -C libft 
	@echo "\033[30;1m---> \033[0mObject files clean\033[32;1m [DONE] \033[0m"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C libft 
	@echo "\033[30;1m---> \033[0mBinary files clean\033[32;1m [DONE] \033[0m"

re: fclean all