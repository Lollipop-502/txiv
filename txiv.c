#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdlib.h>

#include "iutil.h"


int main(int argc, char* argv[]) {
    //if no argument show help and exit
	if(argc < 2) {printf("Usage: %s <image-file>\n", argv[0]); return 0;}	
	//init image variables
	int width , height , channels;
    //get image to Ram with 4 channels (RGBA)
	unsigned char *data = stbi_load(argv[1], &width, &height, &channels, 4); 
    // if not successful open image , exit with error code 1
    if(!data) return 1;
	//if your target cpu is big endian (X86, X86_64, .etc) you need this function
	fix_BandR_color(data, width, height);

    //init
	Display *d = XOpenDisplay(NULL);
	int scr = DefaultScreen(d);
	int scr_w = DisplayWidth(d, scr);
	int scr_h = DisplayHeight(d, scr);
    GC gc = DefaultGC(d,scr);

    // WIndow init and show
	Window w = XCreateSimpleWindow(d, DefaultRootWindow(d), 100 , 100, width, height, 0, 0, 0);
	XStoreName(d, w, "LTiny X Image Viewer");
	XSelectInput(d, w, ExposureMask | KeyPressMask);
	XSetWindowBackgroundPixmap(d, w, None); //optional for low or no flick
    XSetGraphicsExposures(d,gc, False); //optional for low or no flick
	XMapWindow(d, w);
    // set maximum window size from size of image
    win_set_max_size(d, w, width, height);
    // init image with image , size and RGBA
	XImage *img = XCreateImage(d, DefaultVisual(d, scr), DefaultDepth(d, scr), 
										ZPixmap, 0, (char*) data, width, height, 32, width * 4);
    // for respond close programm from Desktop or ...
	Atom wd = XInternAtom(d, "WM_DELETE_WINDOW", 0);
	XSetWMProtocols(d,w,&wd,1);
    // start loop of program
    XEvent e;	
	while (1) {
		XNextEvent(d, &e);
		if(e.type == ClientMessage && e.xclient.data.l[0] == wd) break; //get signal of close and close
        //for close in programm with Q key
		if (e.type == KeyPress) {
			char key;
			XLookupString(&e.xkey, &key, 1, NULL, NULL);
			if(key == 'q') break;
		}
		// draw image when need
		if(e.type == Expose) {
			XPutImage(d,w,gc,img,0,0,0,0, width, height);
		}
	}
    //cleanup
    stbi_image_free(data);
	XDestroyImage(img);
	XDestroyWindow(d,w);	
	XCloseDisplay(d);

	return 0;
}