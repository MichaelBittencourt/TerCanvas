#include"graph.h"
#include<list>
#include<cmath>

double Graph::Point::firstX = 10000000;
double Graph::Point::firstY = 10000000;
double Graph::Point::lastX = -10000000;
double Graph::Point::lastY = -10000000;

Graph::Graph(CanvasIF & canvas, int width, int heigth) : 
    mCanvas(canvas), 
    mWidth(width), 
    mHeight(heigth) { }

void Graph::setPoint(double x, double y) {
    Point p(x, y);
    mapPoints[mapPoints.size()] = p;
    if ( x < Point::firstX )
        Point::firstX = x;
    if ( x > Point::lastX )
        Point::lastX = x;
    if ( y < Point::firstY )
        Point::firstY = y;
    if ( y > Point::lastY )
        Point::lastY = y;
    //listPoint.push_back(p);
}

void Graph::showGraph() {
    showGraph(mapPoints.size()-1);
    /*for (std::map<int, Point>::iterator it=mapPoints.begin(); it!=mapPoints.end(); ++it) {
        mCanvas.drawPoint(-it->second.y + mHeight-mHeight/4, it->second.x+mWidth/4);
    }
    */
}

void Graph::showGraph(int lastIndex, bool ** adjacentMatrix) {
    if ( adjacentMatrix != nullptr ) {

        for(int i = 0; i <= lastIndex; i++) {
            for(int j = i + 1; j <= lastIndex; j++) {
                if (adjacentMatrix[i][j]) {
                    showLine(i, j);
                }
            }
        }

    }
    for(int i = 0; i <= lastIndex && i < mapPoints.size(); i++) {
        mCanvas.drawPoint(-mapPoints[i].y + mHeight-mHeight/4, mapPoints[i].x+mWidth/4);
    }
}

void Graph::showGraph(int lastIndex) {
    showGraph(lastIndex, nullptr);
}

void Graph::showConnectedGraph() {
    showConnectedGraph(mapPoints.size() - 1);
}

void Graph::showConnectedGraph(int lastIndex) {
    for(int i = 0; i <= lastIndex && i < mapPoints.size(); i++) {
        showLine(i%(lastIndex+1), (i+1)%(lastIndex+1));
        //getchar();
    }
}

void Graph::showConnectedGraph(bool ** adjacentMatrix, int sizeMatrix) {
   showConnectedGraph(adjacentMatrix, sizeMatrix, mapPoints.size()-1);
}

void Graph::showConnectedGraph(bool ** adjacentMatrix, int sizeMatrix, int lastIndex) {
    for(int i = 0; i <= lastIndex && i < sizeMatrix; i++) {
        for(int j = i + 1; j < lastIndex && j < sizeMatrix; j++) {
            if(adjacentMatrix[i][j]) {
                showLine(i, j);
            }
        }
    }
}

void Graph::showLine(int indexP1, int indexP2) {
    Point & p1 = mapPoints[indexP1];
    Point & p2 = mapPoints[indexP2];
    mCanvas.drawLine(-p1.y+mHeight-mHeight/4, p1.x+mWidth/4, -p2.y+mHeight-mHeight/4, p2.x+mWidth/4);
}

bool ** Graph::showBestTravelingSalesman() {
    return showBestTravelingSalesman(mapPoints.size() - 1);
}

