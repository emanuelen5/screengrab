#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <iostream>
#include <cstring>

using namespace std;

int main(void) {
	cout << "\n\n";
	cout << "*********************\n";
	cout << "Screengrab\n";
	cout << "*********************\n\n";


    XEvent event;
    char *msg = "Hello, World!";
	int s;

	Display* display = XOpenDisplay(nullptr);
	if (display == NULL) {
		cerr << "Cannot open display\n";
		exit(1);
	}

	s = DefaultScreen(display);
	Window root = RootWindow(display, s);

	XWindowAttributes attr = {};
	XGetWindowAttributes(display, root, &attr);
	auto width = attr.width;
	auto height = attr.height;

	cout << "Screen dimensions:\n";
	cout << "\tWidth: " << width << endl;
	cout << "\tHeight: " << height << endl;

	XImage* image = XGetImage(display, root, 0, 0, width, height, AllPlanes, ZPixmap);

	cout << "Image properties:\n";
	cout << "\tWidth: " << image->width << endl;
	cout << "\tHeight: " << image->height << endl;
	cout << "\tdepth: " << image->depth << endl;
	cout << "\tformat: " << image->format << endl;
	cout << "\toffset: " << image->xoffset << endl;
	cout << "\tbpp-line: " << image->bytes_per_line << endl;

	// Display the grabbed image
    // create window
    Window window = XCreateSimpleWindow(display, RootWindow(display, s), 10, 10, 200, 200, 1,
                                 BlackPixel(display, s), WhitePixel(display, s));
 
    // select kind of events we are interested in
    XSelectInput(display, window, ExposureMask | KeyPressMask);
 
    // map (show) the window
    XMapWindow(display, window);
 
    // event loop
	cerr << "Press any key to close the window\n";
    for (;;)
    {
        XNextEvent(display, &event);
 
        // draw or redraw the window
        if (event.type == Expose)
        {
            XFillRectangle(display, window, DefaultGC(display, s), 20, 20, 10, 10);
            XDrawString(display, window, DefaultGC(display, s), 50, 50, msg, strlen(msg));
        }
        // exit on key press
        if (event.type == KeyPress)
            break;
    }

	XDestroyImage(image);
	XCloseDisplay(display);
}
