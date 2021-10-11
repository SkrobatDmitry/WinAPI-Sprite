#pragma once
#include <windows.h>

struct Properties
{
	FLOAT x;
	FLOAT y;

	FLOAT width;
	FLOAT height;

	FLOAT rebound;
	FLOAT speed;

	BOOL isImage;
};

class Sprite
{
private:
	HDC winDC;
	HDC memDC;

	HBITMAP hBitmap;
	HBITMAP hPrevBitmap;

	PAINTSTRUCT ps;
	RECT clientRect;
	Properties properties;

	BITMAP bm;
	HDC spriteDC;
	HBITMAP image;

	void DrawRectangle(HWND hWnd);
	void DrawSprite(HWND hWnd);

public:
	Sprite(HWND hWnd, RECT clientRect);
	~Sprite();

	void InitProperties(FLOAT x, FLOAT y, FLOAT width, FLOAT height, FLOAT speed, FLOAT rebound);
	void MakeAMove(BOOL isDiagonal, BOOL isForward);
	void ChangeAState();
	void Draw(HWND hWnd);
};
