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
CFLAGS					:= -Wall -Wextra -Werror -Wunreachable-code -Ofast -g3
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

MESSAGE1 := "------------------Compiling cub3d Objects!-------------------"
MESSAGE2 := "---------------Objects Compiled Successfully!----------------"
MESSAGE3 := "-----------------'.cub3d' File Compiled Successfully!----------------"

# Rules
.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	@echo ' '
	@echo $(MESSAGE1)
	@echo ' '
	@$(CC) $(CFLAGS) $^ $(LIBFT) -o $(NAME) $(INCLUDES) $(LFLAGS)
	@echo $(MESSAGE2)
	@echo ' '
	@echo $(MESSAGE3)
	@echo ' '

cleanlibft:
	@$(MAKE_LIBS) $(LIBFT_DIR) clean

fcleanlibft:
	@$(MAKE_LIBS) $(LIBFT_DIR) fclean

clean: cleanlibft
	@$(RM) $(OBJECTS_DIR)

fclean: clean fcleanlibft
	@$(RM) $(NAME)

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