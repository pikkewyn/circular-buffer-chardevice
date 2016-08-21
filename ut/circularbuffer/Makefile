OBJDIR ?= ./obj
TARGET = $(OBJDIR)/test
SRC = $(wildcard *.c)
LINKAGEOBJECTS = $(wildcard $(0BJDIR)/*.o)
OBJECTS=$(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(addprefix $(OBJDIR)/, $(OBJECTS))
	$(CC) $(CFLAGS) $(addprefix $(OBJDIR)/, *.o) -o $(TARGET)
	
$(OBJDIR)/%.o : %.c | $(OBJDIR)
	$(CC) -c $(CFLAGS) -I../../src/circularbuffer $< -o $@

$(OBJDIR):
	mkdir -p $@
