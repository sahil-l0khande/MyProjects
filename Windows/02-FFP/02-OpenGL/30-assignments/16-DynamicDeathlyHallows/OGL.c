
// Win32 headers

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "OGL.h"	// Custom header file
#define _USE_MATH_DEFINES // for C
#include <math.h>
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

GLfloat posX = -1.6f;    // starting X
GLfloat posY = -1.2f;    // starting Y
GLfloat rotationY = 0.0f; // rotation around Y
int rotationsDone = 0;   // count full rotations
float startX = -1.6f;
float startY = -1.2f;
float endX = 0.0f;
float endY = 0.0f;
float dirX, dirY;
float moveSpeed = 0.002f;
float distanceToCenter = 0.0f;
BOOL directionSet = FALSE;


BOOL movingToCenter = TRUE; // state: moving or rotating at center


GLfloat rotationCZ = 0.0f;
BOOL circleReachedCenter = TRUE;
GLfloat posCX = 1.6f;    // starting X
GLfloat posCY = -1.2f;    // starting Y
GLfloat rotationCY = 0.0f; // rotation around Y
int rotationsCDone = 0;   // count full rotations

GLUquadric* quadric = NULL;

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
				gbFullScreen = TRUE;
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
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// Tell opengl to chose the color to clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	quadric = gluNewQuadric();
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
	// Code

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0f, 0.0f, 4.0f,  // Eye position
		0.0f, 0.0f, 0.0f,   // Look at point
		0.0f, 1.0f, 0.0f);  // Up direction

	glPushMatrix();

	// Apply movement and rotation
	glTranslatef(posX, posY, 0.0f);
	glRotatef(rotationY, 0.0f, 1.0f, 0.0f);

		
	// Draw object
	// Triangle
	glBegin(GL_LINES);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(0.0f, 0.5f, 0.0f);
		// left bottom
		//glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.0f);
		// right bottom
		//glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.5f, 0.0f);
		glVertex3f(0.5f, -0.5f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.0f);

		glVertex3f(0.5f, -0.5f, 0.0f);
	glEnd();

	glPopMatrix();


	// Circle
	glPushMatrix();

	glTranslatef(posCX, posCY, 0.0f);
	glRotatef(rotationCY, 0.0f, 1.0f, 0.0f);

	const int sides = 30;
	const double radius = 0.30;
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 1.0f, 0.0f);
	for (int i = 0; i < 360; i += 360 / sides) {
		double heading = i * M_PI / 180;
		glVertex3f(cos(heading) * radius, sin(heading) * radius - 0.19f, 0.0f);
	}
	glEnd();	
	
	glPopMatrix();

	glPushMatrix();

	glTranslatef(0.0f, posCX, 0.0f);

	// Vertical line 
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.5f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glVertex3f(0.0f, -0.5f, 0.0f);
	glEnd();

	SwapBuffers(ghdc);

}

void update(void)
{
	// Code

	if (movingToCenter)
	{
		if (!directionSet) {
			// Compute normalized direction vector
			float dx = endX - startX;
			float dy = endY - startY;
			distanceToCenter = sqrtf(dx * dx + dy * dy);
			dirX = dx / distanceToCenter;
			dirY = dy / distanceToCenter;
			directionSet = TRUE;
		}

		// Move along the diagonal
		posX += dirX * moveSpeed;
		posY += dirY * moveSpeed;

		// Rotate while moving
		rotationY += 0.2f;

		// Check if reached center
		float dx = endX - posX;
		float dy = endY - posY;
		float remaining = sqrtf(dx * dx + dy * dy);
		if (remaining <= 0.01f)
		{
			movingToCenter = FALSE;
			rotationsDone = 0;
			posX = endX;
			posY = endY;
		}
	}
	else
	{
		if (rotationsDone < 5)
		{
			rotationY += 0.2f;
			if (rotationY >= 360.0f)
			{
				rotationY -= 360.0f;
				rotationsDone++;
			}
		}
	}



	if (circleReachedCenter)
	{
		// Move diagonally towards center (slower)
		if (posCX > 0.0f)
			posCX -= 0.0005f;  // Move left (was 0.01f)
		if (posCY < 0.0f)
			posCY += 0.0005f;  // Move up (was 0.01f)

		// Rotate while moving (slower)
		rotationCY += 0.2f;  // was 5.0f

		// If reached center (small tolerance for float)
		if (posCX <= 0.0f && posCY >= 0.0f)
		{
			circleReachedCenter = FALSE;
			rotationsCDone = 0;
		}
	}
	else
	{
		// Stay at center and rotate (slower)
		if (rotationsCDone < 5)
		{
			rotationCY += 0.2f;  // was 1.0f

			// Count complete rotations
			if (rotationCY >= 360.0f)
			{
				rotationCY -= 360.0f;
				rotationsCDone++;
			}
		}
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
