OBJDIR ?= ./obj
SRC = $(wildcard *.c)
OBJECTS = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

all: $(OBJECTS) | $(OBJDIR)
$(OBJECTS) : $(SRC)
	$(CC) -c $(CFLAGS) $< -o $@

$(0BJDIR):
	mkdir -p $@
