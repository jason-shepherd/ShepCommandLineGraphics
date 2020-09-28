#include "src/shep.h"

int main() {
	shep::shepInit(8, 8, 100, 100);	
	while(true) {
		shep::draw(5, 5, 0x00C0);
		shep::drawEllipse(70, 10, 20, 10, true, 0x00C0, 0x00A0);
		shep::drawLine(0, 0, 10, 20, 0x00c0);
		shep::drawRect(10, 10, 10, 10, true, 0x00C0, 0x00A0);
		shep::drawCircle(50, 30, 10, true, 0x00C0, 0x00A0);
		shep::updateScreen();
	}
}
