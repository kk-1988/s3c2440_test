KERN_DIR=./../opt/EmbedSky/linux-2.6.30.4
all:
	make -C $(KERN_DIR) M=`pwd` modules
clean:
	make -C $(KERN_DIR) M=`pwd` module clean
	rm -rf modules.order

obj-m	+= first_drv.o
