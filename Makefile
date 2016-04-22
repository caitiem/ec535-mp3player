all:
	/ad/eng/courses/ec/ec535/gumstix/oe/cross/bin/arm-linux-gcc mp3player.c -o mp3player
	/ad/eng/courses/ec/ec535/gumstix/oe/cross/bin/arm-linux-gcc -static -I /ad/eng/courses/ec/ec535/gumstix/oe/cross/arm-angstrom-linux-gnueabi/include -L /ad/eng/courses/ec/ec535/gumstix/oe/cross/arm-angstrom-linux-gnueabi/lib minimad.c -o minimad -lmad
