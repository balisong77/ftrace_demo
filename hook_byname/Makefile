obj-m = hook_by_name.o
KERNEL_VER = $(shell uname -r)
# KERNEL_VER = 5.15.0-48-generic
all:
	make -C /lib/modules/$(KERNEL_VER)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(KERNEL_VER)/build M=$(PWD) clean