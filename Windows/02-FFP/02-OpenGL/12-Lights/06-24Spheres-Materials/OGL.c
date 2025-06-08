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

// Variables for 24 spheres application

BOOL bLight = FALSE;

GLfloat lightAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat lightPosition[] = { 0.0f, 0.0f, 0.0f, 1.0f };

GLfloat lightModelAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat lightModelLocalViewer[] = { 0.0f };

GLfloat angleForXRotation = 0.0f;
GLfloat angleForYRotation = 0.0f;
GLfloat angleForZRotation = 0.0f;
GLint keyPressed = -1;
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
		case 'x':
		case 'X':
			keyPressed = 1;
			angleForXRotation = 0.0f;   // resetting angle for x rotation
			break;
		case 'y':
		case 'Y':
			keyPressed = 2;
			angleForYRotation = 0.0f;	// 
			break;
		case 'Z':
		case 'z':
			keyPressed = 3;
			angleForZRotation = 0.0f;	// 
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

	glShadeModel(GL_SMOOTH);   // Think about smoothness 
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


	// From here onwards openGL code starts
	// Tell opengl to chose the color to clear the screen
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	// Initialize quadric
	quadric = gluNewQuadric();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
	glEnable(GL_LIGHT0);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightModelAmbient);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, lightModelLocalViewer);

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

	// Do orthographic projection

	if (width <= height) { // deal with top  and bototom 
		glOrtho(0.0f,    // left
			15.0f,     // right
			(0.0f * ((GLfloat)height / (GLfloat)width)), // bottom
			(15.0f * ((GLfloat)height / (GLfloat)width)),  // top
			-10.0f,    // near
			10.0f);    // far
	}
	else { // deal with left and right
		glOrtho(
			(0.0f * ((GLfloat)width / (GLfloat)height)), // left
			(12.0f * ((GLfloat)width / (GLfloat)height)),  // right
			0.0f,    // bottom
			15.0f,     // top
			-10.0f,    // near
			10.0f);    // far
	}
}

void display(void)
{
	// Function declaration
	void draw24Spheres(void);

	// Code

	// Clear opengl buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set matrix to model view mode
	glMatrixMode(GL_MODELVIEW);

	// Set it to identity matrix
	glLoadIdentity();


	if (keyPressed == 1) {
		glRotatef(angleForXRotation, 1.0f, 0.0f, 0.f);
		lightPosition[2] = angleForXRotation;
	}
	else if (keyPressed == 2) {
		glRotatef(angleForYRotation, 0.0f, 1.0f, 0.f);
		lightPosition[0] = angleForYRotation;
	}
	else if (keyPressed == 3) {
		glRotatef(angleForZRotation, 0.0f, 0.0f, 1.f);
		lightPosition[1] = angleForZRotation;
	}
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	// draw24spheres
	draw24Spheres();
	// swap the buffers
	SwapBuffers(ghdc);
}

