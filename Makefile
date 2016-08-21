export CC            = gcc
export CFLAGS        = -std=gnu99 -g3 -Wall --pedantic
export CRCBUFFER_SRC = $(PWD)/src/circularbuffer
export OBJDIR        = $(PWD)/obj

all: circularbuffer tests kmodule

tests: | $(OBJDIR)
	$(MAKE) -C ut/circularbuffer/

circularbuffer: | $(OBJDIR)
	$(MAKE) -C $(CRCBUFFER_SRC)

kmodule: | $(OBJDIR)
	cd src/chardev && $(MAKE)

$(OBJDIR):
	mkdir -p $@

clean:
	rm -rf $(OBJDIR)

