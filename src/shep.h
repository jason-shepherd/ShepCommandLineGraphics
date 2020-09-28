#include <windows.h>
#include <iostream>
#include <cstdlib>

namespace shep {
	//PUBLIC FUNCTIONS
	int getScreenWidth();
	int getScreenHeight();
	void shepInit(int charWidth, char charHeight, int screenWidth, int screenHeight);
	void updateScreen();
	void draw(int x, int y, WORD color);
	void drawRect(int x, int y, int width, int height, bool fill, WORD color, WORD fillColor);
	void drawLine(int x0, int y0, int x1, int y1, WORD color);
	void drawEllipse(int xc, int yc, int rx, int ry, bool fill, WORD color, WORD fillColor);
	void drawCircle(int xc, int yc, int r, bool fill, WORD color, WORD fillColor);
}
