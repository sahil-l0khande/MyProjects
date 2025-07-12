
// Win32 headers

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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


GLUquadric* quadric = NULL;

/* Text related variables */
float posH_Y = 1.5f;   // Start above screen
//float targetY_H = 0.0f;
float posB_X = -2.0f;   // Start far left
float targetX_B = -1.5f;  // Final X position (adjust according to your layout)
float posA_Z = -10.0f;     // Start far back
float targetZ_A = 0.0f;    // Final Z position
float posT_X = 2.0f;       // Start from the right (off-screen)
float targetX_T = 1.4f;    // Final position where 'T' should settle
float posR_Y = -2.0f;      // Start from below
//float targetY_R = -0.4f;   // Final resting Y position

float speed = 0.00050f;   // Falling speed
float speed_A = 0.01f;      // Speed of approach

float baseY = -0.4f;  // Same as R's final Y position
float targetY_H = -0.4f;
float targetY_R = -0.4f;

// Plane animation variables
float planeX = -2.5f;
float targetXplane = 3.5f;

/* plane 2 variables */
float targetX2 = 3.0f;
float targetY2 = 0.1f;
float speed2 = 0.00050f;

float plane2X = -3.0f;
float plane2Y = 1.5f;

int planePhase = 0;  // 0 = entry, 1 = straight, 2 = exit
float exitStartX = 2.0f;  // Adjust this to set when plane2 starts going upward
GLfloat straightSpeed = 0.00080f;

BOOL colorB = FALSE;
BOOL colorH = FALSE;
BOOL colorA1 = FALSE;
BOOL colorR = FALSE;
BOOL colorA2 = FALSE;
BOOL colorT = FALSE;

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
	void buildFont(void); // build display lists
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

	//buildFont(); // build display lists

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
	//glOrtho(0.0, width, 0.0, height, -1.0, 1.0);

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);  // FOV-Y , Aspect ratio, Near, far  (conventional value)

}
GLuint base; // Display list base

void drawFlippedCrescent(float cx, float cy, float outerRadius, float innerRadius, float angleOffset, int segments) {
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= segments; i++) {
		float theta = 2.0f * M_PI * i / segments + angleOffset;

		float x_outer = cx + outerRadius * cosf(theta);
		float y_outer = cy + outerRadius * sinf(theta);

		float x_inner = cx + innerRadius * cosf(theta) - innerRadius * 0.5f;
		float y_inner = cy + innerRadius * sinf(theta);

		// Assign color based on Y position (higher Y → orange, middle Y → white, lower Y → green)
		float avgY_outer = (y_outer + 1.0f) / 2.0f; // normalize to 0-1
		if (avgY_outer > 0.66f)
			glColor3f(1.0f, 0.5f, 0.0f); // Orange
		else if (avgY_outer > 0.33f)
			glColor3f(1.0f, 1.0f, 1.0f); // White
		else
			glColor3f(0.0f, 1.0f, 0.0f); // Green
		glVertex3f(x_outer, y_outer, 0.0f);

		float avgY_inner = (y_inner + 1.0f) / 2.0f;
		if (avgY_inner > 0.66f)
			glColor3f(1.0f, 0.5f, 0.0f); // Orange
		else if (avgY_inner > 0.33f)
			glColor3f(1.0f, 1.0f, 1.0f); // White
		else
			glColor3f(0.0f, 1.0f, 0.0f); // Green
		glVertex3f(x_inner, y_inner, 0.0f);
	}
	glEnd();
}