void draw24Spheres(void)
{
	// Variable declarations
	GLfloat materialAmbient[4];
	GLfloat materialDiffuse[4];
	GLfloat materialSpecular[4];
	GLfloat materialShininess;

	// Code

	// 1st sphere of 1st column   emerald

	materialAmbient[0] = 0.0215f;
	materialAmbient[1] = 0.1745f;
	materialAmbient[2] = 0.0215f;
	materialAmbient[3] = 1.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
	
	materialDiffuse[0] = 0.07568f;
	materialDiffuse[1] = 0.61424f;
	materialDiffuse[2] = 0.7567f;
	materialDiffuse[3] = 1.0f;

	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

	materialSpecular[0] = 0.633f;
	materialSpecular[1] = 0.727811f;
	materialSpecular[2] = 0.633f;
	materialSpecular[3] = 1.0f;

	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

	materialShininess = 0.6f * 128;

	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess); 

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(1.5f, 14.0f, 0.0f);
	gluSphere(quadric, 1.0f, 30, 30);

	// 2nd sphere of 1st column

	GLfloat materialAmbient2[4];
	GLfloat materialDiffuse2[4];
	GLfloat materialSpecular2[4];
	GLfloat materialShininess2;

	materialAmbient2[0] = 0.135f;
	materialAmbient2[1] = 0.2225f;
	materialAmbient2[2] = 0.1575f;
	materialAmbient2[3] = 1.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient2);

	materialDiffuse2[0] = 0.54f;
	materialDiffuse2[1] = 0.89f;
	materialDiffuse2[2] = 0.63f;
	materialDiffuse2[3] = 1.0f;

	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse2);

	materialSpecular2[0] = 0.316228f;
	materialSpecular2[1] = 0.316228f;
	materialSpecular2[2] = 0.316228f;
	materialSpecular2[3] = 1.0f;

	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular2);

	materialShininess2 = 0.1f * 128;

	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess2);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(1.5f, 11.5f, 0.0f);
	gluSphere(quadric, 1.0f, 30, 30);

	// 3rd sphere of 1st column

	GLfloat materialAmbient3[4];
	GLfloat materialDiffuse3[4];
	GLfloat materialSpecular3[4];
	GLfloat materialShininess3;

	materialAmbient3[0] = 0.05375f;
	materialAmbient3[1] = 0.05f;
	materialAmbient3[2] = 0.06625f;
	materialAmbient3[3] = 1.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient3);

	materialDiffuse3[0] = 0.18275f;
	materialDiffuse3[1] = 0.17f;
	materialDiffuse3[2] = 0.22525f;
	materialDiffuse3[3] = 1.0f;

	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse3);

	materialSpecular3[0] = 0.332741f;
	materialSpecular3[1] = 0.328634f;
	materialSpecular3[2] = 0.346435f;
	materialSpecular3[3] = 1.0f;

	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular3);

	materialShininess3 = 0.3f * 128;

	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess3);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(1.5f, 9.0f, 0.0f);
	gluSphere(quadric, 1.0f, 30, 30);

	// 4th sphere of 1st column


	GLfloat materialAmbient4[4];
	GLfloat materialDiffuse4[4];
	GLfloat materialSpecular4[4];
	GLfloat materialShininess4;

	materialAmbient4[0] = 0.25f;
	materialAmbient4[1] = 0.20725f;
	materialAmbient4[2] = 0.20725f;
	materialAmbient4[3] = 1.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient4);

	materialDiffuse4[0] = 1.0f;
	materialDiffuse4[1] = 0.829f;
	materialDiffuse4[2] = 0.829f;
	materialDiffuse4[3] = 1.0f;

	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse4);

	materialSpecular4[0] = 0.296648f;
	materialSpecular4[1] = 0.296648f;
	materialSpecular4[2] = 0.296648f;
	materialSpecular4[3] = 1.0f;

	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular4);

	materialShininess4 = 0.088f * 128;

	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess4);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(1.5f, 6.5f, 0.0f);
	gluSphere(quadric, 1.0f, 30, 30);

	// 5th sphere of 1st column

	GLfloat materialAmbient5[4];
	GLfloat materialDiffuse5[4];
	GLfloat materialSpecular5[4];
	GLfloat materialShininess5;

	materialAmbient5[0] = 0.1745f;
	materialAmbient5[1] = 0.01175f;
	materialAmbient5[2] = 0.01175f;
	materialAmbient5[3] = 1.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient5);

	materialDiffuse5[0] = 0.61424f;
	materialDiffuse5[1] = 0.04136f;
	materialDiffuse5[2] = 0.04136f;
	materialDiffuse5[3] = 1.0f;

	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse5);

	materialSpecular5[0] = 0.727811f;
	materialSpecular5[1] = 0.626959f;
	materialSpecular5[2] = 0.626959f;
	materialSpecular5[3] = 1.0f;

	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular5);

	materialShininess5 = 0.6f * 128;

	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess5);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(1.5f, 4.0f, 0.0f);
	gluSphere(quadric, 1.0f, 30, 30);

	// 6th sphere of 1st column

	GLfloat materialAmbient6[4];
	GLfloat materialDiffuse6[4];
	GLfloat materialSpecular6[4];
	GLfloat materialShininess6;

	materialAmbient6[0] = 0.1f;
	materialAmbient6[1] = 0.18725f;
	materialAmbient6[2] = 0.1745f;
	materialAmbient6[3] = 1.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient6);

	materialDiffuse6[0] = 0.396f;
	materialDiffuse6[1] = 0.74151f;
	materialDiffuse6[2] = 0.69102f;
	materialDiffuse6[3] = 1.0f;

	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse6);

	materialSpecular6[0] = 0.297254f;
	materialSpecular6[1] = 0.30829f;
	materialSpecular6[2] = 0.306678f;
	materialSpecular6[3] = 1.0f;

	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular6);

	materialShininess6 = 0.1f * 128;

	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess6);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(1.5f, 1.5f, 0.0f);
	gluSphere(quadric, 1.0f, 30, 30);

	// 1st sphere of 2nd column 

	GLfloat materialAmbient7[4];
	GLfloat materialDiffuse7[4];
	GLfloat materialSpecular7[4];
	GLfloat materialShininess7;

	// ambient material
	materialAmbient7[0] = 0.329412f; // r
	materialAmbient7[1] = 0.223529f; // g
	materialAmbient7[2] = 0.027451f; // b
	materialAmbient7[3] = 1.0f;      // a
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient7);

	// diffuse material
	materialDiffuse7[0] = 0.780392f; // r
	materialDiffuse7[1] = 0.568627f; // g
	materialDiffuse7[2] = 0.113725f; // b
	materialDiffuse7[3] = 1.0f;      // a
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse7);

	// specular material
	materialSpecular7[0] = 0.992157f; // r
	materialSpecular7[1] = 0.941176f; // g
	materialSpecular7[2] = 0.807843f; // b
	materialSpecular7[3] = 1.0f;      // a
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular7);

	// shininess
	materialShininess7 = 0.21794872f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess7);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(7.5f, 14.0f, 0.0f);
	gluSphere(quadric, 1.0f, 30, 30);


	// 2nd sphere of 2nd column

	GLfloat materialAmbient8[4];
	GLfloat materialDiffuse8[4];
	GLfloat materialSpecular8[4];
	GLfloat materialShininess8;

	// ambient material
	materialAmbient8[0] = 0.2125f;  // r
	materialAmbient8[1] = 0.1275f;  // g
	materialAmbient8[2] = 0.054f;   // b
	materialAmbient8[3] = 1.0f;     // a
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient8);

	// diffuse material
	materialDiffuse8[0] = 0.714f;     // r
	materialDiffuse8[1] = 0.4284f;    // g
	materialDiffuse8[2] = 0.18144f;   // b
	materialDiffuse8[3] = 1.0f;       // a
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse8);

	// specular material
	materialSpecular8[0] = 0.393548f; // r
	materialSpecular8[1] = 0.271906f; // g
	materialSpecular8[2] = 0.166721f; // b
	materialSpecular8[3] = 1.0f;      // a
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular8);

	// shininess
	materialShininess8 = 0.2f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess8);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(7.5f, 11.5f, 0.0f); // adjust Y as per row
	gluSphere(quadric, 1.0f, 30, 30);

	// 3rd sphere of 2nd column

	GLfloat materialAmbient9[4];
	GLfloat materialDiffuse9[4];
	GLfloat materialSpecular9[4];
	GLfloat materialShininess9;

	// ambient material
	materialAmbient9[0] = 0.25f;  // r
	materialAmbient9[1] = 0.25f;  // g
	materialAmbient9[2] = 0.25f;   // b
	materialAmbient9[3] = 1.0f;     // a
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient9);

	// diffuse material
	materialDiffuse9[0] = 0.4f;     // r
	materialDiffuse9[1] = 0.4f;    // g
	materialDiffuse9[2] = 0.4f;   // b
	materialDiffuse9[3] = 1.0f;       // a
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse9);

	// specular material
	materialSpecular9[0] = 0.774597f; // r
	materialSpecular9[1] = 0.774597f; // g
	materialSpecular9[2] = 0.774597f; // b
	materialSpecular9[3] = 1.0f;      // a
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular9);

	// shininess
	materialShininess9 = 0.6f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess9);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(7.5f, 9.0f, 0.0f); // adjust Y as per row
	gluSphere(quadric, 1.0f, 30, 30);

	// 4th sphere of 2nd column

	GLfloat materialAmbient10[4];
	GLfloat materialDiffuse10[4];
	GLfloat materialSpecular10[4];
	GLfloat materialShininess10;

	// ambient material
	materialAmbient10[0] = 0.19125f;  // r
	materialAmbient10[1] = 0.0735f;  // g
	materialAmbient10[2] = 0.0225f;   // b
	materialAmbient10[3] = 1.0f;     // a
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient10);

	// diffuse material
	materialDiffuse10[0] = 0.7038f;     // r
	materialDiffuse10[1] = 0.27048f;    // g
	materialDiffuse10[2] = 0.0828f;   // b
	materialDiffuse10[3] = 1.0f;       // a
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse10);

	// specular material
	materialSpecular10[0] = 0.256777f; // r
	materialSpecular10[1] = 0.137622f; // g
	materialSpecular10[2] = 0.086014f; // b
	materialSpecular10[3] = 1.0f;      // a
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular10);

	// shininess
	materialShininess10 = 0.1f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess10);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(7.5f, 6.5f, 0.0f); // adjust Y as per row
	gluSphere(quadric, 1.0f, 30, 30);

	// 5th sphere of 2nd column

	GLfloat materialAmbient11[4];
	GLfloat materialDiffuse11[4];
	GLfloat materialSpecular11[4];
	GLfloat materialShininess11;

	// ambient material
	materialAmbient11[0] = 0.24725f;  // r
	materialAmbient11[1] = 0.1995f;  // g
	materialAmbient11[2] = 0.0745f;   // b
	materialAmbient11[3] = 1.0f;     // a
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient11);

	// diffuse material
	materialDiffuse11[0] = 0.75164f;     // r
	materialDiffuse11[1] = 0.60648f;    // g
	materialDiffuse11[2] = 0.22648f;   // b
	materialDiffuse11[3] = 1.0f;       // a
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse11);

	// specular material
	materialSpecular11[0] = 0.628281f; // r
	materialSpecular11[1] = 0.555802f; // g
	materialSpecular11[2] = 0.366065f; // b
	materialSpecular11[3] = 1.0f;      // a
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular11);

	// shininess
	materialShininess11 = 0.4f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess11);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(7.5f, 4.0f, 0.0f); // adjust Y as per row
	gluSphere(quadric, 1.0f, 30, 30);

	// 6th sphere of 2nd column

	GLfloat materialAmbient12[4];
	GLfloat materialDiffuse12[4];
	GLfloat materialSpecular12[4];
	GLfloat materialShininess12;

	// ambient material
	materialAmbient12[0] = 0.19225f;  // r
	materialAmbient12[1] = 0.19225f;  // g
	materialAmbient12[2] = 0.19225f;   // b
	materialAmbient12[3] = 1.0f;     // a
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient12);

	// diffuse material
	materialDiffuse12[0] = 0.50754f;     // r
	materialDiffuse12[1] = 0.50754f;    // g
	materialDiffuse12[2] = 0.50754f;   // b
	materialDiffuse12[3] = 1.0f;       // a
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse12);

	// specular material
	materialSpecular12[0] = 0.508273f; // r
	materialSpecular12[1] = 0.508273f; // g
	materialSpecular12[2] = 0.508273f; // b
	materialSpecular12[3] = 1.0f;      // a
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular12);

	// shininess
	materialShininess12 = 0.4f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess12);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(7.5f, 1.5f, 0.0f); // adjust Y as per row
	gluSphere(quadric, 1.0f, 30, 30);

	// 1st sphere of 3rd column

	GLfloat materialAmbient13[4];
	GLfloat materialDiffuse13[4];
	GLfloat materialSpecular13[4];
	GLfloat materialShininess13;

	// ambient
	materialAmbient13[0] = 0.0f;
	materialAmbient13[1] = 0.0f;
	materialAmbient13[2] = 0.0f;
	materialAmbient13[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient13);

	// diffuse
	materialDiffuse13[0] = 0.01f;
	materialDiffuse13[1] = 0.01f;
	materialDiffuse13[2] = 0.01f;
	materialDiffuse13[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse13);

	// specular
	materialSpecular13[0] = 0.50f;
	materialSpecular13[1] = 0.50f;
	materialSpecular13[2] = 0.50f;
	materialSpecular13[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular13);

	// shininess
	materialShininess13 = 0.25f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess13);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(13.5f, 14.0f, 0.0f);
	gluSphere(quadric, 1.0f, 30, 30);

	// ***** 2nd sphere on 3rd column, cyan *****

	GLfloat materialAmbient14[4];
	GLfloat materialDiffuse14[4];
	GLfloat materialSpecular14[4];
	GLfloat materialShininess14;

	// ambient material
	materialAmbient14[0] = 0.0f;
	materialAmbient14[1] = 0.1f;
	materialAmbient14[2] = 0.06f;
	materialAmbient14[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient14);

	// diffuse material
	materialDiffuse14[0] = 0.0f;
	materialDiffuse14[1] = 0.50980392f;
	materialDiffuse14[2] = 0.50980392f;
	materialDiffuse14[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse14);

	// specular material
	materialSpecular14[0] = 0.50196078f;
	materialSpecular14[1] = 0.50196078f;
	materialSpecular14[2] = 0.50196078f;
	materialSpecular14[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular14);

	// shininess
	materialShininess14 = 0.25f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess14);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(13.5f, 11.5f, 0.0f);
	gluSphere(quadric, 1.0f, 30, 30);

	// ***** 3rd sphere on 2nd column, green *****
	
	GLfloat materialAmbient15[4];
	GLfloat materialDiffuse15[4];
	GLfloat materialSpecular15[4];
	GLfloat materialShininess15;

	// ambient material
	materialAmbient15[0] = 0.0f;
	materialAmbient15[1] = 0.0f;
	materialAmbient15[2] = 0.0f;
	materialAmbient15[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient15);

	// diffuse material
	materialDiffuse15[0] = 0.1f;
	materialDiffuse15[1] = 0.35f;
	materialDiffuse15[2] = 0.1f;
	materialDiffuse15[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse15);

	// specular material
	materialSpecular15[0] = 0.45f;
	materialSpecular15[1] = 0.55f;
	materialSpecular15[2] = 0.45f;
	materialSpecular15[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular15);

	// shininess
	materialShininess15 = 0.25f * 128;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess15);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(13.5f, 9.0f, 0.0f); // adjust Y as per row
	gluSphere(quadric, 1.0f, 30, 30);


	// ***** 4th sphere on 3rd column, red *****

	GLfloat materialAmbient16[4];
	GLfloat materialDiffuse16[4];
	GLfloat materialSpecular16[4];
	GLfloat materialShininess16;

	// ambient material
	materialAmbient16[0] = 0.0f;
	materialAmbient16[1] = 0.0f;
	materialAmbient16[2] = 0.0f;
	materialAmbient16[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient16);

	// diffuse material
	materialDiffuse16[0] = 0.5f;
	materialDiffuse16[1] = 0.0f;
	materialDiffuse16[2] = 0.0f;
	materialDiffuse16[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse16);

	// specular material
	materialSpecular16[0] = 0.7f;
	materialSpecular16[1] = 0.6f;
	materialSpecular16[2] = 0.6f;
	materialSpecular16[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular16);

	// shininess
	materialShininess16 = 0.25f * 128;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess16);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(13.5f, 6.5f, 0.0f); // adjust Y as per row
	gluSphere(quadric, 1.0f, 30, 30);

	// ***** 5th sphere on 3rd column, white *****

	GLfloat materialAmbient17[4];
	GLfloat materialDiffuse17[4];
	GLfloat materialSpecular17[4];
	GLfloat materialShininess17;

	// ambient material
	materialAmbient17[0] = 0.0f;
	materialAmbient17[1] = 0.0f;
	materialAmbient17[2] = 0.0f;
	materialAmbient17[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient17);

	// diffuse material
	materialDiffuse17[0] = 0.55f;
	materialDiffuse17[1] = 0.55f;
	materialDiffuse17[2] = 0.55f;
	materialDiffuse17[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse17);

	// specular material
	materialSpecular17[0] = 0.70f;
	materialSpecular17[1] = 0.70f;
	materialSpecular17[2] = 0.70f;
	materialSpecular17[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular17);

	// shininess
	materialShininess17 = 0.25f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess17);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(13.5f, 4.0f, 0.0f); // adjust Y as per row
	gluSphere(quadric, 1.0f, 30, 30);

	// ***** 6th sphere on 3rd column, yellow plastic *****

	GLfloat materialAmbient18[4];
	GLfloat materialDiffuse18[4];
	GLfloat materialSpecular18[4];
	GLfloat materialShininess18;

	// ambient material
	materialAmbient18[0] = 0.0f;
	materialAmbient18[1] = 0.0f;
	materialAmbient18[2] = 0.0f;
	materialAmbient18[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient18);

	// diffuse material
	materialDiffuse18[0] = 0.5f;
	materialDiffuse18[1] = 0.5f;
	materialDiffuse18[2] = 0.0f;
	materialDiffuse18[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse18);

	// specular material
	materialSpecular18[0] = 0.60f;
	materialSpecular18[1] = 0.60f;
	materialSpecular18[2] = 0.50;
	materialSpecular18[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular18);

	// shininess
	materialShininess18 = 0.25f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess18);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(13.5f, 1.5f, 0.0f); // adjust Y as per row
	gluSphere(quadric, 1.0f, 30, 30);

	// ***** 1st sphere on 4th column, black *****

	GLfloat materialAmbient19[4];
	GLfloat materialDiffuse19[4];
	GLfloat materialSpecular19[4];
	GLfloat materialShininess19;

	// ambient material
	materialAmbient19[0] = 0.02f;
	materialAmbient19[1] = 0.02f;
	materialAmbient19[2] = 0.02f;
	materialAmbient19[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient19);

	// diffuse material
	materialDiffuse19[0] = 0.01f;
	materialDiffuse19[1] = 0.01f;
	materialDiffuse19[2] = 0.01f;
	materialDiffuse19[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse19);

	// specular material
	materialSpecular19[0] = 0.4f;
	materialSpecular19[1] = 0.4f;
	materialSpecular19[2] = 0.4f;
	materialSpecular19[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular19);

	// shininess
	materialShininess19 = 0.078125f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess19);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(19.5f, 14.0f, 0.0f); // adjust Y as per row
	gluSphere(quadric, 1.0f, 30, 30);

	// ***** 2nd sphere on 4th column, cyan *****

	GLfloat materialAmbient20[4];
	GLfloat materialDiffuse20[4];
	GLfloat materialSpecular20[4];
	GLfloat materialShininess20;

	// ambient material
	materialAmbient20[0] = 0.0f;
	materialAmbient20[1] = 0.05f;
	materialAmbient20[2] = 0.05f;
	materialAmbient20[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient20);

	// diffuse material
	materialDiffuse20[0] = 0.4f;
	materialDiffuse20[1] = 0.5f;
	materialDiffuse20[2] = 0.5f;
	materialDiffuse20[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse20);

	// specular material
	materialSpecular20[0] = 0.04f;
	materialSpecular20[1] = 0.7f;
	materialSpecular20[2] = 0.7f;
	materialSpecular20[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular20);

	// shininess
	materialShininess20 = 0.078125f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess20);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(19.5f, 11.5f, 0.0f); // adjust Y as per row
	gluSphere(quadric, 1.0f, 30, 30);

	// ***** 3rd sphere on 4th column, green *****

	GLfloat materialAmbient21[4];
	GLfloat materialDiffuse21[4];
	GLfloat materialSpecular21[4];
	GLfloat materialShininess21;

	// ambient material
	materialAmbient21[0] = 0.0f;
	materialAmbient21[1] = 0.05f;
	materialAmbient21[2] = 0.0f;
	materialAmbient21[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient21);

	// diffuse material
	materialDiffuse21[0] = 0.4f;
	materialDiffuse21[1] = 0.5f;
	materialDiffuse21[2] = 0.4f;
	materialDiffuse21[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse21);

	// specular material
	materialSpecular21[0] = 0.04f;
	materialSpecular21[1] = 0.7f;
	materialSpecular21[2] = 0.04f;
	materialSpecular21[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular21);

	// shininess
	materialShininess21 = 0.078125f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess21);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(19.5f, 9.0f, 0.0f); // adjust Y as per row
	gluSphere(quadric, 1.0f, 30, 30);

	// ***** 4th sphere on 4th column, red *****

	GLfloat materialAmbient22[4];
	GLfloat materialDiffuse22[4];
	GLfloat materialSpecular22[4];
	GLfloat materialShininess22;

	// ambient material
	materialAmbient22[0] = 0.05f;
	materialAmbient22[1] = 0.0f;
	materialAmbient22[2] = 0.0f;
	materialAmbient22[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient22);

	// diffuse material
	materialDiffuse22[0] = 0.5f;
	materialDiffuse22[1] = 0.4f;
	materialDiffuse22[2] = 0.4f;
	materialDiffuse22[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse22);

	// specular material
	materialSpecular22[0] = 0.7f;
	materialSpecular22[1] = 0.04f;
	materialSpecular22[2] = 0.04f;
	materialSpecular22[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular22);

	// shininess
	materialShininess22 = 0.078125f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess22);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(19.5f, 6.5f, 0.0f); // adjust Y as per row
	gluSphere(quadric, 1.0f, 30, 30);

	// ***** 5th sphere on 4th column, white *****

	GLfloat materialAmbient23[4];
	GLfloat materialDiffuse23[4];
	GLfloat materialSpecular23[4];
	GLfloat materialShininess23;

	// ambient material
	materialAmbient23[0] = 0.05f;
	materialAmbient23[1] = 0.05f;
	materialAmbient23[2] = 0.05f;
	materialAmbient23[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient23);

	// diffuse material
	materialDiffuse23[0] = 0.5f;
	materialDiffuse23[1] = 0.5f;
	materialDiffuse23[2] = 0.5f;
	materialDiffuse23[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse23);

	// specular material
	materialSpecular23[0] = 0.7f;
	materialSpecular23[1] = 0.7f;
	materialSpecular23[2] = 0.7f;
	materialSpecular23[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular23);

	// shininess
	materialShininess23 = 0.078125f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess23);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(19.5f, 4.0f, 0.0f); // adjust Y as per row
	gluSphere(quadric, 1.0f, 30, 30);

	// ***** 6th sphere on 4th column, yellow rubber *****

	GLfloat materialAmbient24[4];
	GLfloat materialDiffuse24[4];
	GLfloat materialSpecular24[4];
	GLfloat materialShininess24;

	// ambient material
	materialAmbient24[0] = 0.05f;
	materialAmbient24[1] = 0.05f;
	materialAmbient24[2] = 0.0f;
	materialAmbient24[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient24);

	// diffuse material
	materialDiffuse24[0] = 0.5f;
	materialDiffuse24[1] = 0.5f;
	materialDiffuse24[2] = 0.4f;
	materialDiffuse24[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse24);

	// specular material
	materialSpecular24[0] = 0.7f;
	materialSpecular24[1] = 0.7f;
	materialSpecular24[2] = 0.04f;
	materialSpecular24[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular24);

	// shininess
	materialShininess24 = 0.078125f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess24);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(19.5f, 1.5f, 0.0f); // adjust Y as per row
	gluSphere(quadric, 1.0f, 30, 30);

}

void update(void)
{
	// Code
	angleForXRotation = angleForXRotation + 1.0f;
	if (angleForXRotation >= 360.0f) {
		angleForXRotation = -360.0f;
	}

	angleForYRotation = angleForYRotation + 1.0f;
	if (angleForYRotation >= 360.0f) {
		angleForYRotation = -360.0f;
	}

	angleForZRotation = angleForZRotation + 1.0f;
	if (angleForZRotation >= 360.0f) {
		angleForZRotation = -360.0f;
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
