#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <iostream>

using namespace std;

int main(void) {
	cout << "\n\n";
	cout << "*********************\n";
	cout << "Screengrab\n";
	cout << "*********************\n\n";

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

	XDestroyImage(image);
	XCloseDisplay(display);
}
