#include <windows.h>
#include "resource.h"
#include "sprite.h"

Sprite *sprite;

RECT clientRect;
POINT mouseCoords;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM             MyRegisterClass(HINSTANCE);
BOOL             InitInstance(HINSTANCE, INT);

INT CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
	MSG msg;

	MyRegisterClass(hInstance);
	InitInstance(hInstance, nCmdShow);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	delete sprite;
	return (INT)msg.wParam;
}

LRESULT WINAPI MyWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_PAINT:
		sprite->Draw(hWnd);
		break;
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_UP:
		case 'W':
			sprite->MakeAMove(false, false);
			break;
		case VK_DOWN:
		case 'S':
			sprite->MakeAMove(false, true);
			break;
		case VK_LEFT:
		case 'A':
			sprite->MakeAMove(true, false);
			break;
		case VK_RIGHT:
		case 'D':
			sprite->MakeAMove(true, true);
			break;
		case VK_RETURN:
			sprite->ChangeAState();
			break;
		}

		InvalidateRect(hWnd, NULL, TRUE);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		GetCursorPos(&mouseCoords);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAIN_ICON));
	wcex.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAIN_ICON));
	wcex.hCursor = LoadCursor(NULL, IDC_HAND);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.hInstance = hInstance;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.lpfnWndProc = MyWindowProc;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"WinAPI";

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, INT nCmdShow)
{
	HWND hWnd = CreateWindow(L"WinAPI", L"Sprite", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, 0, 720, 480, NULL, NULL, hInstance, NULL);
	if (!hWnd)
	{
		return FALSE;
	}

	GetWindowRect(hWnd, &clientRect);
	sprite = new Sprite(hWnd, clientRect);
	if (!sprite)
	{
		return FALSE;
	}

	sprite->InitProperties((clientRect.right - clientRect.left - 30.0f) / 2, ((clientRect.bottom - clientRect.top) / 2) - 30.0f, 30.0f, 30.0f, 3.0f, 10.0f);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}