/*
void drawCharA() {
	float w = 0.6f, h = 1.0f;

	glBegin(GL_QUADS);

	// --- Top bar (small box on head of A) ---
	float width = 0.1f;    // width of the top box
	float height = 0.05f;   // height of the top box
	float x_center = 0.3f;  // center X of the A's top
	float y_bottom = 0.95f; // vertical bottom of the box
	glColor3f(1.0f, 0.5f, 0.0f);  // orange (top of box)

	//glColor3f(1.0f, 1.0f, 1.0f);  // white (bottom of box)
	glVertex2f(x_center - width / 2, y_bottom);
	glVertex2f(x_center + width / 2, y_bottom);

	glColor3f(1.0f, 0.5f, 0.0f);  // orange (top of box)
	glVertex2f(x_center + width / 2, y_bottom + height);
	glVertex2f(x_center - width / 2, y_bottom + height);

	// --- Left leg of A ---
	glColor3f(0.0f, 1.0f, 0.0f);  // green (bottom)
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.1f, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f);  // white (middle)
	glVertex2f(0.15f, 0.5f);
	glVertex2f(0.05f, 0.5f);

	glColor3f(1.0f, 1.0f, 1.0f);  // white (middle)
	glVertex2f(0.05f, 0.5f);
	glVertex2f(0.15f, 0.5f);

	glColor3f(1.0f, 0.5f, 0.0f);  // orange (top)
	glVertex2f(0.25f, h);
	glVertex2f(0.15f, h);

	// --- Right leg of A ---
	glColor3f(0.0f, 1.0f, 0.0f);  // green (bottom)
	glVertex2f(0.5f, 0.0f);
	glVertex2f(0.6f, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f);  // white (middle)
	glVertex2f(0.55f, 0.5f);
	glVertex2f(0.45f, 0.5f);

	glColor3f(1.0f, 1.0f, 1.0f);  // white (middle)
	glVertex2f(0.45f, 0.5f);
	glVertex2f(0.55f, 0.5f);

	glColor3f(1.0f, 0.5f, 0.0f);  // orange (top)
	glVertex2f(0.45f, h);
	glVertex2f(0.35f, h);

	// --- Cross bar of A ---
	float cross_x_center = 0.3f;
	float cross_y = 0.50f;
	float cross_width = 0.3f;
	float cross_height = 0.1f;

	glColor3f(1.0f, 1.0f, 1.0f);  // green (bottom)
	glVertex2f(cross_x_center - cross_width / 2, cross_y - cross_height / 2); // bottom-left
	glVertex2f(cross_x_center + cross_width / 2, cross_y - cross_height / 2); // bottom-right

	//glColor3f(1.0f, 0.5f, 0.0f);  // orange (top)
	glVertex2f(cross_x_center + cross_width / 2, cross_y + cross_height / 2); // top-right
	glVertex2f(cross_x_center - cross_width / 2, cross_y + cross_height / 2); // top-left

	glEnd();
}
*/
void drawCharA(BOOL colored) {
	float w = 0.6f, h = 1.0f;

	glBegin(GL_QUADS);

	// --- Top bar (small box on head of A) ---
	float width = 0.1f;
	float height = 0.05f;
	float x_center = 0.3f;
	float y_bottom = 0.95f;

	// Top box
	glColor3f(colored ? 1.0f : 0.5f, colored ? 0.5f : 0.5f, colored ? 0.0f : 0.5f);  // orange or gray
	glVertex2f(x_center - width / 2, y_bottom);
	glVertex2f(x_center + width / 2, y_bottom);
	glVertex2f(x_center + width / 2, y_bottom + height);
	glVertex2f(x_center - width / 2, y_bottom + height);

	// --- Left leg of A ---
	// Bottom (green or gray)
	glColor3f(colored ? 0.0f : 0.5f, colored ? 1.0f : 0.5f, colored ? 0.0f : 0.5f);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.1f, 0.0f);

	// Middle (white or gray)
	glColor3f(colored ? 1.0f : 0.5f, colored ? 1.0f : 0.5f, colored ? 1.0f : 0.5f);
	glVertex2f(0.15f, 0.5f);
	glVertex2f(0.05f, 0.5f);

	glVertex2f(0.05f, 0.5f);
	glVertex2f(0.15f, 0.5f);

	// Top (orange or gray)
	glColor3f(colored ? 1.0f : 0.5f, colored ? 0.5f : 0.5f, colored ? 0.0f : 0.5f);
	glVertex2f(0.25f, h);
	glVertex2f(0.15f, h);

	// --- Right leg of A ---
	// Bottom (green or gray)
	glColor3f(colored ? 0.0f : 0.5f, colored ? 1.0f : 0.5f, colored ? 0.0f : 0.5f);
	glVertex2f(0.5f, 0.0f);
	glVertex2f(0.6f, 0.0f);

	// Middle (white or gray)
	glColor3f(colored ? 1.0f : 0.5f, colored ? 1.0f : 0.5f, colored ? 1.0f : 0.5f);
	glVertex2f(0.55f, 0.5f);
	glVertex2f(0.45f, 0.5f);

	glVertex2f(0.45f, 0.5f);
	glVertex2f(0.55f, 0.5f);

	// Top (orange or gray)
	glColor3f(colored ? 1.0f : 0.5f, colored ? 0.5f : 0.5f, colored ? 0.0f : 0.5f);
	glVertex2f(0.45f, h);
	glVertex2f(0.35f, h);

	// --- Cross bar of A ---
	float cross_x_center = 0.3f;
	float cross_y = 0.50f;
	float cross_width = 0.3f;
	float cross_height = 0.1f;

	glColor3f(colored ? 1.0f : 0.5f, colored ? 1.0f : 0.5f, colored ? 1.0f : 0.5f);
	glVertex2f(cross_x_center - cross_width / 2, cross_y - cross_height / 2);
	glVertex2f(cross_x_center + cross_width / 2, cross_y - cross_height / 2);
	glVertex2f(cross_x_center + cross_width / 2, cross_y + cross_height / 2);
	glVertex2f(cross_x_center - cross_width / 2, cross_y + cross_height / 2);

	glEnd();
}

