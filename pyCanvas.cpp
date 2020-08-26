#include "pycanvas.h"

void PyCanvas::setRealDimenssions();
int PyCanvas::getRealX(int x);
int PyCanvas::getRealY(int y);

PyCanvas::PyCanvas();
PyCanvas::~PyCanvas();
PyCanvas::PyCanvas(int width, int height, char _character);
void PyCanvas::drawPoint(int x, int y);
void PyCanvas::drawLine(int x1, int y1, int x2, int y2);
void PyCanvas::drawTriagle(int x1, int y1, int x2, int y2, int x3, int y3);
void PyCanvas::drawCircle(int xc, int yc, int R);
void PyCanvas::clear();
void PyCanvas::enableVerbosity();
void PyCanvas::disebleVerbosity();
