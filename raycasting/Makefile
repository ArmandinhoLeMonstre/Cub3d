NAME = cub3d
BONUS_NAME = cub3d_bonus

LIBFT = ./libft/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -g #-fsanitize=address
MLXFLAGS =  -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -g #-fsanitize=address

RM = rm -rf

SRC_DIR = src/
OBJ_DIR = obj/
BONUS_SRC_DIR = src_bonus/
BONUS_OBJ_DIR = obj_bonus/

SRC_FILES = utils parsing parsing_utils map map_utils main exit game parse_xpm putnbr_base draw \
raycasting raycasting2 player movements keys floor_n_celling

BONUS_SRC_FILES = draw map parsing_utils exit map_player2d player \
floor_n_celling map_utils putnbr_base mouse raycasting2 \
game movements raycasting keys parse_xpm utils main parsing

OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
BONUS_OBJ = $(addprefix $(BONUS_OBJ_DIR), $(addsuffix _bonus.o, $(BONUS_SRC_FILES)))
BONUS_SRC = $(addprefix $(BONUS_SRC_DIR), $(addsuffix _bonus.c, $(BONUS_SRC_FILES)))

HEAD = ./include/

all : $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	@echo "\033[0;33m\nCOMPILING cub3d...\n"
	$(CC) $(OBJ) $(LIBFT) $(MLXFLAGS) -o $(NAME)
	@echo "\033[1;32mcub3d created\n"

$(BONUS_NAME) : $(BONUS_OBJ) $(LIBFT)
	@echo "\033[0;33m\nCOMPILING SO_LONG_BONUS...\n"
	@$(CC) $(BONUS_OBJ) $(LIBFT)  $(MLXFLAGS) -o $(BONUS_NAME)
	@echo "\033[1;32m./cub3d_bonus created\n"

$(LIBFT)	:
	@echo "\033[0;33m\nCOMPILING LIBFT\n"
	@make -C ./libft
	@echo "\033[1;32mLIBFT created\n"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(BONUS_OBJ_DIR)%.o : $(BONUS_SRC_DIR)%.c
	@mkdir -p $(BONUS_OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

bonus : $(BONUS_NAME)

clean :
	$(RM) $(OBJ_DIR) $(BONUS_OBJ_DIR)
	$(RM) ./libft/*.o

fclean : clean
	$(RM) $(NAME) $(BONUS_NAME)
	$(RM) ./libft/libft.a

re : fclean all