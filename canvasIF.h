#ifndef TER_CANVAS_IF_H
#define TER_CANVAS_IF_H

class CanvasIF {

    public:

        virtual void drawPoint(int x, int y) = 0;
        virtual void drawLine(int x1, int y1, int x2, int y2) = 0;
        virtual void drawTriagle(int x1, int y1, int x2, int y2, int x3, int y3) = 0;
        virtual void drawCircle(int xc, int yc, int R) = 0;
        virtual void clear() = 0;

};

#endif
