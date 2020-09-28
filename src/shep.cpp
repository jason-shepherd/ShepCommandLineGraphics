#include "shep.h"

//ANON NAMESPACE FOR PRIVATE VARS
namespace {
	HANDLE hOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int sWidth, sHeight;
	int cWidth, cHeight;
	CHAR_INFO* screen;
	SMALL_RECT screenRect;

	//PRIVATE FUNCTIONS
	void drawHorizontalLine(int x0, int x1, int y, WORD color) {
		if(x0 < x1) {
			for(int i = x0; i < x1; i++) {
				shep::draw(i, y, color);	
			}
		} else {
			for(int i = x1; i < x0; i++) {
				shep::draw(i, y, color);	
			}
		}
	}

	void drawVerticalLine(int y0, int y1, int x, WORD color) {
		if(y0 < y1) {
			for(int j = y0; j < y1; j++) {
				shep::draw(x, j, color);	
			}
		} else {
			for(int j = y1; j < y0; j++) {
				shep::draw(x, j, color);	
			}
		}
	}	

	void drawLowLine(int x0, int y0, int x1, int y1, WORD color) {
		int y, dx, dy, yi, D = 0;	
		dx = x1 - x0;
		dy = y1 - y0;
		yi = 1;
		if(dy < 0) {
			yi = -1;
			dy = -dy;
		}
		D = 2 * dy - dx;
		y = y0;

		for(int x = x0; x <= x1; x++) {
			shep::draw(x, y, color);
			if(D > 0) {
				y += yi;
				D -= 2 * dx;
			}
			D += 2 * dy;
		}
	}

	void drawHighLine(int x0, int y0, int x1, int y1, WORD color) {
		int x, dx, dy, xi, D = 0;	
		dx = x1 - x0;
		dy = y1 - y0;
		xi = 1;
		if(dy < 0) {
			xi = -1;
			dx = -dx;
		}
		D = 2 * dx - dy;
		x = x0;

		for(int y = y0; y <= y1; y++) {
			shep::draw(x, y, color);
			if(D > 0) {
				x += xi;
				D -= 2 * dy;
			}
			D += 2 * dx;
		}
	}

	void plotEllipse(int x, int y, int xc, int yc, bool fill, WORD color, WORD fillColor) {
		if(fill) {
			for(int i = yc - y; i < yc + y; i++) {
				shep::draw(xc + x, i, fillColor);
				shep::draw(xc - x, i, fillColor);
			}
		}
		
		shep::draw(xc + x, yc + y, color);	
		shep::draw(xc + x, yc - y, color);
		shep::draw(xc - x, yc - y, color);
		shep::draw(xc - x, yc + y, color);	
	}

	void plotCircle(int x, int y, int xc, int yc, bool fill, WORD color, WORD fillColor) {
			
		if(fill) {
			for(int i = xc - y; i < xc + y; i++) {
				shep::draw(i, yc + x, fillColor);
				shep::draw(i, yc - x, fillColor);
			}

			for(int j = yc - y; j < yc + y; j++) {
				shep::draw(xc + x, j, fillColor);
				shep::draw(xc - x, j, fillColor);
			}	
		}
		shep::draw(xc + x, yc + y, color);	
		shep::draw(xc + y, yc + x, color);
		shep::draw(xc + y, yc - x, color);
		shep::draw(xc + x, yc - y, color);
		shep::draw(xc - x, yc - y, color);
		shep::draw(xc - y, yc - x, color);
		shep::draw(xc - y, yc + x, color);
		shep::draw(xc - x, yc + y, color);	
	}	
}
	
//PUBLIC FUNCTIONS
int shep::getScreenWidth() {
	return sWidth;
}

int shep::getScreenHeight() {
	return sHeight;
}

