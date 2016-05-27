#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <commctrl.h>
#include <objidl.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <gdiplus.h>
#include <stdlib.h>
#include "stdafx.h" 
#include <ctime>
#define N 9
//function forward declarations 

int nr = 0;

HINSTANCE hInst;
bool butonverificare = false;
bool solveit = false;

HWND   idcbuton1;
HWND	idcbuton2;
HWND Sudoku[9][9];
int mat[9][9];

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

void verificare()
{
	nr = 0;
	CHAR sir[20];
	int x;
	for (int i = 0; i < 9; i++)
	for (int j = 0; j < 9; j++)
	{
		GetWindowText(Sudoku[i][j], sir, 20);
		x = atoi(sir);
		if (x == 0)
			mat[i][j] = 51; 
		else mat[i][j] = x;
	}

	//int nr = 0;

	for (int i = 0; i < 9; i++)
	for (int j = 0; j < 9; j++)                                                  //daca numerele depasesc intervalul 1-9
	{
		if (mat[i][j]>9 && mat[i][j] != 51)
		{
			MessageBox(NULL, "All the numbers have to be between 1 and 9. Check again!", "Error",
				MB_ICONEXCLAMATION | MB_OK);
			nr = 1;
		}
	}

	char buffer[4];
	char buf[80];
	               // pe coloane

	for (int k = 0; k < 9; k++)
	{
		for (int i = 0; i < 8; i++)
		for (int j = i + 1; j < 9; j++)
		if (mat[k][i] == mat[k][j] && mat[k][i] != 51)
		{
			{
				strcpy_s(buf, "Try better! The following one is wrong: ");
				_itoa_s(mat[k][j], buffer, 10);
				strcat_s(buf, buffer);
				MessageBox(NULL, buf, "Error",
					MB_ICONEXCLAMATION | MB_OK);
				nr++;
			}
		}
		if (nr != 0)
			break;
	}

	if (nr == 0)       //pe linii
	{
		nr = 0;
		for (int k = 0; k < 9; k++)
		{
			for (int i = 0; i < 8; i++)
			for (int j = i + 1; j < 9; j++)
			if (mat[i][k] == mat[j][k] && mat[i][k] != 51)
			{
				{
					strcpy_s(buf, "Try better! The following one is wrong: ");
					_itoa_s(mat[i][k], buffer, 10);
					strcat_s(buf, buffer);
					MessageBox(NULL, buf, "Error!",
						MB_ICONEXCLAMATION | MB_OK);
					nr++;
				}
			}
			if (nr != 0)
				break;
		}
	}

	int i, j, l, h,c, k;

	if (nr == 0)
		{
		for (int s = 0; s < 9; s = s + 3)
		{
			for (l = s; l < s+2; l++) //aici
			for (c = 0; c < 2; c++)
			{
				for (h = l + 1; h <= s+3; h++)
				for (k = c + 1; k <= 3; k++)
				if (mat[l][c] == mat[h][k] && mat[l][c] != 51)
				{ 
					strcpy_s(buf, "Try better! The following one is wrong: ");
					_itoa_s(mat[l][c], buffer, 10);
					strcat_s(buf, buffer);
					MessageBox(NULL, buf, "Error!",
						MB_ICONEXCLAMATION | MB_OK);
					nr++; 
				}

				if (nr != 0)
					break;
			}
		}
	}

	if (nr == 0)
	{
		for (int s = 0; s < 9; s = s + 3)
		{
			for (l = s; l < s + 2; l++) //aici
			for (c = 3; c < 5; c++)
			{
				for (h = l + 1; h <= s + 3; h++)
				for (k = c + 1; k <= 5; k++)
				if (mat[l][c] == mat[h][k] && mat[l][c] != 51)
				{
					strcpy_s(buf, "Try better! The following one is wrong: ");
					_itoa_s(mat[l][c], buffer, 10);
					strcat_s(buf, buffer);
					MessageBox(NULL, buf, "Error!",
						MB_ICONEXCLAMATION | MB_OK);
					nr++;
				}

				if (nr != 0)
					break;
			}
		}  
	}

	if (nr == 0)
	{
		for (int s = 0; s < 9; s = s + 3)
		{
			for (l = s; l < s + 2; l++) //aici
			for (c = 6; c < 9; c++)
			{
				for (h = l + 1; h <= s + 3; h++)
				for (k = c + 1; k <= 9; k++)
				if (mat[l][c] == mat[h][k] && mat[l][c] != 51)
				{
					strcpy_s(buf, "Try better! The following one is wrong: ");
					_itoa_s(mat[l][c], buffer, 10);
					strcat_s(buf, buffer);
					MessageBox(NULL, buf, "Error!",
						MB_ICONEXCLAMATION | MB_OK);
					nr++;
					if (nr != 0)
						break;
				}
			}
		}

	}

	bool complet = true;                           //daca este toata tabla Sudoku completata
	for (int i = 0; i < 9;i++)
	for (int j = 0; j < 9; j++)
	{
		if (mat[i][j] == 51)
			complet = false;
	}

	if (nr==0 && complet==true)                    //daca nu are greseli si este toata completata
		MessageBox(NULL, "You have finished the game! Good job !", "You WON!",
		MB_ICONEXCLAMATION | MB_OK);

}

