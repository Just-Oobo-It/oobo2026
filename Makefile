
	############
	##        ##
	##  meow  ##
	##        ##
	############

NAME := assistant


CC := gcc

# CFLAGS := -fPIE -Wall -Werror -O2
CFLAGS := -fPIE -Wall -Werror -Wextra -Wno-unused-variable -Wno-unused-parameter -Wno-calloc-transposed-args -O2
CFLAGS += -Iinclude -Ilib

CFLAGS += $(shell pkg-config sdl2 --cflags)

LIBS := -lSDL2 -lm

SRCDIR := src/
LIBDIR := lib/
OBJDIR := build/obj/
LIBOBJDIR := $(OBJDIR)$(LIBDIR)

SFILES := c
OFILES := o

SOURCES := $(shell find $(SRCDIR) -name "*.$(SFILES)")
LIBSOURCES := $(shell find $(LIBDIR) -name "*.$(SFILES)")
OBJECTS := $(patsubst $(SRCDIR)%.$(SFILES), $(OBJDIR)%.$(OFILES), $(SOURCES))
LIBOBJECTS := $(patsubst $(LIBDIR)%.$(SFILES), $(LIBOBJDIR)%.$(OFILES), $(LIBSOURCES))

all: directories $(NAME)

directories:
	mkdir -p $(OBJDIR)
	mkdir -p $(OBJDIR)$(LIBDIR)

$(NAME): $(OBJECTS) $(LIBOBJECTS)
	$(CC) $^ $(LIBS) -o $@
$(OBJDIR)%$(OFILES): $(SRCDIR)%$(SFILES)
	$(CC) $(CFLAGS) -c $< -o $@
$(LIBOBJDIR)%$(OFILES): $(LIBDIR)%$(SFILES)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

