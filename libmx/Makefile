NAME = libmx.a

SRC_D = src
INC_D = inc
OBJ_D = obj

SRC_F = $(wildcard $(SRC_D)/*.c)

INC = libmx.h
INC_S = $(addprefix $(INC_D)/, $(INC))

CLANG = clang -std=c11 -Wall -Wextra -Werror -Wpedantic

OBJ_S = $(patsubst $(SRC_D)/%.c, $(OBJ_D)/%.o, $(SRC_F))

RM = rm -rf

all: install

install: $(NAME)

$(NAME): $(OBJ_S)
	@ar rcs $@ $^
	@printf "\r\33[2K$@\t   \033[32;1mcreated\033[0m\n"

$(OBJ_D)/%.o: $(SRC_D)/%.c $(INC_S)
	@$(CLANG) -c $< -o $@ -I $(INC_D)

$(OBJ_S): | $(OBJ_D)

$(OBJ_D):
	@mkdir -p $@

clean:
	@$(RM) $(OBJ_D)
	@printf "$(OBJ_D)\t\033[31;1mdeleted\n"

uninstall: clean
	@$(RM) $(NAME)
	@printf "$(NAME)\t\033[31;1muninstalled\n"

reinstall: uninstall install
