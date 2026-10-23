#ifndef IUTIL_H
#define IUTIL_H
#include <string.h>

/* 
swap B and R color for big endian archictures such X86, X86_64 , Arm , etc.
if your target archicture is Little endian please dont use this function
*/

void fix_BandR_color(unsigned char *data, int width, int height) {
	for(int i = 0; i < width * height * 4; i+=4) {
		unsigned char temp = data[i];
		data[i] = data[i + 2];
		data[i + 2] = temp;
	}
}

void win_set_max_size(Display *dsp, Window win, int max_w,int max_h) {
    XSizeHints *sizehints = XAllocSizeHints();
    sizehints->flags = PMaxSize;
    sizehints->max_width = max_w;
    sizehints->max_height = max_h;

    XSetWMNormalHints(dsp, win, sizehints);
    XFree(sizehints);
}

#endif