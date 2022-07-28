NAME	=	pathfinder

CFLG	=	-std=c11 $(addprefix -W, all extra error pedantic) -g

SRC_DIR	= src
INC_DIR	= inc
OBJ_DIR	= obj

INC_FILES = $(wildcard inc/*.h)
SRC_FILES = $(wildcard src/*.c)
OBJ_FILES = $(addprefix obj/, $(notdir $(SRC_FILES:%.c=%.o)))

LMX_A:=	libmx/libmx.a
LMX_INC:= libmx/inc

all: install

install: libmx/libmx.a $(NAME)

$(NAME): $(OBJ_FILES)
	@clang $(CFLG) $(OBJ_FILES) -L libmx -lmx -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_FILES)
	@clang $(CFLG) -c $< -o $@ -I$(INC_DIR) -I$(LMX_INC)

$(OBJ_FILES): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir -p $@

$(LMX_A):
	@make -sC libmx
	
clean:
	@rm -rf $(OBJ_DIR)
uninstall:
	@make -sC libmx $@
	@rm -rf $(OBJ_DIR)
	@rm -rf $(NAME)

reinstall: uninstall all