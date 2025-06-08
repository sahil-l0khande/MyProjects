
// Win32 headers

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "OGL.h"	// Custom header file

// OpenGL related header files

#include <gl/GL.h>
#include <gl/GLU.h>

// OpenGL related libraries 

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "GLU32.lib")

// Macros
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#define MAX_LIMIT_CUBE_TRANSLATE_X 8.0f
#define MIN_LIMIT_CUBE_TRANSLATE_X -8.0f

#define MAX_LIMIT_CUBE_TRANSLATE_Y 4.0f
#define MIN_LIMIT_CUBE_TRANSLATE_Y 0.45f

#define CLOSEST_LIMIT_CUBE_TRANSLATE_Z 5.0f
#define FARTHEST_LIMIT_CUBE_TRANSLATE_Z -20.0f

#define INCREMENT 0.1f
#define DECREMENT 0.1f

// Global function declarations

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Global variable declarations

// Variables related to full screen
HWND ghwnd = NULL;
DWORD dwStyle;
WINDOWPLACEMENT wpPrev;
BOOL gbFullScreen = FALSE;

// Variables related to file I/O
char gszLogFileName[] = "Log.txt";
FILE* gpFile = NULL;

// Active window related variable
BOOL gbActiveWindow = FALSE;

// Exit keypress related
BOOL gbEscapeKeyIsPressed = FALSE;

// OpenGL related global variables
HDC ghdc = NULL;	// global handle to device context
HGLRC ghrc = NULL;	// global handle to Graphics library rendering context

// Rotation angles
GLfloat AngleCube = 0.0f;
GLfloat AnglePyramid = 0.0f;
GLfloat AngleRectangle = 0.0f;

// Lights

GLfloat lightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat lightDefuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat lightPosition[] = { 0.0f, 5.0f, 10.0f, 1.0f };

GLfloat materialAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat materialDiffuse[] = { 1.0f, 0.0f, 0.0f, 0.0f };
GLfloat materialSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

GLfloat materialShininess = 128.0f;

// Special effect related variables 

GLuint texture_marble = 0;

GLfloat translateCubeX = 0.0f;
GLfloat translateCubeY = 1.0f;
GLfloat translateCubeZ = 0.0f;

GLfloat cubeScale = 0.25f;

// Entry point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// Local function declarations

	int initialize(void);
	void display(void);
	void update(void);
	void uninitialize(void);

	// variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("RTR6");
	BOOL bDone = FALSE;
	int xPos;
	int yPos;

	// Code

	// Create log file
	gpFile = fopen(gszLogFileName, "w");
	if (gpFile == NULL) {
		MessageBox(NULL, TEXT("Log file creation failed"), TEXT("Error"), MB_OK);
		exit(0);  // -1 nahi kel karan hi system madhun aleli error ahe , apli nahi
	}
	else {
		fprintf(gpFile, "Program started successfully\n");
	}

	// Windowclass initialization

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// CS: Class style , OWNDC : Swatacha device Context , He OS la sangta asa DC tayar kar jo inbetween tu move karnar nahis, In memory thevshil
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);

	//REgistration window class

	RegisterClassEx(&wndclass);

	// create window

	xPos = GetSystemMetrics(SM_CXSCREEN) / 2 - 400;
	yPos = GetSystemMetrics(SM_CYSCREEN) / 2 - 300;
	hwnd = CreateWindowEx(WS_EX_APPWINDOW, szAppName, TEXT("Sahil Rajendra Lokhande"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
		xPos, // kadhaychay
		yPos, // kadhaychay
		WIN_WIDTH,
		WIN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ghwnd = hwnd;
	// Show window
	ShowWindow(hwnd, iCmdShow);

	// Print background of window
	UpdateWindow(hwnd);

	// Initialize
	int result = initialize();
	if (result != 0) {
		fprintf(gpFile, "initialize() failed\n");
		DestroyWindow(hwnd);
		hwnd = NULL;
	}
	else {
		fprintf(gpFile, "initialize() completed successfully\n");
	}

	// Set this Window as active window
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	// Gameloop
	while (bDone == FALSE) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				bDone = TRUE;
			}
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else {
			if (gbActiveWindow == TRUE) {
				if (gbEscapeKeyIsPressed == TRUE) {
					bDone = TRUE;
				}
				// Render
				display();

				// update
				update();
			}
		}
	}

	// uninitialize 
	uninitialize();

	return ((int)msg.wParam);
}

