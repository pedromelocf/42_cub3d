# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/20 14:56:17 by jovicto2          #+#    #+#              #
#    Updated: 2024/11/20 14:56:26 by jovicto2         ###   ########.org.br    #
#                                                                              #
# **************************************************************************** #

# Variables
NAME					:= cub3D

SOURCES_DIR				:= sources/
OBJECTS_DIR				:= objects/
HEADERS_DIR				:= includes/
LIBRARIES_DIR			:= libraries/
LIBFT_DIR				:= $(addprefix $(LIBRARIES_DIR), libft/)
LIBFT_FILE 				:= libft.a

TEST_NAME				:= test_cub3D
TEST_DIR				:= tests/

MAKE					:= make -s
MAKE_LIBS				:= $(MAKE) -C
CC						:= cc
CFLAGS					:= -Wall -Wextra -Wunreachable-code -O3 -g3 -Wno-unused-result
MKDIR					:= mkdir -p
RM						:= rm -rf

# Sources
FILES					:= main

SOURCES					:= $(addprefix $(SOURCES_DIR), $(addsuffix .c, $(FILES)))
OBJECTS					:= $(addprefix $(OBJECTS_DIR), $(addsuffix .o, $(FILES)))
LIBFT					:= $(addprefix $(LIBFT_DIR), $(LIBFT_FILE))
LIBFT_HEADER			:= $(addprefix $(LIBFT_DIR), includes/libft.h)
HEADERS					:= -I $(HEADERS_DIR)

# Tests
TEST_FILES 				:= test_execution

TEST_SOURCES			:= $(addprefix $(TEST_DIR), $(addsuffix .c, $(TEST_FILES)))
TEST_FLAGS				:= -lcriterion

# Colors
RED						:= \033[0;31m
GREEN					:= \033[0;32m
RESET					:= \033[0m

# Messages
MESSAGE2				:= "$(GREEN)Compiled $(NAME) successfully!$(RESET)"
MESSAGE3				:= "$(GREEN)\nRun './$(NAME) <valid_map.cub>' to execute.$(RESET)\n"
MESSAGE4				:= "$(GREEN)Cleaned objects from $(NAME) successfully!$(RESET)"
MESSAGE5				:= "$(GREEN)Removed $(NAME) successfully!$(RESET)"

# Rules
.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	@echo $(MESSAGE1)
	@$(CC) $(CFLAGS) $^ $(LIBFT) -o $(NAME) $(INCLUDES) $(LFLAGS)
	@echo $(MESSAGE2)
	@echo $(MESSAGE3)

cleanlibft:
	@$(MAKE_LIBS) $(LIBFT_DIR) clean

fcleanlibft:
	@$(MAKE_LIBS) $(LIBFT_DIR) fclean

clean: cleanlibft
	@$(RM) $(OBJECTS_DIR)
	@echo $(MESSAGE4)

fclean: clean fcleanlibft
	@$(RM) $(NAME)
	@echo $(MESSAGE5)

re: fclean
	@$(MAKE)

bonus: all

$(OBJECTS_DIR)%.o: $(SOURCES_DIR)%.c
	@$(MKDIR) $(OBJECTS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

libraries: $(LIBFT)

$(LIBFT):
	@$(MAKE_LIBS) $(LIBFT_DIR)

test: $(NAME) $(TEST_SOURCES)
	@$(CC) $(CFLAGS) $(TEST_FLAGS) $(TEST_SOURCES) $(LIBFT) -o $(TEST_NAME) $(HEADERS)
	@./$(TEST_NAME)
	@$(RM) $(TEST_NAME)
