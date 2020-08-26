#include "terCanvas.h"
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <cmath>

Canvas::Canvas() { 
    setRealDimenssions();
    virtualWidth = realWidth;
    virtualHeight = realHeight;
    character = '*';
    verbosity = false;
}

Canvas::~Canvas() { 
    gotoxy(realHeight, realWidth);
}

Canvas::Canvas(int height, int width, char _character) : character(_character), virtualWidth(width), virtualHeight(height), verbosity(false) {
    setRealDimenssions();
}

void Canvas::setRealDimenssions() {
   struct winsize w;
   ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
   realHeight = w.ws_row;
   realWidth = w.ws_col;
}

int Canvas::getRealY(int y) {
    return (int)((realWidth * (double)y / virtualWidth) + 0.5);  
}

int Canvas::getRealX(int x) {
    return (int)((realHeight * (double)x / virtualHeight) + 0.5);  
}

void Canvas::drawPoint(int x, int y) {
    if (verbosity) {
        gotoxy(realHeight, 0);
        printf("                                     ");
        gotoxy(realHeight, 0);
        printf("x = %d   y = %d   ", x, y);
    }
    setRealDimenssions();
    gotoxy(getRealX(x), getRealY(y));
    //gotoxy(x, y);
    printf("%c", character);
    gotoxy(realHeight, 0);
}

void Canvas::drawLine(int x1, int y1, int x2, int y2) {
    
    double coefAng = ((double)(y1 - y2)) / (x1 - x2);
    double coefLinear = y2 - coefAng*x2;
    if (verbosity) {
        gotoxy(realHeight-1, 0);
        printf("                                     ");
        gotoxy(realHeight-1, 0);
        printf("line y = %.2fx + %.2f", coefAng, coefLinear);
    }
    if (x1 != x2) {
        int inicio = x1 <= x2 ? x1 : x2;
        int fim = x1 <= x2 ? x2 : x1;
        for(int i = inicio ; i <= fim ; i++ ) {
            
            drawPoint(i, (int)(coefAng*i + coefLinear + 0.5));
            //getchar();
        }
    } else {

        int inicio = y1 <= y2 ? y1 : y2;
        int fim = y1 <= y2 ? y2 : y1;
        for(int i = inicio ; i <= fim ; i++ ) {
            drawPoint(x1, i);
            //getchar();
        }
    }
}

void Canvas::drawTriagle(int x1, int y1, int x2, int y2, int x3, int y3) {
    drawLine(x1, y1, x2, y2);
    drawLine(x1, y1, x3, y3);
    drawLine(x2, y2, x3, y3);
}

void Canvas::drawCircle(int xc, int yc, int R) {
    if (verbosity) {
        gotoxy(realHeight-1, 0);
        printf("                                     ");
        gotoxy(realHeight-1, 0);
        printf("circle %d^2 = (x - %d)^2 + (y - %d)^2", R, xc, yc);
    }

    for(int i = xc-R; i <= xc+R; i++) {

        double delta = sqrt(R*R - (i -xc)*(i-xc));
        double y1 = yc + delta;
        double y2 = yc - delta;
        drawPoint(i, (int)(y1 + 0.5));
        drawPoint(i, (int)(y2 + 0.5));

    }

}

void Canvas::clear() {

    const char * cls = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    //printf("%s", cls);
    printf("\033[2J");

}

void Canvas::setCharacterPoint(char character) {
    this->character = character;
}

void Canvas::gotoxy(int x,int y) {
    printf("%c[%d;%df",0x1B,x,y);
}

void Canvas::enableVerbosity() {
    verbosity = true;
}

void Canvas::disebleVerbosity() {
    verbosity = false;
}