bool ** Graph::showBestTravelingSalesman(int lastIndex) {

    int vetIndex[lastIndex+1];
    for(int i = 0; i <= lastIndex; i++) {
        vetIndex[i] = i;
    }
    sortWithDistanceToCenter(vetIndex, lastIndex+1);
    bool ** adjacentMatrix = initAdjacentMatrix(lastIndex+1);
    if ( lastIndex >= 2 ) {
        connectPoints(adjacentMatrix, vetIndex[0], vetIndex[1]);
        connectPoints(adjacentMatrix, vetIndex[0], vetIndex[2]);
        connectPoints(adjacentMatrix, vetIndex[1], vetIndex[2]);
#ifdef DEBUG
        mCanvas.clear();
        showGraph(lastIndex, adjacentMatrix);
        getchar();
#endif
        for ( int i = 3; i <= lastIndex; i++ ) {
            int vetIndexPointsInLine[2];
            calcBestNearLine(adjacentMatrix, lastIndex+1, vetIndex[i], vetIndexPointsInLine);
            //printAdjacentMatrix(adjacentMatrix, lastIndex+1);
            disconnectPoints(adjacentMatrix, vetIndexPointsInLine[0], vetIndexPointsInLine[1]);
            connectPoints(adjacentMatrix, vetIndex[i], vetIndexPointsInLine[0]);
            connectPoints(adjacentMatrix, vetIndex[i], vetIndexPointsInLine[1]);
#ifdef DEBUG
            mCanvas.clear();
            showGraph(lastIndex, adjacentMatrix);
            getchar();
#endif
        }
    } else if ( lastIndex == 1 ) {
        connectPoints(adjacentMatrix, 0, 1);
    } else {
        showGraph(0);
    }

    //mCanvas.clear();
    showGraph(lastIndex, adjacentMatrix);
    getchar();
    return adjacentMatrix;
}

/*Intera em toda a matrix de adjacencia. Quando estiver com os pontos conectatos eu pego esses indices e calculo a distancia do indice do ponto à reta e pego os indices da reta mais próxima.
 */
#ifndef ANTIGO
void Graph::calcBestNearLine(bool ** adjacentMatrix, int size, int indexPoint, int returnIndexes[]) {
    double minDistancetoToLine = 100000000;
    for(int i = 0; i < size; i++) {
        for(int j = i + 1; j < size; j++) {
            if(adjacentMatrix[i][j]) {
                double temp = getDistancePointToLine(indexPoint, i, j);
#ifdef DEBUG
    mCanvas.clear();
    printf("Point %d, dividePoints = (%d, %d)\n", indexPoint, returnIndexes[0], returnIndexes[1]);
    printf("temp %lf, minDistance = %lf\n", temp, minDistancetoToLine);
    getchar();
#endif
                if (temp < minDistancetoToLine) {
                    minDistancetoToLine = temp;
                    returnIndexes[0] = i;
                    returnIndexes[1] = j;
                }
            }
        }
    }
#ifdef DEBUG
    mCanvas.clear();
    printf("Point %d, dividePoints = (%d, %d)\n", indexPoint, returnIndexes[0], returnIndexes[1]);
    printAdjacentMatrix(adjacentMatrix, size);
    getchar();
#endif
}

#else

void Graph::calcBestNearLine(bool ** adjacentMatrix, int size, int indexPoint, int returnIndexes[]) {
    double minDistancetoToLine = 100000000;
    double graphDistance = getDistanceGraph(adjacentMatrix, size);
    for(int i = 0; i < size; i++) {
        for(int j = i + 1; j < size; j++) {
            if(adjacentMatrix[i][j]) {
                double temp = graphDistance;
                temp -= getDistancePointToPoint(i, j);
                temp += getDistancePointToPoint(i, indexPoint);
                temp += getDistancePointToPoint(indexPoint, j);

#ifdef DEBUG
    //mCanvas.clear();
    printf("Point %d, dividePoints = (%d, %d)\n", indexPoint, returnIndexes[0], returnIndexes[1]);
    printf("temp %lf, minDistance = %lf\n", temp, minDistancetoToLine);
    getchar();
#endif
                if (temp < minDistancetoToLine && !lineInterceptOther(adjacentMatrix, size, indexPoint, i) && !lineInterceptOther(adjacentMatrix, size, indexPoint, j)) {
                    minDistancetoToLine = temp;
                    returnIndexes[0] = i;
                    returnIndexes[1] = j;
                }
            }
        }
    }
#ifdef DEBUG
    mCanvas.clear();
    printf("Point %d, dividePoints = (%d, %d)\n", indexPoint, returnIndexes[0], returnIndexes[1]);
    printAdjacentMatrix(adjacentMatrix, size);
    getchar();
#endif
}

#endif

bool Graph::lineInterceptOther(bool ** adjacentMatrix, int size, int indexP1, int indexP2) { 
    return false;
}

double Graph::getDistanceGraph(bool ** adjacentMatrix, int size) {
    double distancePath = 0;
    for(int i = 0; i < size; i++) {
        for(int j = i + 1; j < size; j++) {
            if(adjacentMatrix[i][j]) {
                distancePath += getDistancePointToPoint(i, j);
            }
        }
    }
}

