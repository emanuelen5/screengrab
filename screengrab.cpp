#include <X11/Xlib.h>
#include <X11/X.h>

#include <cstdio>
#include <CImg.h>
using namespace cimg_library;

int main()
{
   Display *display = XOpenDisplay(NULL);
   Window root = DefaultRootWindow(display);

   XWindowAttributes gwa;

   XGetWindowAttributes(display, root, &gwa);
   int width = gwa.width;
   int height = gwa.height;
 


   unsigned char *array = new unsigned char[width * height * 3];

   CImg<unsigned char> pic(array,width,height,1,3);

   for (int frame = 0; frame < 100; frame++) {
	   printf("Grabbing frame %d\n", frame);
       XImage *image = XGetImage(display,root, 0,0 , width,height,AllPlanes, ZPixmap);

       unsigned long red_mask = image->red_mask;
       unsigned long green_mask = image->green_mask;
       unsigned long blue_mask = image->blue_mask;
       for (int x = 0; x < width; x++)
          for (int y = 0; y < height ; y++)
          {
             unsigned long pixel = XGetPixel(image,x,y);
    
             unsigned char blue = pixel & blue_mask;
             unsigned char green = (pixel & green_mask) >> 8;
             unsigned char red = (pixel & red_mask) >> 16;
    
             pic(x,y,0) = red;
             pic(x,y,1) = green;
             pic(x,y,2) = blue;
          }
       }

   pic.save_png("screenshot.png");

   return 0;
}
