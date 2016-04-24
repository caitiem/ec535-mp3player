all:
	/ad/eng/courses/ec/ec535/gumstix/oe/cross/bin/arm-linux-gcc audio_alsa.c audio.c -o audio_alsa -lmad -lid3tag -lasound
