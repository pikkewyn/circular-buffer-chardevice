OBJDIR ?= ../obj
obj-m += chardev.o


all: | $(OBJDIR)
	make -I/home/janek/development/chardevice/trunk/src/circularbuffer -C /lib/modules/$(shell uname -r)/build M=$(PWD)  modules
	find . -name "chardev.ko" -exec mv {} $(OBJDIR)/ \;
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)  clean

$(OBJDIR):
	mkdir -p $@