int free(int sudoku[][9], int lin, int col, int num)
{
	int i, j;
	for (i = 0; i<9; ++i)
	if ((sudoku[lin][i] == num) || (sudoku[i][col] == num))            //verificare in linie si in coloana
		return 0;

	//patrat
	int linStart = (lin / 3) * 3;
	int colStart = (col / 3) * 3;

	for (i = linStart; i<(linStart + 3); ++i)
	{ 
		for (j = colStart; j<(colStart + 3); ++j)
		{
			if (sudoku[i][j] == num)
				return 0;
		}
	}

	return 1;
}

int completare(HWND hwnd,int sudoku[][9], int lin, int col) 
{
	int i;
	char x[20];

	if (lin<9 && col<9)
	{
		if (sudoku[lin][col] != 0)                          //daca este deja ceva in matrice 
		{
			if ((col + 1)<9)
				return completare(hwnd,sudoku, lin, col + 1);             //daca trec pe linia urmatoare
			else if ((lin + 1)<9)
				return completare(hwnd,sudoku, lin + 1, 0);
			else
				return 1; 
		}

		else
		{
			for (i = 0; i < 9; ++i)
			{
				if (free(sudoku, lin, col, i + 1))
				{
					{
						sudoku[lin][col] = i + 1;
						_itoa_s(mat[lin][col], x, 10);
						SetWindowText(Sudoku[lin][col], LPSTR(x));
						UpdateWindow(hwnd);
						Sleep(0.7);
					}

					if ((col + 1) < 9)
					{
						if (completare(hwnd, sudoku, lin, col + 1))
							return 1;
						
						else
						{
							sudoku[lin][col] = 0;
							_itoa_s(mat[lin][col], x, 10);
							SetWindowText(Sudoku[lin][col], LPSTR(x));
							UpdateWindow(hwnd);
							Sleep(0.7);
						}
					}

					else if ((lin + 1) < 9)
					{
						if (completare(hwnd, sudoku, lin + 1, 0))
							return 1;
						
						else
						{
							sudoku[lin][col] = 0;
							_itoa_s(mat[lin][col], x, 10);
							SetWindowText(Sudoku[lin][col], LPSTR(x));
							UpdateWindow(hwnd);
							Sleep(0.7);
						}
					}

					else
					{               
						return 1;
					}
				}
			}
		}
		return 0;
	}

	else
	{
		return 1;
	}

}


