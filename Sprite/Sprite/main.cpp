#include <windows.h>
#include "resource.h"
#include "sprite.h"

Sprite *sprite;
Facets *facets;

RECT clientRect;

FLOAT x = 0;
FLOAT y = 0;
FLOAT size = 30;

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
	{
		sprite->DrawRectangle(hWnd, x, y, size);
	}
	break;
	case VK_RETURN:
	{

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

	x = (clientRect.right - clientRect.left - size) / 2;
	y = ((clientRect.bottom - clientRect.top) / 2) - size;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}