void drawCharT(BOOL colored) {
	glBegin(GL_QUADS);

	// Top bar
	glColor3f(colored ? 1.0f : 0.5f, colored ? 0.5f : 0.5f, colored ? 0.0f : 0.5f);
	glVertex2f(0.0f, 1.0f);
	glVertex2f(0.6f, 1.0f);
	glVertex2f(0.6f, 0.9f);
	glVertex2f(0.0f, 0.9f);

	// Stem
	glColor3f(colored ? 1.0f : 0.5f, colored ? 1.0f : 0.5f, colored ? 1.0f : 0.5f); // White
	glVertex2f(0.25f, 0.9f);
	glVertex2f(0.35f, 0.9f);

	glColor3f(colored ? 0.0f : 0.5f, colored ? 1.0f : 0.5f, colored ? 0.0f : 0.5f); // Green
	glVertex2f(0.35f, 0.0f);
	glVertex2f(0.25f, 0.0f);

	glEnd();
}

/*
void drawCharT() {
	glBegin(GL_QUADS);

	// --- Top bar (Orange to White, left to right gradient) ---
	// Top-left (Orange)
	glColor3f(1.0f, 0.5f, 0.0f);
	glVertex2f(0.0f, 1.0f);

	// Top-right (Orange)
	glColor3f(1.0f, 0.5f, 0.0f);
	glVertex2f(0.6f, 1.0f);

	// Bottom-right (White)
	//glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.6f, 0.9f);

	// Bottom-left (White)
	//glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.0f, 0.9f);


	// --- Stem (White at top to Green at bottom vertical gradient) ---
	// Top-left (White)
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.25f, 0.9f);

	// Top-right (White)
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.35f, 0.9f);

	// Bottom-right (Green)
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.35f, 0.0f);

	// Bottom-left (Green)
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.25f, 0.0f);

	glEnd();
}
*/ 