void shep::shepInit(int charWidth, char charHeight, int screenWidth, int screenHeight) {
	//SET PARAMS TO VARS
	cWidth = charWidth;
	cHeight = charHeight;
	sWidth = screenWidth;
	sHeight = screenHeight;

	//MAKE CONSOLE ACT LIKE AN ARRAY OF PIXELS
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	//CHANGE FONT SIZE
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = cWidth;
	cfi.dwFontSize.Y = cHeight;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	SetCurrentConsoleFontEx(hOut, FALSE, &cfi);
		
	//GET CONSOLE SCREEN BUFFER INFO AND PASS IT TO CSBI
	GetConsoleScreenBufferInfo(hOut, &csbi);
	
	//CHANGE WINDOW SIZE
	screenRect = {(short)0, (short)0, (short)sWidth - 1, (short)sHeight - 1};
	SetConsoleWindowInfo(hOut, TRUE, &screenRect);

	//ARRAY OF PIXELS
	screen = new CHAR_INFO[sWidth * sHeight];
	for(int i = 0; i < sWidth * sHeight; i++) {
		screen[i].Char.UnicodeChar = 0x0020;
		screen[i].Attributes = 0x0030;
	} }
	
void shep::updateScreen() {
	WriteConsoleOutput(hOut, screen, { (short)sWidth, (short)sHeight }, { 0, 0 }, &screenRect);
	for(int i = 0; i < sWidth * sHeight; i++) {
		screen[i].Char.UnicodeChar = 0x0020;
		screen[i].Attributes = 0x0030;
	}
}	

void shep::draw(int x, int y, WORD color) {
	x--;
	y--;
	if(x >= 0 && x <= sWidth && y >= 0 && y <= sHeight) {	
		screen[sWidth * y + x].Attributes = color;
	}
}

void shep::drawRect(int x, int y, int width, int height, bool fill, WORD color, WORD fillColor) {
	if(fill) {
		for(int j = 0; j < height; j++) {
			drawHorizontalLine(x - width / 2, x + width / 2, (y + j) - height / 2, fillColor);
		}
	}	

//	drawHorizontalLine(x - width / 2, x + width / 2, y - height / 2, color);
//	drawHorizontalLine(x - width / 2, x + width / 2, y + height / 2, color);
//	drawVerticalLine(y - height / 2, y + height / 2, x - width / 2, color);
//	drawVerticalLine(y - height / 2, y + height / 2, x + width / 2, color);

}

void shep::drawLine(int x0, int y0, int x1, int y1, WORD color) {
	if(abs(y1 - y0) < abs(x1 - x0)) {
		if(x0 > x1) {
			//LOW LINE FROM p1 to p0
			drawLowLine(x1, y1, x0, y0, color);
		} else {
			//LOW LINE FROM p0 to p1
			drawLowLine(x0, y0, x1, y1, color);
		}
	} else {
		if(y0 > y1) {
			//HIGH LINE FROM p1 to p0
			drawHighLine(x1, y1, x0, y0, color);	
		} else {
			//HIGH LINE FROM p0 to p1
			drawHighLine(x0, y0, x1, y1, color);
		}
	}
}

void shep::drawEllipse(int xc, int yc, int rx, int ry, bool fill, WORD color, WORD fillColor) {
	int x = 0, y = ry;
	int p = (ry * ry) - (rx * rx) * ry + ((rx * rx) / 4);

	while(2 * (ry * ry) * x < 2 * (rx * rx) * y) {
		plotEllipse(x, y, xc, yc, fill, color, fillColor);

		if(p < 0) {
			x += 1;
			p = p + 2 * (ry * ry) * x + (ry * ry);
		} else {
			x += 1;
			y -= 1;
			p = p + 2 * (ry * ry) * x - 2 * (rx * rx) * y + (ry * ry);
		}
	}

	p = (ry * ry) * ((x + (1/2)) * (x + (1/2))) + (rx * rx) * ((y - 1) * (y - 1)) - (rx * rx) * (ry * ry);
	
	while(y >= 0) {
		plotEllipse(x, y, xc, yc, fill, color, fillColor);

		if(p > 0) {
			y -= 1;
			p = p - 2 * (rx * rx) * y + (rx * rx);
		} else {
			x += 1;
			y -= 1;
			p = p + 2 * (ry * ry) * x - 2 * (rx * rx) * y + (rx * rx);
		}
	}
}

void shep::drawCircle(int xc, int yc, int r, bool fill, WORD color, WORD fillColor) {
	int x = 0, y = r;
	int p = 1 - r;

	while(x <= y) {
		plotCircle(x, y, xc, yc, fill, color, fillColor);

		if(p <= 0) {
			x += 1;
			p = p + (2 * x + 3);  
		} else {
			x += 1;
			y -= 1;
			p = p + 2 * (x - y) + 5;
		}
	}
}
