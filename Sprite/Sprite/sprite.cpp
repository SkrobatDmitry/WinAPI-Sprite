#include "sprite.h"

Sprite::Sprite(HWND hWnd, RECT clientRect)
{
	winDC = GetDC(hWnd);
	memDC = CreateCompatibleDC(winDC);

	this->clientRect = clientRect;
	hBitmap = CreateCompatibleBitmap(winDC, clientRect.right, clientRect.bottom);
	hPrevBitmap = (HBITMAP)SelectObject(memDC, hBitmap);

	// image = 
}

Sprite::~Sprite()
{
	DeleteObject((HBITMAP)image);
	DeleteObject(hPrevBitmap);
	DeleteObject(hBitmap);
	DeleteDC(spriteDC);
	DeleteDC(memDC);
	DeleteDC(winDC);
}

void Sprite::DrawRectangle(HWND hWnd, FLOAT x, FLOAT y, FLOAT size)
{
	memDC = BeginPaint(hWnd, &ps);
	SelectObject(memDC, CreateSolidBrush(RGB(18, 188, 156)));
	SelectObject(memDC, CreatePen(PS_SOLID, 3, RGB(54, 92, 112)));
	Rectangle(memDC, (INT)x, (INT)y, (INT)x + (INT)size, (INT)y + (INT)size);
	EndPaint(hWnd, &ps);
}

void Sprite::DrawSprite(HWND hWnd, FLOAT x, FLOAT y)
{
}
