# Variables
NAME					:= cub3d

SOURCES_DIR				:= sources/
OBJECTS_DIR				:= objects/
HEADERS_DIR				:= includes/
LIBRARIES_DIR			:= libraries/
LIBFT_DIR				:= $(addprefix $(LIBRARIES_DIR), lib/)
LIBFT_FILE 				:= libft.a

MAKE					:= make
MAKE_LIBS				:= $(MAKE) -sC
CC						:= cc
CFLAGS					:= -Wall -Wextra -Werror -Wunreachable-code -Ofast
MKDIR					:= mkdir -p
RM						:= rm -rf

# Sources
FILES := main init_cub3d error_handler

SOURCES					:= $(addprefix $(SOURCES_DIR), $(addsuffix .c, $(FILES)))
OBJECTS					:= $(addprefix $(OBJECTS_DIR), $(addsuffix .o, $(FILES)))
LIBFT					:= $(addprefix $(LIBFT_DIR), $(LIBFT_FILE))
LIBFT_HEADER			:= $(addprefix $(LIBFT_DIR), includes/libft.h)
HEADERS					:= -I $(HEADERS_DIR)

MESSAGE1 := "------------------Compiling cub3d Objects!-------------------"
MESSAGE2 := "---------------Objects Compiled Successfully!----------------"
MESSAGE3 := "-----------------.cub3d Compiled Successfully----------------"

# Rules
.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	@ echo ' '
	@ echo $(MESSAGE1)
	@ echo ' '
	@$(CC) $(CFLAGS) $^ $(LIBFT) -o $(NAME) $(INCLUDES) $(LFLAGS)
	@ echo $(MESSAGE2)
	@ echo ' '
	@ echo $(MESSAGE3)
	@ echo ' '

cleanlibft:
	@$(MAKE_LIBS) $(LIBFT_DIR) clean

fcleanlibft:
	@$(MAKE_LIBS) $(LIBFT_DIR) fclean

clean: cleanlibft
	@ rm -rf $(OBJECTS_DIR)

fclean: clean fcleanlibft
	@$(RM) $(NAME)

re: fclean
	@$(MAKE) -s

bonus: all

$(OBJECTS_DIR)%.o: $(SOURCES_DIR)%.c
	@$(MKDIR) $(OBJECTS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

libraries: $(LIBFT)

$(LIBFT):
	@$(MAKE_LIBS) $(LIBFT_DIR)