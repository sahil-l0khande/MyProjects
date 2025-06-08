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

GLUquadric* quadric = NULL;

// 
BOOL bLight = FALSE;
GLfloat lightAmbientZero[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat lightDiffuseZero[] = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat lightSpecularZero[] = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat lightPositionZero[] = { 0.0f, 0.0f, 0.0f, 1.0f };

GLfloat lightAmbientOne[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat lightDiffuseOne[] = { 0.0f, 1.0f, 0.0f, 1.0f };
GLfloat lightSpecularOne[] = { 0.0f, 1.0f, 0.0f, 1.0f };
GLfloat lightPositionOne[] = { 0.0f, 0.0f, 0.0f, 1.0f };

GLfloat lightAmbientTwo[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat lightDiffuseTwo[] = { 0.0f, 0.0f, 1.0f, 1.0f };
GLfloat lightSpecularTwo[] = { 0.0f, 0.0f, 1.0f, 1.0f };
GLfloat lightPositionTwo[] = { 0.0f, 0.0f, 0.0f, 1.0f };

GLfloat materialAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat materialDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat materialSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat materialShininess = 50.0f;

GLfloat lightAngleZero = 0.0f;
GLfloat lightAngleOne = 0.0f;
GLfloat lightAngleTwo = 0.0f;

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
				gbFullScreen = FALSE;
			}
			break;
		case 'L':
		case 'l':
			if (bLight == FALSE) {
				bLight = TRUE;
				glEnable(GL_LIGHTING);
			}
			else {
				bLight = FALSE;
				glDisable(GL_LIGHTING);
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

	// Initialize quadric
	quadric = gluNewQuadric();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbientZero);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuseZero);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecularZero);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbientOne);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuseOne);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecularOne);
	glEnable(GL_LIGHT1);

	glLightfv(GL_LIGHT2, GL_AMBIENT, lightAmbientTwo);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, lightDiffuseTwo);
	glLightfv(GL_LIGHT2, GL_SPECULAR, lightSpecularTwo);
	glEnable(GL_LIGHT2);

	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);

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

	// Clear opengl buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set matrix to model view mode
	glMatrixMode(GL_MODELVIEW);

	// Set it to identity matrix
	glLoadIdentity();
	glPushMatrix();

	// Do view transformation
	gluLookAt(0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// RED light rotation
	glPushMatrix();
	glRotatef(lightAngleZero, 1.0f, 0.0f, 0.0f);
	lightPositionZero[2] = lightAngleZero;
	glLightfv(GL_LIGHT0, GL_POSITION, lightPositionZero);
	glPopMatrix();

	// GREEN light rotation
	glPushMatrix();
	glRotatef(lightAngleOne, 0.0f, 1.0f, 0.0f);
	lightPositionOne[0] = lightAngleOne;
	glLightfv(GL_LIGHT1, GL_POSITION, lightPositionOne);
	glPopMatrix();

	// BLUE light rotation
	glPushMatrix();
	glRotatef(lightAngleTwo, 0.0f, 0.0f, 1.0f);
	lightPositionTwo[1] = lightAngleTwo;
	glLightfv(GL_LIGHT2, GL_POSITION, lightPositionTwo);
	glPopMatrix();

	/* Code for Sun */
	// Save above transformation into modelview matrix stack
	glPushMatrix();

	// Adjust the poles of sphere of sun
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // x bhovtine rotate karav lagtay 

	// Set sun's polygon properties 
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // polygon che front and back bhariv kr , solid 

	gluSphere(quadric, 0.75f, 30, 30); // ha sphere draw karnare , glu mdhla ahe he , 2:radius of sphere , 3,4 : sphere la subdivision kr, MOre the subdivision smoother the surface
	glPopMatrix();
	glPopMatrix();
	// swap the buffers
	SwapBuffers(ghdc);
}

void update(void)
{
	// Code
	// update red light angle

	lightAngleZero = lightAngleZero + 0.2f;
	if (lightAngleZero >= 360.0f) {
		lightAngleZero = lightAngleZero - 360.0f;
	}

	// Update green light angle
	lightAngleOne = lightAngleOne + 0.2f;
	if (lightAngleOne >= 360.0f)
		lightAngleOne = lightAngleOne - 360.0f;

	// Update blue light Angle
	lightAngleTwo = lightAngleTwo + 0.2f;
	if (lightAngleTwo >= 360.0f)
		lightAngleTwo = lightAngleTwo - 360.0f;
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

	if (quadric) {
		gluDeleteQuadric(quadric);
		quadric = NULL;
	}

	// Close the file
	if (gpFile) {
		fprintf(gpFile, "Program terminated successfully\n");
		fclose(gpFile);
		gpFile = NULL;
	}
}
