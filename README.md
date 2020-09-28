# Shep
A super simple framework to do some basic command line drawing. Great for basic graphical examples, like Conway's Game of Life.

# The basics
This framework just has the complete basics for creating some graphics on the command line. IT ONLY WORKS ON WINDOWS and likes being compiled with MSVC more than anything else. It has the basic functions to create a command line window, size it, color it, and draw shapes or lines.

# Use
To use the frame work you first include the "shep.h" header. The framework is wrapped in a namespace so every function will require shep:: in front of it. To start you need to run the init function.  
```shep::shepInit(widthOfCells, heightOfCells, screenWidth, screenHeight);```  
The command line is seperated into "cells". The first 2 arguments are the width and height of the cells and the last 2 are how many columns and rows of cells there are. Next you can draw. Most of the time you will be drawing shapes in a while/game loop.  
```shep::draw(x, y, color);```  
The colors are hex with black being 0x0000 and white being 0x00F0 with other colors in between. I forgot what colors there are, so you can have some fun playing with it. :). Lastly you need to update the screen with  
```shep::updateScreen();```  
See main.cpp for an example!

# Have fun
I built this to mess around with graphics and I hope someone will use it to do the same thing. Have fun!
