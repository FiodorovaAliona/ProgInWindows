

#include "stdafx.h"
#include "Bezier1.h"

#include <windows.h>
#include <math.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void MyBezier(HDC hdc, POINT *tab, int nr);
void SimpleBez(HDC hdc, POINT p1, POINT p2, POINT p3, POINT p4);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	static char szAppName[] = "Bezier";
	HWND        hwnd;
	MSG         msg;
	WNDCLASSEX  wndclass;
	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wndclass);
	hwnd = CreateWindow(szAppName,         // window class name
		"Bezier Program",     // window caption
		WS_OVERLAPPEDWINDOW,     // window style
		CW_USEDEFAULT,           // initial x position
		CW_USEDEFAULT,           // initial y position
		CW_USEDEFAULT,           // initial x size
		CW_USEDEFAULT,           // initial y size
		NULL,                    // parent window handle
		NULL,                    // window menu handle
		hInstance,               // program instance handle
		NULL);	     // creation parameters
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}


void Bezier(HDC hdc, POINT apt[]) {
	MoveToEx(hdc, apt[0].x, apt[0].y, NULL);
	LineTo(hdc, apt[1].x, apt[1].y);
	MoveToEx(hdc, apt[2].x, apt[2].y, NULL);
	LineTo(hdc, apt[3].x, apt[3].y);
	SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(255, 0, 0)));
	PolyBezier(hdc, apt, 4);
}
double X(double t, int a, int b, int c, int d) {
	double ans = (1 - t)*(1 - t)*(1 - t)*a + 3 * (1 - t)*(1 - t)*t*b + 3 * (1 - t)*t*t*c + t*t*t*d;
	return ans;
}
double Y(double t, int a, int b, int c, int d) {
	double ans = (1 - t)*(1 - t)*(1 - t)*a + 3 * (1 - t)*(1 - t)*t*b + 3 * (1 - t)*t*t*c + t*t*t*d;
	return ans;
}
void BezierFormula(HDC hdc, POINT apt[]) {
	static POINT point2[1000];
	for (int i = 0; i < 1000; i++) {
		point2[i].x = X((i / 1000.0), apt[0].x, apt[1].x, apt[2].x, apt[3].x);
		point2[i].y = Y((i / 1000.0), apt[0].y, apt[1].y, apt[2].y, apt[3].y);
	}
	SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(0, 0, 0)));
	Polyline(hdc, point2, 1000);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;
	static POINT point1[7];
	int count = 4;


	switch (message) {
	case WM_LBUTTONDOWN:
		hdc = GetDC(hWnd);
		if (clicks == 0) {
			point1[0].x = GET_X_LPARAM(lParam);
			point1[0].y = GET_Y_LPARAM(lParam);
		}
		if (clicks == 1) {
			point1[1].x = GET_X_LPARAM(lParam);
			point1[1].y = GET_Y_LPARAM(lParam);
		}
		if (clicks == 2) {
			point1[2].x = GET_X_LPARAM(lParam);
			point1[2].y = GET_Y_LPARAM(lParam);
		}
		if (clicks == 3) {
			point1[3].x = GET_X_LPARAM(lParam);
			point1[3].y = GET_Y_LPARAM(lParam);
			BezierFormula(hdc, point1);
			Bezier(hdc, point1);
		}
		clicks++;
		ReleaseDC(hWnd, hdc);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		if (clicks > 3) {
			BezierFormula(hdc, point1);
			Bezier(hdc, point1);
		}


		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

