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

void Sprite::DrawRectangle(HWND hWnd)
{
	memDC = BeginPaint(hWnd, &ps);
	SelectObject(memDC, CreateSolidBrush(RGB(18, 188, 156)));
	SelectObject(memDC, CreatePen(PS_SOLID, 3, RGB(54, 92, 112)));
	Rectangle(memDC, (INT)properties.x, (INT)properties.y, (INT)properties.x + (INT)properties.width, (INT)properties.y + (INT)properties.height);
	EndPaint(hWnd, &ps);
}

void Sprite::DrawSprite(HWND hWnd)
{
}

void Sprite::InitProperties(FLOAT x, FLOAT y, FLOAT width, FLOAT height, FLOAT speed, FLOAT rebound)
{
	properties.x = x;
	properties.y = y;
	properties.width = width;
	properties.height = height;
	properties.speed = speed;
	properties.rebound = rebound;
	properties.isImage = false;
}

void Sprite::MakeAMove(BOOL isDiagonal, BOOL isForward)
{
	if (isDiagonal)
	{
		isForward ? properties.x += properties.speed : properties.x -= properties.speed;
	}
	else
	{
		isForward ? properties.y += properties.speed : properties.y -= properties.speed;
	}
}

void Sprite::ChangeAState()
{
	properties.isImage = !properties.isImage;
}

void Sprite::Draw(HWND hWnd)
{
	properties.isImage ? DrawSprite(hWnd) : DrawRectangle(hWnd);
}
