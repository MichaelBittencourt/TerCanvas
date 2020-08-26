#ifndef GRAPH_H
#define GRAPH_H

#include<list>
#include<map>
#include"canvasIF.h"

class Graph {

    public:

        Graph(CanvasIF & canvas, int width, int height);
        void setPoint(double x, double y);
        void setCanvas(CanvasIF & canvas);
        ~Graph();
        void showGraph();
        void showGraph(int lastIndex);
        void showGraph(int lastIndex, bool ** adjacentMatrix);
        void showLine(int indexP1, int indexP2);
        void showConnectedGraph();
        void showConnectedGraph(int lastIndex);
        void showConnectedGraph(bool ** adjacentMatrix, int sizeMatrix);
        void showConnectedGraph(bool ** adjacentMatrix, int sizeMatrix, int lastIndex);
        bool ** showBestTravelingSalesman();
        bool ** showBestTravelingSalesman(int lastIndex);
        void showBestPathFromTo(int indexP1, int indexP2);
        void showMinimumSpanningTree();
        void showMinimumSpanningTree(int lastIndex);
        void printAdjacentMatrix(bool ** adjacentMatrix, int size);

    private:

        struct Point {
            static double firstX;
            static double firstY;
            static double lastX;
            static double lastY;
            double x;
            double y;
            Point() {
                x = 0;
                y = 0;
            }

            Point(double x, double y) {
                this->x = x;
                this->y = y;
            }

            static double getXCenter() {
                return (lastX - firstX) / 2.0;

            }

            static double getYCenter() {
                return (lastY - firstY) / 2.0;
            }
        };

        CanvasIF & mCanvas;
        int mWidth;
        int mHeight;
        int mQtdPoints;

        std::map<int, Point> mapPoints;

        void calcBestNearLine(bool ** adjacentMatrix, int size, int indexPoint, int returnIndexes[]);

        bool lineInterceptOther(bool ** adjacentMatrix, int size, int indexP1, int indexP2);
        double abs(double value);
        double getDistancePointToLine(int indexPoint, int i, int j);
        void connectPoints(bool ** adjacentMatrix, int indexP1, int indexP2);
        void disconnectPoints(bool ** adjacentMatrix, int indexP1, int indexP2);

        bool ** initAdjacentMatrix(int size);
        void sortWithDistanceToCenter(int vet[], int size);
        double distancePointToCenter(int indexPoint);

        double getDistancePointToPoint(int indexP1, int indexP2);
        double getDistanceGraph(bool ** adjacentMatrix, int size);

};

#endif
