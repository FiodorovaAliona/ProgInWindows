#include "stdafx.h"
#include <windows.h>
#include <math.h>
#include "PWlab5.h"

#define MAX_LOADSTRING 100
#define PI 3.141592653589
#define IDC_PW5
#define IDS_APP_TITLE 1000
#define MAKEINTRESOURCE 1000
HINSTANCE hInst;
TCHAR szTitle[MAX_LOADSTRING];
TCHAR szWindowClass[MAX_LOADSTRING];

ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

int cxClient, cyClient;
static POINT temp[4];

struct CustomPoint {
	double x;
	double y;
}Square[4];

void Move(int x, int y) {
	for (int i = 0; i<4; i++) {
		Square[i].x += x;
		Square[i].y += y;
	}
}

void RotateClockwise(static POINT center) {
	double x, y;
	for (int i = 0; i<4; i++) {
		x = (double)(Square[i].x - center.x)*cosf(PI / 90) - (Square[i].y - center.y)*sinf(PI / 90) + center.x;
		y = (double)(Square[i].x - center.x)*sinf(PI / 90) + (Square[i].y - center.y)*cosf(PI / 90) + center.y;
		Square[i].x = x;
		Square[i].y = y;
	}
}

void RotateCounterClockwise(static POINT center) {
	double x, y;
	for (int i = 0; i<4; i++) {
		x = (double)(Square[i].x - center.x)*cosf(-PI / 90) - (Square[i].y - center.y)*sinf(-PI / 90) + center.x;
		y = (double)(Square[i].x - center.x)*sinf(-PI / 90) + (Square[i].y - center.y)*cosf(-PI / 90) + center.y;
		Square[i].x = x;
		Square[i].y = y;
	}
}

void MouseMoveXY(int x, int y) {
	Square[0].x = x - 100;
	Square[0].y = y - 100;
	Square[1].x = x + 100;
	Square[1].y = y - 100;
	Square[2].x = x + 100;
	Square[2].y = y + 100;
	Square[3].x = x - 100;
	Square[3].y = y + 100;
}

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	MSG msg;
	HACCEL hAccelTable;
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_PW5, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	if (!InitInstance(hInstance, nCmdShow)) return FALSE;

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PW5));
	while (GetMessage(&msg, NULL, 0, 0)) {
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance) {
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_PW5));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOWFRAME);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
	HWND hWnd;

	hInst = hInstance;

	hWnd = CreateWindow(szWindowClass, L"Лабараторная работа №5.2", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd) return FALSE;


	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;
	static POINT center;
	static int cxClient, cyClient;
	static int X, Y;
	switch (message) {
	case WM_SIZE:
		cxClient = GET_X_LPARAM(lParam);
		cyClient = GET_Y_LPARAM(lParam);
		X = cxClient / 2;
		Y = cyClient / 2;
		Square[0].x = X - 100;
		Square[0].y = Y - 100;
		Square[1].x = X + 100;
		Square[1].y = Y - 100;
		Square[2].x = X + 100;
		Square[2].y = Y + 100;
		Square[3].x = X - 100;
		Square[3].y = Y + 100;
		break;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_LEFT:
			if (X > 145) { Move(-5, 0); X -= 5; }
			break;
		case VK_RIGHT:
			if (X<cxClient - 145) { Move(5, 0); X += 5; }
			break;
		case VK_UP:
			if (Y>145) { Move(0, -5); Y -= 5; }
			break;
		case VK_DOWN:
			if (Y < cyClient - 145) { Move(0, 5); Y += 5; }
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 128)));
		for (int i = 0; i < 4; i++) {
			temp[i].x = (int)Square[i].x;
			temp[i].y = (int)Square[i].y;
		}
		Polygon(hdc, temp, 4);

		EndPaint(hWnd, &ps);
		break;

	case WM_CHAR:
		if (wParam == 'd') {
			center.x = X;
			center.y = Y;
			InvalidateRect(hWnd, NULL, TRUE);
			RotateClockwise(center);
		}
		if (wParam == 'a') {
			center.x = X;
			center.y = Y;
			InvalidateRect(hWnd, NULL, TRUE);
			RotateCounterClockwise(center);
		}
		return 0;
		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
		if ((GET_X_LPARAM(lParam)>X - 100 && GET_X_LPARAM(lParam)<X + 100) &&
			(GET_Y_LPARAM(lParam)>Y - 100 && GET_Y_LPARAM(lParam)<Y + 100) &&
			(GET_X_LPARAM(lParam) >= 100 && GET_X_LPARAM(lParam)<cxClient - 100) &&
			(GET_Y_LPARAM(lParam) >= 100 && GET_Y_LPARAM(lParam)<cyClient - 100)) {
			SetCursor(LoadCursorFromFile(L"grab.cur"));
		}
		int cy, cx;
		hdc = GetDC(hWnd);
		if ((GET_X_LPARAM(lParam)>X - 100 && GET_X_LPARAM(lParam)<X + 100) &&
			(GET_Y_LPARAM(lParam)>Y - 100 && GET_Y_LPARAM(lParam)<Y + 100) &&
			(GET_X_LPARAM(lParam) >= 100 && GET_X_LPARAM(lParam)<cxClient - 100) &&
			(GET_Y_LPARAM(lParam) >= 100 && GET_Y_LPARAM(lParam)<cyClient - 100))
			if (wParam & MK_LBUTTON) {
				cx = GET_X_LPARAM(lParam);
				cy = GET_Y_LPARAM(lParam);
				SelectObject(hdc, GetStockObject(WHITE_PEN));
				SetCursor(LoadCursorFromFile(L"grabCL.cur"));
				X = cx;
				Y = cy;
				MouseMoveXY(X, Y);
				SelectObject(hdc, GetStockObject(BLACK_PEN));
				for (int i = 0; i < 4; i++) {
					temp[i].x = (int)Square[i].x;
					temp[i].y = (int)Square[i].y;
				}
				Polygon(hdc, temp, 4);
				InvalidateRect(hWnd, NULL, TRUE);
			}
		ReleaseDC(hWnd, hdc);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
