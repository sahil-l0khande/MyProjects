// Standard header files
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>     // for memset

// xlib header files
#include <X11/Xlib.h>
#include <X11/Xutil.h>  // For visualinfo related 
#include <X11/XKBlib.h>

// MACROS
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// global variables
Display* gpDisplay = NULL;
XVisualInfo visualInfo; // hardware visual capacities info baddal sangnar struct 
Window window;          // Window handler/ID
Colormap colormap;      // hardware DS ahe and colors , Graphic card chya memory la color cells astat ani tyachya anek cells la colormap 
Bool bFullScreen = False;

// Variables related to file I/O
char gszLogFileName[] = "Log.txt";
FILE* gpFile = NULL;

int main(void)
{
    // Function declarations
    void toggleFullScreen(void);
    void MessageBox(const char* msg);
    void printGLInfo(void);
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
    KeySym keySym;
    char keys[26];  // This is convension because of no of alphabates, We need only 0th index

    
    // code
    // Create log file
	gpFile = fopen(gszLogFileName, "w");
	if (gpFile == NULL) {
		MessageBox("Log file creation failed");
		exit(0);  // -1 nahi kel karan hi system madhun aleli error ahe , apli nahi
	}
	else {
		fprintf(gpFile, "Program started successfully\n");
	}
     printGLInfo();

    // Open connection with x server
    gpDisplay = XOpenDisplay(NULL);     // client is opening connection with xserver, NULL for jo asel number display la to ghe
    if (gpDisplay == NULL) {
        fprintf(gpFile,"XopenDisplay() failed\n");
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
        fprintf(gpFile,"XMatchVisualInfo() failed\n");
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
        fprintf(gpFile,"XCreateWindow() failed\n");
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
            break;
        case FocusIn:
            break;
        case FocusOut:
            break;
        case ConfigureNotify:
            break;
        case KeyPress:
            // For escape key
            keySym = XkbKeycodeToKeysym(gpDisplay, event.xkey.keycode, 0, 0);
            switch (keySym) {
                case XK_Escape:
                    uninitialize();
                    exit(EXIT_SUCCESS);
                    break;
                default:
                    break;
            }

            // For alphabtic keypress
            XLookupString(&event.xkey, keys, sizeof(keys), NULL, NULL);
            switch (keys[0]) {
                case 'f':
                case 'F':
                    if (bFullScreen == False) {
                        toggleFullScreen();
                        bFullScreen = True;
                    } else {
                        toggleFullScreen();
                        bFullScreen = False;
                    }
                    break;
                default:
                    break;
            }
            break;
        case ButtonPress:
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

void toggleFullScreen(void)
{
    // Code
    Atom windowManagerNormalStateAtom = XInternAtom(gpDisplay, "_NET_WM_STATE", False); // _NET is we are using xprotol's atom 
    Atom windowManagerFullScreenStateAtom = XInternAtom(gpDisplay, "_NET_WM_STATE_FULLSCREEN", False);
    XEvent event;

    memset((void*)&event, 0, sizeof(XEvent));

    event.type = ClientMessage;
    event.xclient.window =  window; // kontya window sathi janar ahe ha event
    event.xclient.message_type = windowManagerNormalStateAtom;
    event.xclient.format = 32;
    event.xclient.data.l[0] = bFullScreen ? 0 : 1; // l for long 
    event.xclient.data.l[1] = windowManagerFullScreenStateAtom;
    
    // send above event to XServer
    XSendEvent(
        gpDisplay, 
        XRootWindow(gpDisplay, visualInfo.screen),
        False,
        SubstructureNotifyMask,
        &event
        );        
}

void printGLInfo(void)
{
	// code
    FILE* fp = NULL;
    char buf[256] = {0};
    char output[1024] = {0};

	// Print openGL info
	fprintf(gpFile, "OPENGL INFORMATION\n");
	fprintf(gpFile, "******************\n");

    fp = popen("glxinfo | grep OpenGL", "r");
    if (fp == NULL) {
        fprintf(gpFile, "glxinfo command failed\n");
        pclose(fp);
        return;
    }
    

    while (fgets(buf, sizeof(buf), fp) != NULL) {
        strcat(output, buf);
    }

    fprintf(gpFile, "%s", output);

	// fprintf(gpFile, "openGL vendor : %s \n", glGetString(GL_VENDOR));
	// fprintf(gpFile, "openGL renderer : %s \n", glGetString(GL_RENDERER));
	// fprintf(gpFile, "openGL version : %s \n", glGetString(GL_VERSION));
	fprintf(gpFile, "******************\n");
    pclose(fp);
}

void MessageBox(const char *message) {
    char command[512];
    snprintf(command, sizeof(command), "xmessage -center \"%s\"", message);
    system(command);
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
    
    if (gpFile) {
		fprintf(gpFile, "Program terminated successfully\n");
		fclose(gpFile);
		gpFile = NULL;
	}
}