double Graph::getDistancePointToPoint(int indexP1, int indexP2) {
    return sqrt(pow(mapPoints[indexP1].x-mapPoints[indexP2].x, 2) + pow(mapPoints[indexP1].y -mapPoints[indexP1].y, 2));
}

double Graph::abs(double value) {
    return value < 0 ? -value : value;
}

double Graph::getDistancePointToLine(int indexPoint, int i, int j) {
    double x0 = mapPoints[indexPoint].x;
    double y0 = mapPoints[indexPoint].y;
    double x1 = mapPoints[i].x;
    double y1 = mapPoints[i].y;
    double x2 = mapPoints[j].x;
    double y2 = mapPoints[j].y;
    double xc = (x1+x2)/2;
    double yc = (y1+y2)/2;
    return sqrt(pow((x0-xc), 2) + pow(y0-yc, 2));
}

/*
double Graph::getDistancePointToLine(int indexPoint, int i, int j) {
    double x0 = mapPoints[indexPoint].x;
    double y0 = mapPoints[indexPoint].y;
    double x1 = mapPoints[i].x;
    double y1 = mapPoints[i].y;
    double x2 = mapPoints[j].x;
    double y2 = mapPoints[j].y;
    double coefAng = (y2 - y1) / (x2 - x1);
    double coefLinear = y2 - coefAng*x2;
    double coefAngCenter = (Point::getYCenter() - y0) / (Point::getXCenter() - x0);
    double coefLinearCenter = y0 - coefAngCenter*x0;

    if (coefAng == coefAngCenter)
        return 1000000;
    double xIntercept = (coefLinearCenter - coefLinear) / (coefAng - coefAngCenter);
 #ifdef DEBUG
    printf("\nx0 = %lf\n\
    y0 = %lf\n\
    x1 = %lf\n\
    y1 = %lf\n\
    x2 = %lf\n\
    y2 = %lf\n\
    coefAng = %lf\n\
    coefLinear = %lf\n\
    coefAngCenter = %lf\n\
    coefLinearCenter = %lf\n\
    xIntercept = %lf\n\
    xCenter = %lf\n\
    yCenter = %lf\n\
    ", x0, y0, x1, y1, x2, y2, coefAng, coefLinear, coefAngCenter, coefLinearCenter, xIntercept, Point::getXCenter(), Point::getYCenter());
    getchar();
#endif
    if (x1 < x2) {
        if (xIntercept < x1 || xIntercept > x2){
            return 2000000;
        }
    } else {
        if (xIntercept < x2 || xIntercept > x1) {
            return 3000000;
        }
    }

    double yIntercept = coefAng*xIntercept + coefLinear;

    if (y1 < y2) {
        if (yIntercept < y1 || yIntercept > y2){
            return 4000000;
        }
    } else {
        if (yIntercept < y2 || yIntercept > y1) {
            return 5000000;
        }
    }
    return sqrt(pow(xIntercept-x0, 2) + pow(yIntercept-y0, 2));

    //y = ax + b
    //y = coefAng*x + coefLinear
    //coefAng*x -y + coefLinear = 0
    //d = |ax0 + by0 + c| / sqrt(a^2 + b^2)

    //Não está funcionando porque a reta é a reta infinita. Nesse caso não dá pra usar sempre a equação pois a distancia mínima pode ser um valor passe do seguimento de reta, invalidando a operação.
    //Dica: Tentan checar se o valor está no inferior da reta. se estiver usa a conta se não estiver então faz uma busca binária no interior da reta.
    //Dica: Se o valor estiver no intervalo fora, então a menor distancia
    //é a menor distancia até um dos dois pontos.
//    return sqrt(pow(mapPoints[indexPoint].x-126, 2) + pow(mapPoints[indexPoint].y -81, 2));

    /*
    double distP1 = sqrt(pow(x1-x0, 2) + pow(y1-y0, 2));
    double distP2 = sqrt(pow(x2-x0, 2) + pow(y2-y0, 2));
    double distP1ForaDaReta;
    double distP2ForaDaReta;

    if (x1 < x2) {
        distP1ForaDaReta = sqrt(pow(x1-1-x0, 2) + pow(coefAng*(x1-1)+coefLinear-y0, 2));
        distP2ForaDaReta = sqrt(pow(x2+1-x0, 2) + pow(coefAng*(x2+1)+coefLinear-y0, 2));
    } else { if ( x1 > x2 ) {
        distP1ForaDaReta = sqrt(pow(x2-1-x0, 2) + pow(coefAng*(x2-1)+coefLinear-y0, 2));
        distP2ForaDaReta = sqrt(pow(x1+1-x0, 2) + pow(coefAng*(x1+1)+coefLinear-y0, 2));
    } else {
        if ( y1 > y2 ) {
            distP1ForaDaReta = sqrt(pow(x1-x0, 2) + pow(y1+1-y0, 2));
            distP2ForaDaReta = sqrt(pow(x2-x0, 2) + pow(y2-1-y0, 2));
        } else {
            distP1ForaDaReta = sqrt(pow(x1-x0, 2) + pow(y1-1-y0, 2));
            distP2ForaDaReta = sqrt(pow(x2-x0, 2) + pow(y2+1-y0, 2));
        }
    }
    }
    if (distP1ForaDaReta < distP1 || distP2ForaDaReta < distP2) {
        return distP1 < distP2 ? distP1 : distP2;
    } {
        if ( x1 != x2 )
            return (abs(coefAng*x0 -y0 + coefLinear) / sqrt(pow(coefAng, 2) + 1));
        else
            return 10000000; //if x1 ==  x2 calc using the inverse function
    }
    */
