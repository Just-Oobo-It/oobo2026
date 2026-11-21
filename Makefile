#CFLAGS := -fPIE -Wall -Werror -Wextra -Wno-unused-variable -Wno-unused-parameter -Wno-calloc-transposed-args -Wno-error=unused-but-set-variable -O2
CC = cc
CFLAGS = -std=c23 -Wall -Wextra -Werror -O2# -pedantic
CFLAGS += -Iinclude -Ilib
CFLAGS += -Wc23-extensions
CFLAGS += -Wno-unused-parameter -Wno-unused-variable

LIBS != pkg-config --libs sdl2
LIBS += -lm
INC != pkg-config --static --cflags sdl2

NAME = oob

SRC != find src/ -type f -iname '*.c'

SRCLIB != find lib/ -type f -iname '*.c'

OBJ = ${SRC:src/%.c=.cobj/%.o}
OBJLIB = ${SRCLIB:lib/%.c=.cobj/%.o}

TARGETS = ${SRC:src/%.c=%.o}
TARGETSLIB = ${SRCLIB:lib/%.c=%.o}

all: $(NAME)
		@echo "Done!"

$(NAME): $(OBJ) $(OBJLIB)
		@echo "Compiling $(NAME)..."
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(OBJLIB) $(LIBS)

$(OBJ): $(TARGETS)
$(OBJLIB): $(TARGETSLIB)

$(TARGETS): $(SRC)
$(TARGETSLIB): $(SRCLIB)

clean:
		@echo "Deleting $(NAME) objects..."
		@rm -rf .cobj

fclean: clean
		@echo "Deleting $(NAME) ..."
		@rm -f $(NAME)

re: fclean all

.c.o:
		@mkdir -p .cobj
		@echo  "Compiling $@..."
		$(CC) $(CFLAGS) $(INC) -c $< -o .cobj/$@

.PHONY: all re fclean clean

