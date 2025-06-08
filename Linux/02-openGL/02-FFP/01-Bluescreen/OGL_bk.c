// Standard header files
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>     // for memset

// xlib header files
#include <X11/Xlib.h>
#include <X11/Xutil.h>  // For visualinfo related 
#include <X11/XKBlib.h>

// OpenGL related headerfiles
#include <GL/gl.h>
#include <GL/glx.h>

// MACROS
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// global variables
Display* gpDisplay = NULL;
XVisualInfo *visualInfo = NULL; // hardware visual capacities info baddal sangnar struct 
Window window;          // Window handler/ID
Colormap colormap;      // hardware DS ahe and colors , Graphic card chya memory la color cells astat ani tyachya anek cells la colormap 
Bool bFullScreen = False;

 
Bool bActiveWindow = False;

// OpenGl related globalvariable
GLXContext glxContext = NULL;


int main(void)
{
    // Function declarations
    void toggleFullScreen(void);
    int initialize(void);
    void resize(int, int);
    void display(void);
    void update(void);
    void uninitialize(void);

    // Variable declarations
    int defaultScreen;
    int defaultDepth;
    XSetWindowAttributes windowAttributes;
    Atom windowManagerDeleteAtom;
    XEvent event;
    Screen* screen = NULL;
    int screenWidth, screenHeight;
    KeySym keySym;
    char keys[26];  // This is convension because of no of alphabates, We need only 0th index
    /* pfd equivallent */
    int framebufferAttributes[] = 
                                    {
                                        GLX_DOUBLEBUFFER,
                                        GLX_RGBA,
                                        GLX_RED_SIZE, 8,
                                        GLX_GREEN_SIZE, 8,
                                        GLX_BLUE_SIZE, 8,
                                        GLX_ALPHA_SIZE, 8,
                                        None
                                    };
    Bool bDone = False;


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
    visualInfo = glXChooseVisual(gpDisplay, defaultScreen, framebufferAttributes);
    if (visualInfo == NULL) {
        printf("XMatchVisualInfo() failed\n");
        uninitialize();
        exit(EXIT_FAILURE);
    }

    // Set window attributes (window chya properties set kara)
    memset((void*)&windowAttributes, 0, sizeof(XSetWindowAttributes));
    windowAttributes.border_pixel = 0;  // not know , use default
    windowAttributes.background_pixmap = 0;    // Background la image dyaychiye ka , ppm (portable pixmap), we want color not image
    windowAttributes.background_pixel = XBlackPixel(gpDisplay, visualInfo->screen); // We have 2 different screen by data structs , both are same but  we use visual info wali
    windowAttributes.colormap = XCreateColormap(gpDisplay, 
                                                XRootWindow(gpDisplay, visualInfo->screen),
                                                visualInfo->visual,
                                                AllocNone
                                                );
    colormap = windowAttributes.colormap;
    windowAttributes.event_mask = KeyPressMask | ButtonPressMask | FocusChangeMask | StructureNotifyMask | ExposureMask;

    // Create the window
    window = XCreateWindow(
                    gpDisplay,
                    XRootWindow(gpDisplay, visualInfo->screen),
                    0,
                    0,
                    WIN_WIDTH,
                    WIN_HEIGHT,
                    0,
                    visualInfo->depth,
                    InputOutput,
                    visualInfo->visual,
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
    screen = XScreenOfDisplay(gpDisplay, visualInfo->screen);
    screenWidth = XWidthOfScreen(screen);
    screenHeight = XHeightOfScreen(screen);
    XMoveWindow(gpDisplay, window, screenWidth / 2 - WIN_WIDTH / 2, screenHeight/2 - WIN_HEIGHT / 2);
    
    // Initialize
    int iResult = initialize();
    if (iResult == -1) {
        uninitialize();
        exit(EXIT_FAILURE);
    }

    // Game loop
    while (bDone == False)
    {
        while (XPending(gpDisplay))
        {
            XNextEvent(gpDisplay, &event);
            switch (event.type)
            {
            case MapNotify:
                break;
            case FocusIn:
                bActiveWindow = True;
                break;
            case FocusOut:
                break;
            case ConfigureNotify:
                resize(event.xconfigure.width, event.xconfigure.height);
                break;
            case KeyPress:
                // For escape key
                keySym = XkbKeycodeToKeysym(gpDisplay, event.xkey.keycode, 0, 0);
                switch (keySym)
                {
                case XK_Escape:
                    bDone = True;
                    break;
                default:
                    break;
                }

                // For alphabtic keypress
                XLookupString(&event.xkey, keys, sizeof(keys), NULL, NULL);
                switch (keys[0])
                {
                case 'f':
                case 'F':
                    if (bFullScreen == False)
                    {
                        toggleFullScreen();
                        bFullScreen = True;
                    }
                    else
                    {
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
                bDone = True;
                break;
            default:
                break;
            }
        }

        // Rendering
        if (bActiveWindow == True) {
            display();

            update();
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
        XRootWindow(gpDisplay, visualInfo->screen),
        False,
        SubstructureNotifyMask,
        &event
        );        
}

int initialize(void)
{
    // Code 
    glxContext = glXCreateContext(gpDisplay, visualInfo, NULL, True);
    if (glxContext == NULL) {
        printf("glxCratecontext() failed\n");
        return -1;
    }

    glXMakeCurrent(gpDisplay, window, glxContext);

    // Clear color
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    return 0;
}

void resize(int width, int height)
{
    // Code

    if (height <= 0) height = 1;

    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

void display(void)
{
    // Code

    glClear(GL_COLOR_BUFFER_BIT);

    glXSwapBuffers(gpDisplay, window);
}

void update(void)
{
    // Code
}

void uninitialize(void)
{
    // Code
    GLXContext currentContext = glXGetCurrentContext();
    if (currentContext && currentContext == glxContext) {
        glXMakeCurrent(gpDisplay, 0, 0);
    }

    if (glxContext) {
        glXDestroyContext(gpDisplay, glxContext);
        glxContext = NULL;
    }

    if (visualInfo) {
        free(visualInfo);
        visualInfo = NULL;
    }
    
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
