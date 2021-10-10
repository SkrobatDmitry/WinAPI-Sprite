#pragma once
#include <windows.h>

struct Facets
{
	FLOAT top;
	FLOAT bottom;
	FLOAT left;
	FLOAT right;
};

class Sprite
{
	HDC winDC;
	HDC memDC;

	HBITMAP hBitmap;
	HBITMAP hPrevBitmap;

	PAINTSTRUCT ps;
	RECT clientRect;
	Facets facets;

	BITMAP bm;
	HDC spriteDC;
	HBITMAP image;

public:
	Sprite(HWND hWnd, RECT clientRect);
	~Sprite();

	void DrawRectangle(HWND hWnd, FLOAT x, FLOAT y, FLOAT size);
	void DrawSprite(HWND hWnd, FLOAT x, FLOAT y);
};