/*
void drawCharH() {
	glBegin(GL_QUADS);

	// Left vertical bar (Orange → White → Green)
	glColor3f(0.0f, 1.0f, 0.0f); // Green (bottom)
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.1f, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f); // White (middle)
	glVertex2f(0.1f, 0.5f);
	glVertex2f(0.0f, 0.5f);

	glColor3f(1.0f, 1.0f, 1.0f); // White (middle)
	glVertex2f(0.0f, 0.5f);
	glVertex2f(0.1f, 0.5f);

	glColor3f(1.0f, 0.5f, 0.0f); // Orange (top)
	glVertex2f(0.1f, 1.0f);
	glVertex2f(0.0f, 1.0f);

	// Middle connector (bottom: Green → middle: White → top: Orange)
	glColor3f(0.0f, 1.0f, 0.0f); // Green
	glVertex2f(0.1f, 0.45f);
	glVertex2f(0.5f, 0.45f);

	glColor3f(1.0f, 1.0f, 1.0f); // White
	glVertex2f(0.5f, 0.55f);
	glVertex2f(0.1f, 0.55f);

	// Right vertical bar (Green → White → Orange)
	glColor3f(0.0f, 1.0f, 0.0f); // Green (bottom)
	glVertex2f(0.5f, 0.0f);
	glVertex2f(0.6f, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f); // White (middle)
	glVertex2f(0.6f, 0.5f);
	glVertex2f(0.5f, 0.5f);

	glColor3f(1.0f, 1.0f, 1.0f); // White (middle)
	glVertex2f(0.5f, 0.5f);
	glVertex2f(0.6f, 0.5f);

	glColor3f(1.0f, 0.5f, 0.0f); // Orange (top)
	glVertex2f(0.6f, 1.0f);
	glVertex2f(0.5f, 1.0f);

	glEnd();
}
*/
void drawCharH(BOOL colored) {
	glBegin(GL_QUADS);

	// Left vertical bar
	glColor3f(colored ? 0.0f : 0.5f, colored ? 1.0f : 0.5f, colored ? 0.0f : 0.5f); // Green
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.1f, 0.0f);

	glColor3f(colored ? 1.0f : 0.5f, colored ? 1.0f : 0.5f, colored ? 1.0f : 0.5f); // White
	glVertex2f(0.1f, 0.5f);
	glVertex2f(0.0f, 0.5f);

	glVertex2f(0.0f, 0.5f);
	glVertex2f(0.1f, 0.5f);

	glColor3f(colored ? 1.0f : 0.5f, colored ? 0.5f : 0.5f, colored ? 0.0f : 0.5f); // Orange
	glVertex2f(0.1f, 1.0f);
	glVertex2f(0.0f, 1.0f);

	// Middle connector
	glColor3f(colored ? 0.0f : 0.5f, colored ? 1.0f : 0.5f, colored ? 0.0f : 0.5f); // Green
	glVertex2f(0.1f, 0.45f);
	glVertex2f(0.5f, 0.45f);

	glColor3f(colored ? 1.0f : 0.5f, colored ? 1.0f : 0.5f, colored ? 1.0f : 0.5f); // White
	glVertex2f(0.5f, 0.55f);
	glVertex2f(0.1f, 0.55f);

	// Right vertical bar
	glColor3f(colored ? 0.0f : 0.5f, colored ? 1.0f : 0.5f, colored ? 0.0f : 0.5f); // Green
	glVertex2f(0.5f, 0.0f);
	glVertex2f(0.6f, 0.0f);

	glColor3f(colored ? 1.0f : 0.5f, colored ? 1.0f : 0.5f, colored ? 1.0f : 0.5f); // White
	glVertex2f(0.6f, 0.5f);
	glVertex2f(0.5f, 0.5f);

	glVertex2f(0.5f, 0.5f);
	glVertex2f(0.6f, 0.5f);

	glColor3f(colored ? 1.0f : 0.5f, colored ? 0.5f : 0.5f, colored ? 0.0f : 0.5f); // Orange
	glVertex2f(0.6f, 1.0f);
	glVertex2f(0.5f, 1.0f);

	glEnd();
}