// Callback function

LRESULT CALLBACK WndProc(HWND hwnd, UINT imsg, WPARAM wParam, LPARAM lParam)
{
	// Function declarations
	void toggleFullScreen(void);
	void resize(int, int);
	void uninitialize(void);

	// Code
	switch (imsg)
	{
	case WM_CREATE:
		ZeroMemory((void*)&wpPrev, sizeof(WINDOWPLACEMENT));
		wpPrev.length = sizeof(WINDOWPLACEMENT);
		break;
	case WM_SETFOCUS:
		gbActiveWindow = TRUE;
		break;
	case WM_KILLFOCUS:
		gbActiveWindow = FALSE;
		break;
		// using For better rendering purpose ,not mendatory
	case WM_ERASEBKGND:
		return (0);
	case WM_SIZE:
		resize(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:		// Letter nahiye mhanun virtual key
			gbEscapeKeyIsPressed = TRUE;
			break;
		case VK_RIGHT:
			if (translateCubeX < MAX_LIMIT_CUBE_TRANSLATE_X) {
				translateCubeX = translateCubeX + INCREMENT;
			}
			break;
		case VK_LEFT:
			if (translateCubeX > MIN_LIMIT_CUBE_TRANSLATE_X) {
				translateCubeX = translateCubeX - DECREMENT;
			}
			break;
		case VK_UP:
			if (translateCubeY < MAX_LIMIT_CUBE_TRANSLATE_Y) {
				translateCubeY = translateCubeY + INCREMENT;
			}
			break;
		case VK_DOWN:
			if (translateCubeY > MIN_LIMIT_CUBE_TRANSLATE_Y) {
				translateCubeY = translateCubeY - DECREMENT;
			}
			break;
		case VK_ADD:	// Zoom in
			if (translateCubeZ < CLOSEST_LIMIT_CUBE_TRANSLATE_Z) {
				translateCubeZ = translateCubeZ + INCREMENT;
			}
			break;
		case VK_SUBTRACT:	// Zoom out
			if (translateCubeZ > FARTHEST_LIMIT_CUBE_TRANSLATE_Z) {
				translateCubeZ = translateCubeZ - DECREMENT;
			}
			break;
		default:
			break;
		}
		break;
	case WM_CHAR:
		switch (LOWORD(wParam))
		{
		case 'F':
		case 'f':
			if (gbFullScreen == FALSE) {
				toggleFullScreen();
				gbFullScreen = TRUE;
			}
			else {
				toggleFullScreen();
				gbFullScreen = FALSE;
			}
			break;
		}
		break;
	case WM_CLOSE:
		uninitialize();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	return (DefWindowProc(hwnd, imsg, wParam, lParam));
}

void toggleFullScreen(void) // Stub function 
{
	// Variable declarations
	MONITORINFO mi;

	// Code
	if (gbFullScreen == FALSE) {
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
		if (dwStyle & WS_OVERLAPPEDWINDOW) {
			ZeroMemory((void*)&mi, sizeof(MONITORINFO));
			mi.cbSize = sizeof(MONITORINFO);

			if (GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
			{
				SetWindowLong(ghwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);  // old Style kadhli
				SetWindowPos(ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top,
					SWP_NOZORDER | SWP_FRAMECHANGED); /* expand keli window, yankadun os la messsage jato WM_NCCALCSIZE */
			}
			ShowCursor(FALSE);	// OS cha cursor hide 
		}
	}
	else {
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);  // Jar already full screeen asel tr , normal window
		ShowCursor(TRUE);
	}
}

int initialize(void)
{
	// Function declaration
	void printGLInfo(void);
	BOOL loadGLTexture(GLuint * texture, TCHAR imageResouceID[]);
	void resize(int width, int height);

	// Varibale declarations
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex = 0;

	// Code

	// Pixel format descriptor initialization
	ZeroMemory((void*)&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;
	pfd.cDepthBits = 32;
	// Without this we wont have stencil
	pfd.cStencilBits = 24;

	// get DC
	ghdc = GetDC(ghwnd);
	if (ghdc == NULL) {
		fprintf(gpFile, "GetDC() failed\n");
		return -1;
	}

	// Get matching pixel format index using hdc and pfd 
	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);
	if (iPixelFormatIndex == 0) {
		fprintf(gpFile, "ChoosePixelFormat() failed\n");
		return -2;
	}

	// Select the pixel format of found index
	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE) {
		fprintf(gpFile, "SetPixelFormat() failed\n");
		return -3;
	}

	// Create rendering context using hdc pfd and chosen pixelformatidex
	ghrc = wglCreateContext(ghdc);
	if (ghrc == NULL) {
		fprintf(gpFile, "wglCreateContext() failed\n");
		return -4;
	}

	// Make this rendering context as current contex
	if (wglMakeCurrent(ghdc, ghrc) == FALSE) {
		fprintf(gpFile, "wglMakeCurrent() failed\n");
		return -5;
	}

	// Print openGL information
	printGLInfo();

	// From here onwards openGL code starts	
	
	// Depth related code
	
	glShadeModel(GL_SMOOTH);   // Think about smoothness 
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


	// Tell opengl to chose the color to clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	// Load textures
	if (loadGLTexture(&texture_marble, MAKEINTRESOURCE(IDBITMAP_MARBLE)) == FALSE) {
		fprintf(gpFile, "loadGLTexture failed for marble\n");
		return -6;
	}

	// Enable texturing
	glEnable(GL_TEXTURE_2D);

	// Light configuration
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDefuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glEnable(GL_LIGHT0);

	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);
	glEnable(GL_NORMALIZE);
	glEnable(GL_AUTO_NORMAL);

	// Warmup resize
	resize(WIN_WIDTH, WIN_HEIGHT);
	return (0);
}



