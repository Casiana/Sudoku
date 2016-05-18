#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <commctrl.h>
#include <objidl.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <gdiplus.h>
#include<stdlib.h>
#include "stdafx.h" 
//function forward declarations

HINSTANCE hInst;
const char g_szClassName[] = "myWindowClass"; 
 
ATOM RegisterGridClass(HINSTANCE);
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK GridProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK DlgProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK DlgProc(HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		switch (wParam)
		{
		case IDOK:
			EndDialog(hWndDlg, 0);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (msg)

	{

	case WM_COMMAND:                                      // in caz ca apesi din meniu o anumita cifra
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// SLECTIILE MENIULUI
		switch (wmId)
		{

		case (40016) :  //DIALOG BOX
			DialogBox(hInst, MAKEINTRESOURCE(104), hwnd, About);
			break;


			break;

		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
		break;

	case WM_CREATE:
	{}

		break;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;   //WndClsEx
	HWND hwnd;       //hWnd
	MSG Msg;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;  //WndProcedure
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	wc.hIcon = static_cast<HICON>(LoadImage(hInstance,
		MAKEINTRESOURCE(105),
		IMAGE_ICON,
		32,
		32,
		LR_DEFAULTSIZE));

	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = MAKEINTRESOURCE(106);
	wc.lpszClassName = g_szClassName;
	wc.hInstance = hInstance;

	wc.hIconSm = static_cast<HICON>(LoadImage(hInstance,
		MAKEINTRESOURCE(105),
		IMAGE_ICON,
		16,
		16,
		LR_DEFAULTSIZE));

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	static char szAppName[] = "ExoBrush";

	CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,
		szAppName, "Pattern Brushes",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, 500, 240,
		NULL, NULL, hInstance, NULL);


	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"SUDOKU",
		WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);


	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}


	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	///////////////////////////////////////////////////////////////////
	UNREFERENCED_PARAMETER(hPrevInstance);
	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(108));

	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return Msg.wParam;
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
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)   //si aici le folosesc la fel
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}



// keBlank=>IsFree 