void drawCharB() {
	glBegin(GL_QUADS);

	// Top bar
	if (colorB)
		glColor3f(1.0f, 0.5f, 0.0f);  // Orange or your theme
	else
		glColor3f(0.5f, 0.5f, 0.5f);  // Gray

	glVertex2f(0.0f, 0.90f);  // align with left vertical
	glVertex2f(0.4f, 0.90f);
	glVertex2f(0.4f, 1.0f);
	glVertex2f(0.0f, 1.0f);   // align with left vertical

	// Left vertical
	if (colorB) glColor3f(1.0f, 0.5f, 0.0f); // Orange (top)
	else glColor3f(0.5f, 0.5f, 0.5f);  // Gray
	glVertex2f(0.0f, 1.0f);
	glVertex2f(0.1f, 1.0f);

	if (colorB) glColor3f(1.0f, 1.0f, 1.0f); // White (middle)
	else glColor3f(0.5f, 0.5f, 0.5f);  // Gray
	glVertex2f(0.1f, 0.5f);
	glVertex2f(0.0f, 0.5f);

	// Bottom half: White to Green
	if (colorB) glColor3f(1.0f, 1.0f, 1.0f); // White
	else glColor3f(0.5f, 0.5f, 0.5f);  // Gray
	glVertex2f(0.0f, 0.5f);
	glVertex2f(0.1f, 0.5f);

	if (colorB) glColor3f(0.0f, 1.0f, 0.0f); // Green
	else glColor3f(0.5f, 0.5f, 0.5f);  // Gray
	glVertex2f(0.1f, 0.0f);
	glVertex2f(0.0f, 0.0f);

	// Middle bar (white)
	if (colorB) glColor3f(1.0f, 1.0f, 1.0f);
	else glColor3f(0.5f, 0.5f, 0.5f);  // Gray
	glVertex2f(0.1f, 0.45f);
	glVertex2f(0.4f, 0.45f);
	glVertex2f(0.4f, 0.55f);
	glVertex2f(0.1f, 0.55f);

	// Bottom bar: green to white
	if (colorB) glColor3f(0.0f, 1.0f, 0.0f); // Green
	else glColor3f(0.5f, 0.5f, 0.5f);  // Gray
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.4f, 0.0f);

	if (colorB) glColor3f(1.0f, 1.0f, 1.0f); // White
	else glColor3f(0.5f, 0.5f, 0.5f);  // Gray
	glVertex2f(0.4f, 0.1f);
	glVertex2f(0.0f, 0.1f);

	// Upper curve (orange to white)
	if (colorB) glColor3f(1.0f, 0.5f, 0.0f); // Orange
	else glColor3f(0.5f, 0.5f, 0.5f);  // Gray
	glVertex2f(0.4f, 0.9f);  // Top-left
	glVertex2f(0.5f, 0.85f); // Top-right

	if (colorB) glColor3f(1.0f, 1.0f, 1.0f); // White
	else glColor3f(0.5f, 0.5f, 0.5f);  // Gray
	glVertex2f(0.5f, 0.6f);  // Bottom-right
	glVertex2f(0.4f, 0.55f); // Bottom-left

	// Lower curve (white to green)
	if (colorB) glColor3f(1.0f, 1.0f, 1.0f); // White
	else glColor3f(0.5f, 0.5f, 0.5f);  // Gray
	glVertex2f(0.4f, 0.5f);  // Top-left
	glVertex2f(0.5f, 0.45f); // Top-right

	if (colorB) glColor3f(0.0f, 1.0f, 0.0f); // Green
	else glColor3f(0.5f, 0.5f, 0.5f);  // Gray
	glVertex2f(0.5f, 0.2f);  // Bottom-right
	glVertex2f(0.4f, 0.1f);  // Bottom-left

	glEnd();
}

