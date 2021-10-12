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
			sprite->MakeAMove('W');
			break;
		case VK_DOWN:
		case 'S':
			sprite->MakeAMove('S');
			break;
		case VK_LEFT:
		case 'A':
			sprite->MakeAMove('A');
			break;
		case VK_RIGHT:
		case 'D':
			sprite->MakeAMove('D');
			break;
		case VK_RETURN:
			sprite->ChangeAState();
			break;
		}

		InvalidateRect(hWnd, NULL, TRUE);
		break;
	}
	case WM_MOUSEWHEEL:
	{
		if (LOWORD(wParam) == MK_SHIFT)
		{
			GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? sprite->MakeAMove('D') : sprite->MakeAMove('A');
		}
		else
		{
			GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? sprite->MakeAMove('S') : sprite->MakeAMove('W');
		}
	}
	case WM_SIZE:
	{
		GetClientRect(hWnd, &clientRect);

		sprite->SetARect(clientRect);
		sprite->MakeABounce();
		
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

	GetClientRect(hWnd, &clientRect);
	sprite = new Sprite(hWnd, clientRect);
	if (!sprite)
	{
		return FALSE;
	}

	sprite->InitProperties((clientRect.right - clientRect.left - 30.0f) / 2, (clientRect.bottom - clientRect.top - 30.0f) / 2, 30.0f, 30.0f, 3.0f, 10.0f);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}