void printGLInfo(void)
{
	// code

	// Print openGL info
	fprintf(gpFile, "OPENGL INFORMATION\n");
	fprintf(gpFile, "******************\n");
	fprintf(gpFile, "openGL vendor : %s \n", glGetString(GL_VENDOR));
	fprintf(gpFile, "openGL renderer : %s \n", glGetString(GL_RENDERER));
	fprintf(gpFile, "openGL version : %s \n", glGetString(GL_VERSION));
	fprintf(gpFile, "******************\n");

}

BOOL loadGLTexture(GLuint* texture, TCHAR imageResouceID[])
{
	// Variable declarations
	HBITMAP hBitmap = NULL;
	BITMAP bmp;
	BOOL bResult = FALSE;

	// Code

	// Load the bitmap as image
	hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), imageResouceID, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION); // Device independant bitmap
	if (hBitmap) {
		bResult = TRUE;

		// Get bitmap structure from the loaded bitmap image
		GetObject(hBitmap, sizeof(BITMAP), &bmp);

		// Generate openGL texture object
		glGenTextures(1, texture); // empty textute obj craetes

		// bind to the newly created empty structure object
		glBindTexture(GL_TEXTURE_2D, *texture);

		// unpack the image in memory for faster loading
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // mag means jevha object motha hoil tevha quality
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // Lamb ahe mhnun kami quality

		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bmp.bmWidth, bmp.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, bmp.bmBits);

		// Unbind
		glBindTexture(GL_TEXTURE_2D, 0);

		// Delete object
		DeleteObject(hBitmap);
		hBitmap = NULL;

	}

	return bResult;
}

void resize(int width, int height)
{
	// Height by accedent becomes 0 or less ,then make it 1
	if (height <= 0) {
		height = 1;
	}

	// Set the view port
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	// Set matrix projection mode

	glMatrixMode(GL_PROJECTION); // matrix cha mode projection la thev
	
	// Set To Identity Matrix

	glLoadIdentity();   // jya matrix cha mode tu projection la set kela atta , tya matrix la identity matrix kar

	// Do Perspective projection

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);  // FOV-Y , Aspect ratio, Near, far  (conventional value)

}