/*
void drawCharR() {
	glBegin(GL_QUADS);

	// --- Left vertical bar (Orange to White to Green) ---
	// Top half: Orange to White
	glColor3f(1.0f, 0.5f, 0.0f); // Orange (top)
	glVertex2f(0.0f, 1.0f);
	glVertex2f(0.1f, 1.0f);

	glColor3f(1.0f, 1.0f, 1.0f); // White (middle)
	glVertex2f(0.1f, 0.5f);
	glVertex2f(0.0f, 0.5f);

	// Bottom half: White to Green
	glColor3f(1.0f, 1.0f, 1.0f); // White
	glVertex2f(0.0f, 0.5f);
	glVertex2f(0.1f, 0.5f);

	glColor3f(0.0f, 1.0f, 0.0f); // Green
	glVertex2f(0.1f, 0.0f);
	glVertex2f(0.0f, 0.0f);

	// --- Top horizontal bar (Orange to White), same as B ---
	glColor3f(1.0f, 0.5f, 0.0f); // Orange (left)
	glVertex2f(0.1f, 1.0f);
	glVertex2f(0.4f, 1.0f);

	//glColor3f(1.0f, 1.0f, 1.0f); // White (right)
	glVertex2f(0.4f, 0.90f);
	glVertex2f(0.1f, 0.90f);

	// --- Top curl (Orange to White) ---
	glColor3f(1.0f, 0.5f, 0.0f); // Orange
	glVertex2f(0.4f, 0.90f);  // Top-left of curl
	glVertex2f(0.5f, 0.85f);  // Top-right

	glColor3f(1.0f, 1.0f, 1.0f); // White
	glVertex2f(0.5f, 0.6f);  // Bottom-right
	glVertex2f(0.4f, 0.55f); // Bottom-left

	// --- Middle bar (White) ---
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.1f, 0.45f);
	glVertex2f(0.40f, 0.45f);
	glVertex2f(0.40f, 0.55f);
	glVertex2f(0.1f, 0.55f);

	// --- Diagonal leg (White to Green) ---
	glColor3f(1.0f, 1.0f, 1.0f); // Top
	glVertex2f(0.2f, 0.45f);
	glVertex2f(0.3f, 0.45f);

	glColor3f(0.0f, 1.0f, 0.0f); // Bottom
	glVertex2f(0.45f, 0.0f);
	glVertex2f(0.35f, 0.0f);

	glEnd();
}
*/
void drawCharR(BOOL colored) {
	glBegin(GL_QUADS);

	// Left vertical bar (Orange → White → Green)
	glColor3f(colored ? 1.0f : 0.5f, colored ? 0.5f : 0.5f, colored ? 0.0f : 0.5f); // Orange
	glVertex2f(0.0f, 1.0f);
	glVertex2f(0.1f, 1.0f);

	glColor3f(colored ? 1.0f : 0.5f, colored ? 1.0f : 0.5f, colored ? 1.0f : 0.5f); // White
	glVertex2f(0.1f, 0.5f);
	glVertex2f(0.0f, 0.5f);

	glColor3f(colored ? 1.0f : 0.5f, colored ? 1.0f : 0.5f, colored ? 1.0f : 0.5f); // White
	glVertex2f(0.0f, 0.5f);
	glVertex2f(0.1f, 0.5f);

	glColor3f(colored ? 0.0f : 0.5f, colored ? 1.0f : 0.5f, colored ? 0.0f : 0.5f); // Green
	glVertex2f(0.1f, 0.0f);
	glVertex2f(0.0f, 0.0f);

	// Top horizontal bar
	glColor3f(colored ? 1.0f : 0.5f, colored ? 0.5f : 0.5f, colored ? 0.0f : 0.5f); // Orange
	glVertex2f(0.1f, 1.0f);
	glVertex2f(0.4f, 1.0f);
	glVertex2f(0.4f, 0.90f);
	glVertex2f(0.1f, 0.90f);

	// Top curl
	glColor3f(colored ? 1.0f : 0.5f, colored ? 0.5f : 0.5f, colored ? 0.0f : 0.5f); // Orange
	glVertex2f(0.4f, 0.90f);
	glVertex2f(0.5f, 0.85f);

	glColor3f(colored ? 1.0f : 0.5f, colored ? 1.0f : 0.5f, colored ? 1.0f : 0.5f); // White
	glVertex2f(0.5f, 0.6f);
	glVertex2f(0.4f, 0.55f);

	// Middle bar
	glColor3f(colored ? 1.0f : 0.5f, colored ? 1.0f : 0.5f, colored ? 1.0f : 0.5f); // White
	glVertex2f(0.1f, 0.45f);
	glVertex2f(0.40f, 0.45f);
	glVertex2f(0.40f, 0.55f);
	glVertex2f(0.1f, 0.55f);

	// Diagonal leg
	glColor3f(colored ? 1.0f : 0.5f, colored ? 1.0f : 0.5f, colored ? 1.0f : 0.5f); // White
	glVertex2f(0.2f, 0.45f);
	glVertex2f(0.3f, 0.45f);

	glColor3f(colored ? 0.0f : 0.5f, colored ? 1.0f : 0.5f, colored ? 0.0f : 0.5f); // Green
	glVertex2f(0.45f, 0.0f);
	glVertex2f(0.35f, 0.0f);

	glEnd();
}


