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

void Sprite::MakeAMove(CHAR key)
{
	switch (key)
	{
	case 'W':
		properties.y -= properties.speed;
		break;
	case 'S':
		properties.y += properties.speed;
		break;
	case 'A':
		properties.x -= properties.speed;
		break;
	case 'D':
		properties.x += properties.speed;
		break;
	}

	MakeABounce();
}

void Sprite::MakeABounce()
{
	if (properties.y < clientRect.top)
	{
		properties.y = clientRect.top + properties.rebound;
	}
	else if (properties.y + properties.height > clientRect.bottom)
	{
		properties.y = clientRect.bottom - properties.height - properties.rebound;
	}
	else if (properties.x < clientRect.left)
	{
		properties.x = clientRect.left + properties.rebound;
	}
	else if (properties.x + properties.width > clientRect.right)
	{
		properties.x = clientRect.right - properties.width - properties.rebound;
	}
}

void Sprite::SetARect(RECT clientRect)
{
	this->clientRect = clientRect;
}

void Sprite::ChangeAState()
{
	properties.isImage = !properties.isImage;
}

void Sprite::Draw(HWND hWnd)
{
	properties.isImage ? DrawSprite(hWnd) : DrawRectangle(hWnd);
}
