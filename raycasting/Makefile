NAME = cub3d

LIBFT = ./libft/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3
MLXFLAGS = -fsanitize=address -g mlx_linux/libmlx_Linux.a mlx_linux -Lmlx_linux -lXext -lX11 -lm

RM = rm -rf

SRC_DIR = src/
OBJ_DIR = obj/

SRC_FILES = main player keyhook draw draw_utils parse_xpm putnbr_base

OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))

HEAD = ./include/

all : $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	@echo "\033[0;33m\nCOMPILING cub3d...\n"
	$(CC) $(OBJ) $(LIBFT) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
	@echo "\033[1;32mcub3d created\n"

$(LIBFT)	:
	@echo "\033[0;33m\nCOMPILING LIBFT\n"
	@make -C ./libft
	@echo "\033[1;32mLIBFT created\n"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean :
	$(RM) $(OBJ_DIR)
	$(RM) ./libft/*.o

fclean : clean
	$(RM) $(NAME) $(LIBFT)
	$(RM) ./libft/libft.a

re : fclean all