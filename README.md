# txiv
Tiny X11 Image Viewer with std_image header!
for all Linux Destributes or other OS (freebsd, etc) with X11.
tested in Linux with XFCE Desktop.
options:
* low dependency (only libX11 and libc)
* very minimal for learn or minimal use
* without zoom in and zoom out because its tiny
* Commented codes
* STDC is C99
* its fast and takes few resources. (txiv < 5MB ram)

## Build
for build you can simply write this command:
'''bash
chmod +x build.sh
./build.sh
'''
or directly:
'''bash
gcc txiv.c -o txiv -lX11 -lm
'''
## Install
for install:
'''bash
./build.sh install
'''
## Usage
for use:
'''bash
txiv <image-file>
'''
## Problems
if you use labwc or other wayland compositors and use Xwayland , it wont work properly.
but its been tested on Xfce and it works fine.

# Thanks
Thanks nothings for stb_image header:
https://github.com/nothings/stb

Thanks for use , read codes my programm (:
sorry for my bad English writing ):