/*
void buildFont() {
	base = glGenLists(128);
	for (int i = 0; i < 128; i++) {
		glNewList(base + i, GL_COMPILE);
		if (i == 'A') {
			drawCharA();
		}
		else if (i == 'B') {
			drawCharB();
		}
		else if (i == 'H') {
			drawCharH();
		}
		else if (i == 'T') {
			drawCharT();
		}
		else if (i == 'R') {
			drawCharR();
		}
		glTranslatef(0.7f, 0.0f, 0.0f); // advance after each char
		glEndList();
	}
}*/

// Render string at position (x, y), scale, and color
void renderText(float x, float y, float scale, const char* text, float r, float g, float b) {
	glPushMatrix();
	glTranslatef(x, y, 0.0f);
	glScalef(scale, scale, 1.0f);
	glColor3f(r, g, b);
	glListBase(base);
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
	glPopMatrix();
}

void drawPlane(void)
{
	glBegin(GL_TRIANGLES);

	// --- Nose (pointy tip) ---
	glColor3f(0.8f, 0.8f, 0.8f);
	glVertex3f(0.5f, 0.0f, 0.0f);   // Tip of the nose
	glVertex3f(0.2f, 0.1f, 0.0f);
	glVertex3f(0.2f, -0.1f, 0.0f);

	// --- Main Body ---
	glColor3f(0.3f, 0.3f, 0.3f);
	glVertex3f(0.2f, 0.1f, 0.0f);
	glVertex3f(-0.4f, 0.1f, 0.0f);
	glVertex3f(-0.4f, -0.1f, 0.0f);

	glVertex3f(0.2f, 0.1f, 0.0f);
	glVertex3f(0.2f, -0.1f, 0.0f);
	glVertex3f(-0.4f, -0.1f, 0.0f);

	// --- Wings ---
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-0.1f, 0.1f, 0.0f);
	glVertex3f(-0.4f, 0.3f, 0.0f);
	glVertex3f(-0.4f, 0.1f, 0.0f);

	glVertex3f(-0.1f, -0.1f, 0.0f);
	glVertex3f(-0.4f, -0.3f, 0.0f);
	glVertex3f(-0.4f, -0.1f, 0.0f);

	// --- Tail fins ---
	glColor3f(0.6f, 0.6f, 0.6f);
	glVertex3f(-0.4f, 0.05f, 0.0f);
	glVertex3f(-0.6f, 0.15f, 0.0f);
	glVertex3f(-0.6f, 0.05f, 0.0f);

	glVertex3f(-0.4f, -0.05f, 0.0f);
	glVertex3f(-0.6f, -0.15f, 0.0f);
	glVertex3f(-0.6f, -0.05f, 0.0f);

	glEnd();


}

/* Plane 3 */
float plane3X = -3.0f;
float plane3Y = -1.5f;
int plane3Phase = 0;  // 0 = entry, 1 = straight, 2 = exit

