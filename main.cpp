#include<stdio.h>
#include<cstdlib>
#include "terCanvas.h"
#include "canvasIF.h"
#include "graph.h"
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

/*
 *#include <iostream>       // std::cout, std::endl
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
 
int main() 
{
  std::cout << "countdown:\n";
  for (int i=10; i>0; --i) {
    std::cout << i << std::endl;
    std::this_thread::sleep_for (std::chrono::seconds(1));
  }
  std::cout << "Lift off!\n";

  return 0;
}
 *
 *
 * */

#ifdef TEST_CANVAS

int main(void) {

    Canvas canvas(70, 100, '*');
    canvas.clear();
    canvas.enableVerbosity();
    canvas.drawCircle(34, 85, 14);
    getchar();
    canvas.drawLine(15, 35, 60, 70);
    getchar();
    canvas.drawLine(18, 45, 60, 70);
    getchar();
    canvas.drawLine(60, 70, 20, 70);
    getchar();
    canvas.setCharacterPoint('+');
    canvas.drawTriagle(20, 70, 40, 10, 50, 60);
    canvas.setCharacterPoint('#');
    canvas.drawPoint(15, 35);
    getchar();
    canvas.drawPoint(18, 45);
    getchar();
    canvas.drawPoint(60, 70);
    getchar();
    canvas.drawPoint(20, 70);
    getchar();
    canvas.drawPoint(40, 10);
    getchar();
    canvas.drawPoint(50, 60);
    getchar();
    canvas.drawPoint(34, 85);
    getchar();


}

#else
    #ifdef TEST_GRAPH


int main(void) {

    int heigth = 500;
    //int heigth = 161;
    int width = 500;
    //int width = 251;
    Canvas canvas(heigth, width, '*');
    Graph graph(canvas, width, heigth);
    graph.setPoint(15, 29);
    graph.setPoint(42, 50);
    graph.setPoint(58, 87);
    graph.setPoint(77, 76);
    canvas.clear();
    graph.showGraph();
    getchar();
    for(int i = 1; i < 250; i += 5) {
        canvas.clear();

        //canvas.enableVerbosity();
        graph.showLine(0, 1);
        //getchar();
        graph.showLine(1, 2);
        //getchar();
        graph.showLine(2, 3);
        //getchar();
        graph.showLine(3, 0);
    
        canvas.setCharacterPoint('@');
        graph.showGraph();

        canvas.setCharacterPoint('+');
        canvas.drawPoint(heigth/2+1, width/2+1);
        //canvas.drawCircle(heigth/2+1, width/2+1, i);
        //canvas.setCharacterPoint('@');
        //graph.showGraph(graph, width, heigth, canvas);
        std::this_thread::sleep_for (std::chrono::milliseconds(100));
        canvas.setCharacterPoint('*');
    }
}

    #else

        #if CANVAS_TEST

int main(void) {

    int heigth = 500;
    //int heigth = 161;
    int width = 500;
    //int width = 251;
    int qtdPoints = 0;

    scanf("%d %d", &heigth, &width);
    scanf("%d", &qtdPoints);
    Canvas canvas(heigth, width, '*');
    Graph graph(canvas, width, heigth);
    for(int i = 0; i < qtdPoints; i++) {
        int x = 0, y = 0;
        scanf("%d %d", &x, &y);
        graph.setPoint(x, y);
    }
    /*
    for(int k = 1; k < 250; k += 5) {
        canvas.setCharacterPoint('*');
        canvas.clear();
        canvas.enableVerbosity();
        graph.showConnectedGraph();
        canvas.setCharacterPoint('@');
        graph.showGraph();

        canvas.setCharacterPoint('+');
        canvas.drawPoint(heigth/2+1, width/2+1);
        canvas.drawCircle(heigth/2+1, width/2+1, k);
        canvas.setCharacterPoint('@');
        graph.showGraph();
        std::this_thread::sleep_for (std::chrono::milliseconds(100));
        //getchar();
    }
    */

    canvas.clear();
    getchar();
    canvas.setCharacterPoint('*');
    bool ** adjacentMatrix = graph.showBestTravelingSalesman();
    canvas.clear();
    graph.showConnectedGraph(adjacentMatrix, qtdPoints);
    canvas.setCharacterPoint('@');
    graph.showGraph();
    getchar();
    canvas.clear();
    graph.printAdjacentMatrix(adjacentMatrix, qtdPoints);

}
        #else

int main(void) {

    int heigth = 500;
    //int heigth = 161;
    int width = 500;
    //int width = 251;
    int qtdPoints = 0;

    scanf("%d %d", &heigth, &width);
    scanf("%d", &qtdPoints);
    Canvas canvas(heigth, width, '*');
    Graph graph(canvas, width, heigth);
    for(int i = 0; i < qtdPoints; i++) {
        int x = 0, y = 0;
        scanf("%d %d", &x, &y);
        graph.setPoint(x, y);
    }
    /*
    for(int k = 1; k < 250; k += 5) {
        canvas.setCharacterPoint('*');
        canvas.clear();
        canvas.enableVerbosity();
        graph.showConnectedGraph();
        canvas.setCharacterPoint('@');
        graph.showGraph();

        canvas.setCharacterPoint('+');
        canvas.drawPoint(heigth/2+1, width/2+1);
        canvas.drawCircle(heigth/2+1, width/2+1, k);
        canvas.setCharacterPoint('@');
        graph.showGraph();
        std::this_thread::sleep_for (std::chrono::milliseconds(100));
        //getchar();
    }
    */

    canvas.clear();
    getchar();
    canvas.setCharacterPoint('*');
    bool ** adjacentMatrix = graph.showBestTravelingSalesman();
    canvas.clear();
    graph.showConnectedGraph(adjacentMatrix, qtdPoints);
    canvas.setCharacterPoint('@');
    graph.showGraph();
    getchar();
    canvas.clear();
    graph.printAdjacentMatrix(adjacentMatrix, qtdPoints);

}

        #endif

    #endif

#endif
