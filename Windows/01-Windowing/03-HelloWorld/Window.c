// Win32 headers

#include <Windows.h>

// Global function declarations

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Entry point function

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("RTR6");

	// Code

	// Windowclass initialization

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//REgistration window class

	RegisterClassEx(&wndclass);

	// create window

	hwnd = CreateWindow(szAppName, TEXT("Sahil Rajendra Lokhande"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	// Show window
	ShowWindow(hwnd, iCmdShow);

	// messageloop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);
}

// Callback function

LRESULT CALLBACK WndProc(HWND hwnd, UINT imsg, WPARAM wParam, LPARAM lParam)
{
	// Variable declarations
	HDC hdc;
	PAINTSTRUCT ps;   // resize keli window tari apla text persist thevychy
	RECT rc;
	static int iPaintFlag = -1;
	TCHAR str[] = TEXT("Hello World !!!");
	
	// code
	switch (imsg)
	{
	case WM_PAINT:	// Ha retained mode cha type ahe , GDI+ ne karu shaktop online rendering , Ha postem message ahe, ha 8 setuations madhe ueto
					// 1  : jevha jevha window first time display hote
			// 2. Window firavtana parat parat paint hotiye
				// 3. ekhada icon window varun move kartana
				// 4. Mouse cha arrow jevha window varaun jato
				// 5. System menu jevha app chi window zakto , when oyu pullback menu
				// 6. Resize kelyavr window la
				// 7. scrolling chya velela hoanr repaint
				// 8. when partially covered portion of window is uncovered then paint is done
		GetClientRect(hwnd, &rc);
		//hdc = GetDC(hwnd);    // Handle to device(graphic card) 
		hdc = BeginPaint(hwnd, &ps);   // paint karaychay  ps ha bharun yeil
		SetBkColor(hdc, RGB(0, 0, 0));  // Window paint kar , black window varti mazya text chi background , RGB ha macro ahe range (0 - 255 = 256) 
		//SetTextColor(hdc, RGB(0, 255, 0));
		if (iPaintFlag == 1) {
			SetTextColor(hdc, RGB(255, 0, 0));
		}
		else if (iPaintFlag == 2) {
			SetTextColor(hdc, RGB(0, 255, 0));
		}
		else if (iPaintFlag == 3) {
			SetTextColor(hdc, RGB(0, 0, 255));
		}
		else if (iPaintFlag == 4) {
			SetTextColor(hdc, RGB(255, 255, 0));
		}
		else if (iPaintFlag == 5) {
			SetTextColor(hdc, RGB(0, 255, 255));
		}
		else if (iPaintFlag == 6) {
			SetTextColor(hdc, RGB(255, 0, 255));
		}
		else if (iPaintFlag == 7) {
			SetTextColor(hdc, RGB(255, 255, 255));
		}
		DrawText(hdc, str, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);  // Full text pahije tr -1 pathvaych, Draw text ne single line kadhun de | horizontally center | vertically center
		//ReleaseDC(hwnd, hdc);
		EndPaint(hwnd, &ps);
		break;
	case WM_CHAR:
		switch (wParam)
		{
		case 'R':
		case 'r':
			iPaintFlag = 1;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 'G':
		case 'g':
			iPaintFlag = 2;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 'B':
		case 'b':
			iPaintFlag = 3;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 'Y':
		case 'y':
			iPaintFlag = 4;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 'C':
		case 'c':
			iPaintFlag = 5;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 'M':
		case 'm':
			iPaintFlag = 6;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 'W':
		case 'w':
			iPaintFlag = 7;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		default:
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	return (DefWindowProc(hwnd, imsg, wParam, lParam));
}

/*

RGB(255, 0, 0) RED
RGB(0, 255, 0) Green
RGB(0, 0, 255) blue
RGB(255, 255, 0) yellow
RGB(0, 255, 255) cyan
RGB(255, 0, 255) MAGENTA


Forcefull WM_paint pathvaycha asel tr ,generally 8 cases madhe bhagta ,  Window cha rectangle validate kar 
InvalidateRect(hwnd, NULL (akkha window), TRUE)  

HOMEWORK :
	1 local var declare kar wndproc mdhe:  static int iPaintFlag = -1;

WM_CHAR ikde lihaych cases madhe f F remove karaych
	case 'R':
	case 'r':
		iPaintFlag = 1;
		break;
	case 'G':

		iPaintFlag = 2;

		for b B  = 3;

		y Y la 4

		c C la 5

		m M la 6

		w W la 7

		pratyek flag update nnatr InvalidateRect cha call dyaycha

WM_PAINT :
	SetTextColor chi line badlaych
		if ipaint flag == 1
		rgb madhe red color dyaycha
		else if green
		3 blue 

*/