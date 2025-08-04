#include "Heap.h"
#include <stdexcept>

void Heap::heapUp(int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (data[parent] < data[i]) {
            swap(data[i], data[parent]);
            i = parent;
        } else {
            break;
        }
    }
}

void Heap::heapDown(int i) {
    int size = data.size();
    while (true) {
        int left = (2*i)+1;
        int right = (2*i)+2;
        int biggest = i;

        if (left < size && data[biggest] < data[left]) {
            biggest = left;
        }
        if (right < size && data[biggest] < data[right]) {
            biggest = right;
        }

        if (biggest != i) {
            swap(data[i], data[biggest]);
            i = biggest;
        } else {
            break;
        }
    }
}

void Heap::insert(const weightedGame& dataPoint) {
    data.push_back(dataPoint);
    heapUp(data.size() - 1);
}

weightedGame Heap::getMax() {
    if (isEmpty()) {
        throw std::runtime_error("Heap is empty");
    }

    weightedGame max = data[0];
    data[0] = data.back();
    data.pop_back();
    if (!isEmpty()) heapDown(0);
    return max;
}

bool Heap::isEmpty() const {
    return data.empty();
}