void display(void)
{
	// Code

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0f, 0.0f, 4.0f,  // Eye position
		0.0f, 0.0f, 0.0f,   // Look at point
		0.0f, 1.0f, 0.0f);  // Up direction

 
	// B from left
	glPushMatrix();
	glTranslatef(posB_X, baseY, 0.0f);
	drawCharB();
	glPopMatrix();

	// H from top
	glPushMatrix();
	glTranslatef(-0.9f, posH_Y, 0.0f);
	drawCharH(colorH);
	glPopMatrix();

	// A from back (left A)
	glPushMatrix();
	glTranslatef(-0.25f, baseY, posA_Z);
	drawCharA(colorA1);   // For left A
	glPopMatrix();

	// R from bottom
	glPushMatrix();
	glTranslatef(0.4f, posR_Y, 0.0f);
	drawCharR(colorR);
	glPopMatrix();

	// A from back (right A)
	glPushMatrix();
	glTranslatef(0.9f, baseY, posA_Z);
	drawCharA(colorA2);   // For left A
	glPopMatrix();

	// T from right
	glPushMatrix();
	glTranslatef(posT_X, baseY, 0.0f);
	drawCharT(colorT);
	glPopMatrix();

	/* Plane 1 */
	glPushMatrix();
	glTranslatef(planeX, 0.07f, 1.0f);
	glScalef(0.3f, 0.3f, 0.3f);  // Scale down to 50%
	drawPlane();
	glPopMatrix();

	/* Plane 2 */
	glPushMatrix();
	glTranslatef(plane2X, plane2Y, 0.1f);
	glScalef(0.35f, 0.35f, 0.35f);
	drawPlane();
	glPopMatrix();

	/* Plane 3 */
	glPushMatrix();
	glTranslatef(plane3X, plane3Y, 0.1f);
	glScalef(0.35f, 0.35f, 0.35f);
	drawPlane();
	glPopMatrix();

	SwapBuffers(ghdc);

}

void update(void)
{
	/* plane 1 */
	if (posH_Y > targetY_H) {
		posH_Y -= speed;
	}

	if (posB_X < targetX_B) {
		posB_X += speed;
	}

	if (posA_Z < targetZ_A) {
		posA_Z += speed_A;
	}

	if (posT_X > targetX_T) {
		posT_X -= speed;
	}

	if (posR_Y < targetY_R) {
		posR_Y += speed;
	}

	if (planeX < targetXplane) {
		planeX += speed;
	}

	/* plane 2 movement */
	if (planePhase == 0) {
		// Entry diagonal
		if (plane2X < 0.0f) plane2X += speed;
		if (plane2Y > 0.1f) plane2Y -= speed;

		if (plane2X >= 0.0f && plane2Y <= 0.1f) {
			plane2X = 0.0f;
			plane2Y = 0.1f;
			planePhase = 1;
		} 
	}
	else if (planePhase == 1) {
		// Move straight to the right
		plane2X += straightSpeed;

		// Trigger exit phase once x >= 2.0
		if (plane2X >= 2.0f) {
			planePhase = 2;
		}
	}
	else if (planePhase == 2) {
		// Move diagonally upward to top-right corner
		if (plane2X < 4.0f) plane2X += speed;
		if (plane2Y < 2.0f) plane2Y += speed;
	}

	if (plane2X >= -1.5f) colorB = TRUE;   // B at ~-1.5
	if (plane2X >= -0.9f) colorH = TRUE;   // H at ~-0.9
	if (plane2X >= -0.25f) colorA1 = TRUE; // A1 at ~-0.25
	if (plane2X >= 0.4f) colorR = TRUE;    // R at ~0.4
	if (plane2X >= 0.9f) colorA2 = TRUE;   // A2 at ~0.9
	if (plane2X >= 1.4f) colorT = TRUE;    // T at ~1.4

	// Clamp position so it doesn't overshoot
	if (plane2X > 4.0f) plane2X = 4.0f;
	if (plane2Y > 3.0f) plane2Y = 3.0f;


	/* plane 3 movement (mirror of plane 2) */
	if (plane3Phase == 0) {
		// Entry diagonal from bottom-left
		if (plane3X < 0.0f) plane3X += speed;
		if (plane3Y < 0.1f) plane3Y += speed;

		if (plane3X >= 0.0f && plane3Y >= -0.1f) {
			plane3X = 0.0f;
			plane3Y = 0.1f;
			plane3Phase = 1;
		}
	}
	else if (plane3Phase == 1) {
		// Move straight to the right
		plane3X += straightSpeed;

		// Trigger exit phase once x >= 2.0
		if (plane3X >= 2.0f) {
			plane3Phase = 2;
		}
	}
	else if (plane3Phase == 2) {
		// Exit diagonally down-right
		if (plane3X < 4.0f) plane3X += speed;
		if (plane3Y > -2.0f) plane3Y -= speed;
	}

	// Clamp position
	if (plane3X > 4.0f) plane3X = 4.0f;
	if (plane3Y < -2.0f) plane3Y = -2.0f;

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
