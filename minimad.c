/*
* libmad - MPEG audio decoder library
* Copyright (C) 2000-2008 Underbit Technologies, Inc.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
* $Id: minimad.c 88 2008-06-09 11:59:11Z mich $
*/

# include <stdio.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include "mad.h"

int xx;

static int decode(unsigned char const *, unsigned long);

int main(int argc, char *argv[])
{
	struct stat stat;
	void *fdm;

	xx = 0;

	/*if (argc != 1) {
		printf("returning 1\n");
		return 1;
	}*/

	FILE *fp = fopen(argv[1], "r");
    int fd = fileno(fp);
 
	if (fstat(fd, &stat) == -1 ||
	stat.st_size == 0) {
		printf("returning 2\n");
		return 2;
	}
 
	fdm = mmap(0, stat.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (fdm == MAP_FAILED) {
		printf("returning 3\n");
		return 3;
	}
 
	decode(fdm, stat.st_size);
 
	if (munmap(fdm, stat.st_size) == -1) {
		printf("returning 4\n");
		return 4;
	}

	fclose(fp);
 
	printf("returning 0\n");
	return 0;
}
 
struct buffer {
	unsigned char const *start;
	unsigned long length;
};
 
static enum mad_flow input(void *data, struct mad_stream *stream)
{
	//printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\ninput function\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	struct buffer *buffer = data;
 
	if (!buffer->length)
		return MAD_FLOW_STOP;

	mad_stream_buffer(stream, buffer->start, buffer->length);
 
	//buffer->length = 0;
 
	return MAD_FLOW_CONTINUE;
}
 
static inline signed int scale(mad_fixed_t sample)
{
	// round
	sample += (1L << (MAD_F_FRACBITS - 16));
 
	// clip
	if (sample >= MAD_F_ONE)
		sample = MAD_F_ONE - 1;
	else if (sample < -MAD_F_ONE)
		sample = -MAD_F_ONE;
 
	// quantize
	return sample >> (MAD_F_FRACBITS + 1 - 16);
}
 
static enum mad_flow output(void *data, struct mad_header const *header, struct mad_pcm *pcm)
{
	unsigned int nchannels, nsamples;
	mad_fixed_t const *left_ch, *right_ch;
 
	// pcm->samplerate contains the sampling frequency
 
	nchannels = pcm->channels;
	nsamples  = pcm->length;
	left_ch   = pcm->samples[0];
	right_ch  = pcm->samples[1];
 
	while (nsamples--) {
		signed int sample;
 
		// output sample(s) in 16-bit signed little-endian PCM
 
		sample = scale(*left_ch++);
		putchar((sample >> 0) & 0xff);
		putchar((sample >> 8) & 0xff);
 
		if (nchannels == 2) {
			sample = scale(*right_ch++);
			putchar((sample >> 0) & 0xff);
			putchar((sample >> 8) & 0xff);
		}
	}
 
	return MAD_FLOW_CONTINUE;
}
 
static enum mad_flow error(void *data, struct mad_stream *stream, struct mad_frame *frame)
{
	struct buffer *buffer = data;
 
	fprintf(stderr, "decoding error 0x%04x (%s) at byte offset %u\n", stream->error, mad_stream_errorstr(stream), stream->this_frame - buffer->start);
 
	// return MAD_FLOW_BREAK here to stop decoding (and propagate an error)
 
	return MAD_FLOW_CONTINUE;
}
 
static int decode(unsigned char const *start, unsigned long length)
{
	struct buffer buffer;
	struct mad_decoder decoder;
	int result;
 
	// initialize our private message structure
 
	buffer.start  = start;
	buffer.length = length;
 
	// configure input, output, and error functions
 
	// header, filter, message
	mad_decoder_init(&decoder, &buffer, input, 0, 0 , output, error, 0);
 
	// start decoding
 
	result = mad_decoder_run(&decoder, MAD_DECODER_MODE_SYNC);
 
	// release the decoder
 
	mad_decoder_finish(&decoder);
 
	return result;
}
