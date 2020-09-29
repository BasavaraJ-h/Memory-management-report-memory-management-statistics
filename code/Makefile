

obj-m +=sys_vma_stats.o
obj-m +=sys_vma_props.o

kdir=/lib/modules/$(shell uname -r)/build
all:
	make -C ${kdir} M=$$PWD
modules_install clean:
	make -C ${kdir} M=$$PWD $@
