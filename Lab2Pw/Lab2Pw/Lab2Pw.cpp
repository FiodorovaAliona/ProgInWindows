// lab2PW.cpp: ���������� ����� ����� ��� ����������.
//

#include "stdafx.h"
#include "lab2PW.h"

#define MAX_LOADSTRING 100

// ���������� ����������:
HINSTANCE hInst;                                // ������� ���������
WCHAR szTitle[MAX_LOADSTRING];                  // ����� ������ ���������
WCHAR szWindowClass[MAX_LOADSTRING];            // ��� ������ �������� ����

												// ��������� ���������� �������, ���������� � ���� ������ ����:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: ���������� ��� �����.

	// ������������� ���������� �����
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_LAB2PW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ��������� ������������� ����������:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB2PW));

	MSG msg;

	// ���� ��������� ���������:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  �������: MyRegisterClass()
//
//  ����������: ������������ ����� ����.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB2PW));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB2PW);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   �������: InitInstance(HINSTANCE, int)
//
//   ����������: ��������� ��������� ���������� � ������� ������� ����.
//
//   �����������:
//
//        � ������ ������� ���������� ���������� ����������� � ���������� ����������, � �����
//        ��������� � ��������� �� ����� ������� ���� ���������.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // ��������� ���������� ���������� � ���������� ����������
	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 500, 500, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  �������: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����������:  ������������ ��������� � ������� ����.
//
//  WM_COMMAND � ���������� ���� ����������
//  WM_PAINT � ���������� ������� ����
//  WM_DESTROY � ��������� ��������� � ������ � ���������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HBITMAP shar;
	HDC hdc, pompom;
	HPEN MyPen;
	HFONT hfont;
	RECT rect;
	POINT pt;

	static int x1 = 30, x2 = 10, x3 = 50, x4 = 400, x5 = 300;
	int y1 = 30, y2 = 50, y3 = 60, y4 = 200, y5 = 220;

	int static xMax, yMax;
	int static y = 600;
	
	HGDIOBJ hBrush;
	HGDIOBJ hPen,hPen1;
	switch (message)
	{

	case WM_CREATE:
	{
		SetTimer(hWnd, 1, 100, nullptr);
	}
	case WM_TIMER:

		InvalidateRect(hWnd, nullptr, true);
		
		x1 += 2;
		x2 += 2;
		x3 += 2;
		x4 += 2;
		x5 += 2;

		//x1 = 30, x2 = 10, x3 = 50, x4 = 400, x5 = 300;
		if (x5 > xMax && xMax != 0) { x5 = 0; x4 = 100; }
		if (x2 > xMax && xMax!=0) { x2 = 0; x1 = 20; x3 = 40; }

		if (y<0 ) {
			y = yMax;
		}
		
		else {
			
			
			y -= 5;
			
		}
		return 0;

	case WM_SIZE:
		xMax = LOWORD(lParam);
		yMax = HIWORD(lParam);
		return 0;
	case WM_PAINT:
	{
		hBrush = CreateSolidBrush(RGB(0, 50, 255));
		hdc = BeginPaint(hWnd, &ps);
		pompom = CreateCompatibleDC(hdc);
		GetClientRect(hWnd, &rect);
	
		SelectObject(hdc, GetStockObject(NULL_PEN));
		SelectObject(hdc, hBrush);
		Rectangle(hdc, 0, 0, xMax, yMax / 2);
		
		SelectObject(hdc, hBrush);
		Rectangle(hdc, 0, yMax / 2 - 50, xMax, yMax);
		
		shar = (HBITMAP)LoadImage(hInst, "C:\\Shar.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		SelectObject(pompom, shar);
		BitBlt(hdc, xMax / 2 - 100, y, 227, 300, pompom, 0, 0, SRCCOPY);
		hPen1 = CreatePen(PS_SOLID, 2, BLACK_PEN);
		SelectObject(hdc, hPen1);


		POINT r[5];
		r[0].x = 5; r[0].y = 5;
		r[1].x = 100; r[1].y = 5;
		r[2].x = 100; r[2].y =25;
		r[3].x =5; r[3].y = 25;
		r[4].x = 5; r[4].y = 5;
		Polyline(hdc, r, 5);
		SetBkColor(hdc, RGB(0, 0, 255));
		TextOut(hdc, 6, 6, "Fiodorova A.", 12);
		hBrush = GetStockObject(WHITE_BRUSH);
		SelectObject(hdc, hBrush);
		hPen = GetStockObject(WHITE_PEN);
		SelectObject(hdc, hPen);
		
		Ellipse(hdc, x1, y1, x1 + 120, y1 + 20);
		Ellipse(hdc, x2, y2, x2 + 240, y2 + 10);
		Ellipse(hdc, x3, y3, x3 + 150, y3 + 10);
		
		Ellipse(hdc, x4, y4, x4 + 200, y4 + 30);
		Ellipse(hdc, x5, y5, x5 + 200, y5 + 30);
		
		

		EndPaint(hWnd, &ps);
		return 0;
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

