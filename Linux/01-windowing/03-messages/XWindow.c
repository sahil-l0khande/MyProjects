// Standard header files
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>     // for memset

// xlib header files
#include <X11/Xlib.h>
#include <X11/Xutil.h>

// MACROS
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// global variables
Display* gpDisplay = NULL;
XVisualInfo visualInfo; // hardware visual capacities info baddal sangnar struct 
Window window;          // Window handler/ID
Colormap colormap;      // hardware DS ahe and colors , Graphic card chya memory la color cells astat ani tyachya anek cells la colormap 

int main(void)
{
    // Function declarations
    void uninitialize(void);

    // Variable declarations
    int defaultScreen;
    int defaultDepth;
    Status status;
    XSetWindowAttributes windowAttributes;
    Atom windowManagerDeleteAtom;
    XEvent event;
    Screen* screen = NULL;
    int screenWidth, screenHeight;

    // code
    // Open connection with x server
    gpDisplay = XOpenDisplay(NULL);     // client is opening connection with xserver, NULL for jo asel number display la to ghe
    if (gpDisplay == NULL) {
        printf("XopenDisplay() failed\n");
        uninitialize();
        exit(EXIT_FAILURE);
    }

    // Create the default screen
    defaultScreen = XDefaultScreen(gpDisplay); // Opened display la vicharta , TU jo client server mdhla interface ahe default screen cha number return kr

    // Get default depth 
    defaultDepth = XDefaultDepth(gpDisplay, defaultScreen);

    // Get visual info
    memset(&visualInfo, 0, sizeof(XVisualInfo));
    status = XMatchVisualInfo(gpDisplay, defaultScreen, defaultDepth, TrueColor, &visualInfo); // mi detoy to pixel format shi match kr true color nava chya  vicual class la match honara, (Identical to pfd bits in windows)
    if (status == 0) {
        printf("XMatchVisualInfo() failed\n");
        uninitialize();
        exit(EXIT_FAILURE);
    }

    // Set window attributes (window chya properties set kara)
    memset((void*)&windowAttributes, 0, sizeof(XSetWindowAttributes));
    windowAttributes.border_pixel = 0;  // not know , use default
    windowAttributes.background_pixmap = 0;    // Background la image dyaychiye ka , ppm (portable pixmap), we want color not image
    windowAttributes.background_pixel = XBlackPixel(gpDisplay, visualInfo.screen); // We have 2 different screen by data structs , both are same but  we use visual info wali
    windowAttributes.colormap = XCreateColormap(gpDisplay, 
                                                XRootWindow(gpDisplay, visualInfo.screen),
                                                visualInfo.visual,
                                                AllocNone
                                                );
    colormap = windowAttributes.colormap;
    windowAttributes.event_mask = KeyPressMask | ButtonPressMask | FocusChangeMask | StructureNotifyMask | ExposureMask;

    // Create the window
    window = XCreateWindow(
                    gpDisplay,
                    XRootWindow(gpDisplay, visualInfo.screen),
                    0,
                    0,
                    WIN_WIDTH,
                    WIN_HEIGHT,
                    0,
                    visualInfo.depth,
                    InputOutput,
                    visualInfo.visual,
                    CWBorderPixel | CWBackPixel | CWEventMask | CWColormap,
                    &windowAttributes
    );

    if (!window) {
        printf("XCreateWindow() failed\n");
        uninitialize();
        exit(EXIT_FAILURE);

    }

    // Create atom for window manager to destroy the window
    windowManagerDeleteAtom = XInternAtom(gpDisplay, "WM_DELETE_WINDOW", True);     // Window manage la command dene
    XSetWMProtocols(gpDisplay, window, &windowManagerDeleteAtom, 1);

    // Set window title
    XStoreName(gpDisplay, window, "SRL Xwindow");

    // Map the window to show it
    XMapWindow(gpDisplay, window);

    // Centering of window
    screen = XScreenOfDisplay(gpDisplay, visualInfo.screen);
    screenWidth = XWidthOfScreen(screen);
    screenHeight = XHeightOfScreen(screen);
    XMoveWindow(gpDisplay, window, screenWidth / 2 - WIN_WIDTH / 2, screenHeight/2 - WIN_HEIGHT / 2);
    
    // Message loop
    while (1) {
        XNextEvent(gpDisplay, &event);
        switch (event.type)
        {
        case MapNotify:
            printf("Map notify even is recceived \n");
            break;
        case FocusIn:
            printf("Window got focus\n");
            break;
        case FocusOut:
            printf("Window lost focus\n");
            break;
        case ConfigureNotify:
            printf("Window is resized\n");
            break;
        case KeyPress:
            printf("Keypress event recevied\n");
            break;
        case ButtonPress:
            switch (event.xbutton.button) {
                case 1:
                    printf("Left mouse button is clicked\n");
                    break;
                case 2:
                    printf("Middle mouse button clicked\n");
                    break;
                case 3 :
                    printf("Right mouse button is clicked\n");
                    break;
                default:
                    break;
            }
            break;
        case Expose:
            break;
        case 33:
            uninitialize();
            exit(EXIT_SUCCESS);
            break;
        default:
            break;
        }
    }

    uninitialize();
    return 0;
}

void uninitialize(void)
{
    // Code
    if (window) {
        XDestroyWindow(gpDisplay, window);
    }

    if (colormap) {
        XFreeColormap(gpDisplay, colormap);
    }

    if (gpDisplay) {
        XCloseDisplay(gpDisplay);
        gpDisplay = NULL;
    }
}
