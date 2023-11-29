NAME = uls
CLANG = -std=c11 -Wall -Wextra -Werror -Wpedantic

SRC_D = src
INC_D = inc
OBJ_D = obj
TEST_D = test

INC_F = $(wildcard $(INC_D)/*.h)
SRC_F = $(wildcard $(SRC_D)/*.c)
OBJ_F = $(addprefix $(OBJ_D)/, $(notdir $(SRC_F:%.c=%.o)))

LMX_D = libmx
LMX_A := $(LMX_D)/libmx.a
LMX_INC := $(LMX_D)/inc

.PHONY: all clean uninstall reinstall test archive

all: install

install: $(LMX_A) $(NAME)

$(NAME): $(OBJ_F)
	@clang $(CLANG) $(OBJ_F) -L$(LMX_D) -lmx -o $@
	@printf "\r\33[2K$@ \033[32;1mcreated\033[0m\n"

$(OBJ_D)/%.o: $(SRC_D)/%.c $(INC_F)
	@clang $(CLANG) -c $< -o $@ -I$(INC_D) -I$(LMX_INC)
	@printf "\r\33[2K$(NAME) \033[33;1mcompile \033[0m$(<:$(SRC_D)/%.c=%) "

$(OBJ_F): | $(OBJ_D)

$(OBJ_D):
	@mkdir -p $@

$(LMX_A):
	@make -sC $(LMX_D)

clean:
	@rm -rf $(OBJ_D)
	@printf "$(OBJ_D) in $(NAME) \033[31;1mdeleted\033[0m\n"

uninstall:
	@make -sC $(LMX_D) $@
	@rm -rf $(OBJ_D)
	@rm -rf $(NAME)
	@printf "$(NAME) \033[31;1muninstalled\033[0m\n"

reinstall: uninstall all