void completare_matrice(HWND hwnd)
{
	CHAR sir[20];
	int x;
	for (int i = 0; i < 9; i++)
	for (int j = 0; j < 9; j++)
	{
		GetWindowText(Sudoku[i][j], sir, 20);              //pun in matrice valorile din "Sudoku" introduse de catre utilizator
		x = atoi(sir);
		mat[i][j] = x;
	}
	completare(hwnd,mat, 0, 0); 
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	char x[20];
	int r;
	//time_t tTime = time(NULL);

	switch (msg)

	{
	case WM_COMMAND:                                      // in caz ca apesi din meniu o anumita cifra
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// SLECTIILE MENIULUI
		switch (wmId)
		{
		case (40005):                                    // NEW GAME
		{
			 for (int i = 0; i < 9; i++)
			 for (int j = 0; j < 9; j++)
			 {
				 mat[i][j] = 0;
				 SetWindowText(Sudoku[i][j], LPSTR(NULL));
				 UpdateWindow(hwnd);
			 }

			 /////////////////////////////////////////////////////////////////////////////////////////////////////////////
			 for (int i = 0; i < 9;i++)
			 for (int j = 0; j < 9; j++)
			 {
				 if (i == 0 && j == 0) //cheked
				 {
					 srand(unsigned(time(NULL)));             //numere de inceput random
					 r = rand() % 5 + 1;
					 _itoa_s(r, x, 10);
					 SetWindowText(Sudoku[i][j], LPSTR(x));
					 UpdateWindow(hwnd);
				 }
				 else if (i == 2 && j == 7) //checked
				 {
					 r = rand() % 5 + 1;
					 _itoa_s(r, x, 10);
					 SetWindowText(Sudoku[i][j], LPSTR(x));
					 UpdateWindow(hwnd);
				 }
				 else if (i == 1 && j == 8) //checked
				 {
					 SetWindowText(Sudoku[i][j], LPSTR("8"));
					 UpdateWindow(hwnd);
				 }
				 else if (i == 4 && j == 4) //checked
				 {
					 SetWindowText(Sudoku[i][j], LPSTR("9"));
					 UpdateWindow(hwnd);
				 }
				 else if (i == 4 && j == 5) //checked
				 {
					 SetWindowText(Sudoku[i][j], LPSTR("7"));
					 UpdateWindow(hwnd);
				 }
				 else if (i == 5 && j == 6) //checked
				 {
					 SetWindowText(Sudoku[i][j], LPSTR("7"));
					 UpdateWindow(hwnd);
				 }
				 else if (i == 2 && j == 2) //checked
				 {
					 r = rand() % 10;
					 _itoa_s(r, x, 10); 
					 SetWindowText(Sudoku[i][j], LPSTR("6"));
					 UpdateWindow(hwnd);

				 }
			 
				 else if (i == 3 && j == 8) //checked
				 {
					 _itoa_s(r, x, 10);
					 SetWindowText(Sudoku[i][j], LPSTR("9"));
					 UpdateWindow(hwnd);
				 }
				 else if (i == 6 && j == 2) //checked
				 {
					 r = rand() % 5 + 1;
					 _itoa_s(r, x, 10);
					 SetWindowText(Sudoku[i][j], LPSTR(x));
					 UpdateWindow(hwnd);
				 }
				 else if (i == 6 && j == 3) //checked
				 {
					 r = rand() % 10;
					 _itoa_s(r, x, 10);
					 SetWindowText(Sudoku[i][j], LPSTR("8"));
					 UpdateWindow(hwnd);
				 }
				 else if (i == 8 && j == 8) //checked
				 {
					 r = rand() % 5 + 1;
					 _itoa_s(r, x, 10);
					 SetWindowText(Sudoku[i][j], LPSTR(x));
					 UpdateWindow(hwnd);
				 }
			 }

			 nr = 0;
			 solveit = false;
			 butonverificare = false;
		}
	    break;

		case (40016) :  //DIALOG BOX
			DialogBox(hInst, MAKEINTRESOURCE(104), hwnd, About);
			break;

		case (40006) :
			DestroyWindow(hwnd);
			break;

		case BN_CLICKED:
		{
			{
				if ((HWND)lParam == idcbuton1)
				{
					if (butonverificare==false)
					verificare();
					if (butonverificare == true)                 //daca a fost completata prin algoritm si nu de catre jucator
					{
						LPCTSTR Caption = "Solved";
						MessageBox(NULL, "Try to complete the game by yourself -> NEW GAME",
						Caption, MB_OK | MB_ICONINFORMATION);
					}

				}

				if ((HWND)lParam == idcbuton2)
				{
					if (solveit==false)
					verificare();
					if (nr == 0)					
					{
						solveit = true;
						completare_matrice(hwnd);
						butonverificare = true;
					}

					else 
					{
						nr = 0;
						LPCTSTR Caption = "WAIT!";
						MessageBox(NULL, "Try to verify the errors and then click SOLVE IT",
							       Caption, MB_OK | MB_ICONINFORMATION);

					}
				}
			}
		}
		break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
		} 
		break;

	case WM_CREATE:
	{
					  for (int i = 0; i < 9;i++)
					  for (int j = 0; j < 9; j++)
					  {
						  if (i == 0 && j == 0) //cheked
						  {
							  srand(unsigned(time(NULL)));             //numere de inceput random
							  r = rand()%5+1;
							  _itoa_s(r, x, 10);
							  Sudoku[i][j] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("STATIC"), x, WS_CHILD | WS_VISIBLE | ES_CENTER | ES_NUMBER,
								  50 + i * 40, 50 + j * 40, 30, 30, hwnd, NULL, NULL, NULL);
						  }
						  else if (i == 2 && j == 7) //checked
						  {
							  r = rand() % 5+1;
							  _itoa_s(r, x, 10);
							  Sudoku[i][j] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("STATIC"), x, WS_CHILD | WS_VISIBLE | ES_CENTER | ES_NUMBER,
								  50 + i * 40, 50 + j * 40, 30, 30, hwnd, NULL, NULL, NULL);
						  }
						  else if (i == 1 && j == 8) //checked
						  {
							  _itoa_s(r, x, 10);
							  Sudoku[j][i] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("STATIC"), "8", WS_CHILD | WS_VISIBLE | ES_CENTER | ES_NUMBER,
								  50 + i * 40, 50 + j * 40, 30, 30, hwnd, NULL, NULL, NULL); 
						  }
						  else if (i == 4 && j == 4) //checked
						  {
							  Sudoku[i][j] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("STATIC"), "9", WS_CHILD | WS_VISIBLE | ES_CENTER | ES_NUMBER,
								  50 + i * 40, 50 + j * 40, 30, 30, hwnd, NULL, NULL, NULL);
						  }
						  else if (i == 4 && j == 5) //checked
						  {
							  Sudoku[i][j] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("STATIC"), "7", WS_CHILD | WS_VISIBLE | ES_CENTER | ES_NUMBER,
								  50 + i * 40, 50 + j * 40, 30, 30, hwnd, NULL, NULL, NULL);
						  }
						  else if (i == 5 && j == 6) //checked
						  {
							  Sudoku[i][j] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("STATIC"), "7", WS_CHILD | WS_VISIBLE | ES_CENTER | ES_NUMBER,
								  50 + i * 40, 50 + j * 40, 30, 30, hwnd, NULL, NULL, NULL);
						  }
						  else if (i == 2 && j == 2) //checked
						  {
							  r = rand() % 10;
							  _itoa_s(r, x, 10); Sudoku[i][j] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("STATIC"), "6", WS_CHILD | WS_VISIBLE | ES_CENTER | ES_NUMBER,
								  50 + i * 40, 50 + j * 40, 30, 30, hwnd, NULL, NULL, NULL);
						  }
						  else if (i == 3 && j == 8) //checked
						  {
							  _itoa_s(r, x, 10); Sudoku[i][j] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("STATIC"), "9", WS_CHILD | WS_VISIBLE | ES_CENTER | ES_NUMBER,
								  50 + i * 40, 50 + j * 40, 30, 30, hwnd, NULL, NULL, NULL);
						  }
						  else if (i == 6 && j == 2) //checked
						  {
							  r = rand() % 5+1;
							  _itoa_s(r, x, 10);
							  Sudoku[i][j] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("STATIC"), x, WS_CHILD | WS_VISIBLE | ES_CENTER | ES_NUMBER,
								  50 + i * 40, 50 + j * 40, 30, 30, hwnd, NULL, NULL, NULL);
						  }
						  else if (i == 6 && j == 3) //checked
						  {
							  r = rand() % 10;
							  _itoa_s(r, x, 10);
							  Sudoku[i][j] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("STATIC"), "8", WS_CHILD | WS_VISIBLE | ES_CENTER | ES_NUMBER,
								  50 + i * 40, 50 + j * 40, 30, 30, hwnd, NULL, NULL, NULL);
						  }
						  else if (i == 8 && j == 8) //checked
						  {
							  r = rand() % 5+1;
							  _itoa_s(r, x, 10);
							  Sudoku[i][j] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("STATIC"), x, WS_CHILD | WS_VISIBLE | ES_CENTER | ES_NUMBER,
								  50 + i * 40, 50 + j * 40, 30, 30, hwnd, NULL, NULL, NULL);
						  }

						  else 
						  Sudoku[i][j] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(""), WS_CHILD | WS_VISIBLE | ES_CENTER | ES_NUMBER,
							  50 + i * 40, 50 + j * 40, 30, 30, hwnd, NULL, NULL, NULL);
					  }
					  idcbuton1 = CreateWindowEx(NULL, "BUTTON", "Verify! ", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
						430, 150, 150, 30, hwnd, (HMENU)NULL, GetModuleHandle(NULL), NULL);					 
					  idcbuton2 = CreateWindowEx(NULL, "BUTTON", "Solve it!", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
						  430, 265, 150, 30, hwnd, (HMENU)NULL, GetModuleHandle(NULL), NULL);
	} 
	break; 

	case WM_PAINT:
	{
					 HDC hdc = BeginPaint(hwnd, &ps);

					 HPEN hPenOld;
					 HPEN hLinePen;
					 COLORREF qLineColor;
					 qLineColor = RGB(64, 0, 64);
					 hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
					 hPenOld = (HPEN)SelectObject(hdc, hLinePen);

					 PAINTSTRUCT ps;

					 MoveToEx(hdc, 165, 50, NULL);
					 LineTo(hdc, 165, 400);

					 MoveToEx(hdc, 285, 50, NULL);
					 LineTo(hdc, 285, 400);

					 MoveToEx(hdc, 50, 165, NULL);
					 LineTo(hdc, 400, 165);
				
					 MoveToEx(hdc, 50, 285, NULL);
					 LineTo(hdc, 400, 285);


					 EndPaint(hwnd, &ps);
	}
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
		CW_USEDEFAULT, 0, 630, 550,
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
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)  
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}