void display(void)
{
	// Function declaration
	void drawLitCube(void);
	void drawFloor(void);

	// Code

	// Clear opengl buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Set matrix to model view mode
	glMatrixMode(GL_MODELVIEW);

	// Cube

	glLoadIdentity();

	// Setup camera
	gluLookAt(0.0f, 5.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Render the actual cube

	glPushMatrix();

	// Translate triangle backwards by z
	glTranslatef(translateCubeX, translateCubeY, translateCubeZ);

	glRotatef(AngleRectangle, 1.0f, 0.0f, 0.0f);

	glScalef(cubeScale, cubeScale, cubeScale);
	glRotatef(AngleCube, 1.0f, 0.0f, 0.0f);
	glRotatef(AngleCube, 0.0f, 1.0f, 0.0f);
	glRotatef(AngleCube, 0.0f, 0.0f, 1.0f);

	drawLitCube();
	glPopMatrix();

	// DOnt go outside of floor
	// Define floor as stencil  , SO we dont need depth testing for sometime
	glDisable(GL_DEPTH_TEST);

	// As we r not rendering floor right now , Mask out all rendering color
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	// Enable stencil test
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1);  // Always pass the stencil test 
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);  // what to do in Empty spaces 
	drawFloor();   // This call will not render the floor

	// Render the reflected cube

	glEnable(GL_DEPTH_TEST);	// as we wanna start rendering , enable depthtest again

	// As we want to start rendering again, unmask the colors
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glStencilFunc(GL_EQUAL, 1, 1); // Draw only where 1 present in stencil buffer
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	glPushMatrix();

	glScalef(1.0f, -1.0f, 1.0f);

	// Translate triangle backwards by z
	glTranslatef(translateCubeX, translateCubeY, translateCubeZ);

	glRotatef(AngleRectangle, 1.0f, 0.0f, 0.0f);

	glScalef(cubeScale, cubeScale, cubeScale);
	glRotatef(AngleCube, 1.0f, 0.0f, 0.0f);
	glRotatef(AngleCube, 0.0f, 1.0f, 0.0f);
	glRotatef(AngleCube, 0.0f, 0.0f, 1.0f);

	drawLitCube();
	glPopMatrix();

	//  Done with stenciling
	glDisable(GL_STENCIL_TEST);

	// Render the floor 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0f, 1.0f, 1.0f, 0.7f);
	drawFloor();
	glDisable(GL_BLEND);
	// swap the buffers
	SwapBuffers(ghdc);
}

void drawLitCube(void)
{
	glEnable(GL_LIGHTING);
	glBegin(GL_QUADS);

	// Front face
	//glColor3f(1.0f, 0.0f, 0.0f);  // RED
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Right face
	//glColor3f(0.0f, 1.0f, 0.0f);  // GREEN
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Back face
	//glColor3f(0.0f, 0.0f, 1.0f);  // BLUE
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);

	// Left face
	//glColor3f(0.0f, 1.0f, 1.0f);  // CYAN
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	// Top face
	//glColor3f(1.0f, 1.0f, 0.0f);  // YELLOW
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	// Bottom face
	//glColor3f(1.0f, 0.0f, 1.0f);  // MAGENTA
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	glEnd();
	glDisable(GL_LIGHTING);

}

void drawFloor(void)
{
	// Code

	glPushMatrix();
	/* Translate triangle backwards by z */
	glTranslatef(0.0f, -1.0f, -2.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glScalef(5.0f, 5.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, texture_marble);
	glBegin(GL_QUADS);

	// Right top
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);

	// Left top
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);

	// left bottom
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	// right bottom
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
}

void update(void)
{
	// Code

	// Cube
	AngleCube = AngleCube + 0.5f;

	if (AngleCube >= 360.0f) {
		AngleCube = AngleCube - 360.0f;
	}

}

void uninitialize(void)
{
	// Function declarations
	void toggleFullScreen(void);

	// Code

	// if user is exiting in full screen then restore it to normal 
	if (gbFullScreen == TRUE) {
		toggleFullScreen();
		gbFullScreen = FALSE;
	}

	if (texture_marble) {
		glDeleteTextures(1, &texture_marble);
		texture_marble = 0;
	}

	// Make hdc as current contex by releasing rendering context as current contex
	if (wglGetCurrentContext() == ghrc) {
		wglMakeCurrent(NULL, NULL);
	}

	// Delete the rendering context
	if (ghrc) {
		wglDeleteContext(ghrc);
		ghrc = NULL;
	}

	if (ghwnd) {
		DestroyWindow(ghwnd);
		ghwnd = NULL;
	}
	// Release the DC 
	if (ghdc) {
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	// Close the file
	if (gpFile) {
		fprintf(gpFile, "Program terminated successfully\n");
		fclose(gpFile);
		gpFile = NULL;
	}
}
