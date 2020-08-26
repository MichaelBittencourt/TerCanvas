#ifndef TER_CANVAS_H
#define TER_CANVAS_H

#include "canvasIF.h"

class Canvas : public CanvasIF {

    private:

        char character;
        int virtualWidth;
        int virtualHeight;
        int realHeight;
        int realWidth;
        bool verbosity;


        void gotoxy(int x,int y);
        void setRealDimenssions();
        int getRealX(int x);
        int getRealY(int y);

    public:
        
        Canvas();
        ~Canvas();
        Canvas(int width, int height, char _character);
        virtual void drawPoint(int x, int y);
        virtual void drawLine(int x1, int y1, int x2, int y2);
        virtual void drawTriagle(int x1, int y1, int x2, int y2, int x3, int y3);
        virtual void drawCircle(int xc, int yc, int R); 
        virtual void clear();
        void setCharacterPoint(char character);
        void enableVerbosity();
        void disebleVerbosity();


};

#endif