//}


void Graph::connectPoints(bool ** adjacentMatrix, int indexP1, int indexP2) {
    adjacentMatrix[indexP1][indexP2] = true;
    adjacentMatrix[indexP2][indexP1] = true;
}

void Graph::disconnectPoints(bool ** adjacentMatrix, int indexP1, int indexP2) {
    adjacentMatrix[indexP1][indexP2] = false;
    adjacentMatrix[indexP2][indexP1] = false;
}

bool ** Graph::initAdjacentMatrix(int size) {
    bool ** adjacentMatrix = new bool*[size];
    for( int i = 0; i < size; i++ ) {
        adjacentMatrix[i] = new bool[size];
        for ( int j = 0; j < size; j++ ) {
            adjacentMatrix[i][j] = false;
        }
    }
    return adjacentMatrix;
}


void Graph::printAdjacentMatrix(bool ** adjacentMatrix, int size) {

    printf("   ");
    for(int i = 0; i < size; i++) {
        if ( i < 10 )
            printf("| %d ", i);
        else
            printf("|%d ", i);
    }
    printf("|\n");
    for(int i = 0; i < size; i++) {
        if (i < 10)
            printf("%d  | ", i);
        else
            printf("%d | ", i);
        for(int j = 0; j < size; j++) {
            if (j > i)
                printf("%d | ", adjacentMatrix[i][j]);
            else
                printf("# | ");

        }
        printf("\n");
    }
}

void Graph::sortWithDistanceToCenter(int vet[], int size) {
    for(int i = 0; i < size; i++) {
        double min=100000000;
        int minIndex=0;
        for(int j = i; j < size; j++) {
           double temp = distancePointToCenter(vet[j]);
           if (temp < min) {
               min = temp;
               minIndex = j;
           }
        }
        int tempIndex = vet[i];
        vet[i] = vet[minIndex];
        vet[minIndex] = tempIndex;
#ifdef DEBUG
        printf("vet[%d] = %d\n", i, vet[i]);
        getchar();
#endif
    }
}


double Graph::distancePointToCenter(int indexPoint) {

    //mCanvas.drawPoint(-mapPoints[i].y + mHeight-mHeight/4, mapPoints[i].x+mWidth/4);
    return sqrt(pow(mapPoints[indexPoint].x-Point::getXCenter(), 2) + pow(mapPoints[indexPoint].y -Point::getYCenter(), 2));

}


void Graph::showBestPathFromTo(int indexP1, int indexP2) { }
void Graph::showMinimumSpanningTree() { }
void Graph::showMinimumSpanningTree(int lastIndex) { }

Graph::~Graph() { }
