#ifndef HEAP_H
#define HEAP_H

#include "Game.h"
#include <vector>
using namespace std;

class Heap {
private:
  vector<weightedGame> data;

  void heapUp(int i);
  void heapDown(int i);

public:
  void insert(const weightedGame& dataPoint);
  weightedGame extractMax();
  bool isEmpty() const;
};


#endif //HEAP_H
