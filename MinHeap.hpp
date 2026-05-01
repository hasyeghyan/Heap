#ifndef MINHEAP_HPP
#define MINHEAP_HPP

#include <iostream>
#include <vector>

template<typename T>
class MinHeap {
    private:
        std::vector<T> heap;
    public: 
        MinHeap() = default;
        MinHeap(const MinHeap& other) : heap{other.heap} {}
        MinHeap(MinHeap&& other) noexcept : heap{std::move(other.heap)} {}
        ~MinHeap() = default;
        
        MinHeap& operator=(const MinHeap& other);
        MinHeap& operator=(MinHeap&& other) noexcept;
        
        void heapify_up(size_t i);
        void heapify_down(std::vector<int>& vec, size_t i, size_t n);

        void insert(T val);
        void pop();
        T& top() { if (!heap.empty()) return heap.front(); }

        void buildHeap(std::vector<T>& vec);
        void heapSort(std::vector<T>& vec);
}; 

template <typename T>
MinHeap<T>& MinHeap<T>::operator=(const MinHeap& other) {
    if (this != &other) {
        heap = other.heap;
    }
    return *this;
}

template <typename T>
MinHeap<T>& MinHeap<T>::operator=(MinHeap&& other) noexcept {
    if (this != &other) {
        heap = std::move(other.heap);
    }
    return *this;
}

template <typename T>
void MinHeap<T>::heapify_up(size_t i) {
    while (i > 0) { 
        int p = (i - 1) / 2;

        if (heap[i] < heap[p]) std::swap(heap[i], heap[p]);
        else break;

        i = p;
    }
}

template <typename T>
void MinHeap<T>::heapify_down(std::vector<int>& vec, size_t i, size_t n) {    
    int lc = 2 * i + 1;
    int rc = 2 * i + 2;
    int min = i;

    if (lc < n && heap[lc] < heap[min]) min = lc;
    if (rc < n && heap[rc] < heap[min]) min = rc;

    if(min == i) return;

    std::swap(heap[min], heap[i]);
    heapify_down(heap, min, n);
}

template <typename T>
void MinHeap<T>::insert(T val) {
    heap.push_back(val);
    heapify_up(heap.size() - 1);
}

template <typename T>
void MinHeap<T>::pop() {
    std::swap(heap[0], heap[heap.size() - 1]);
    heap.pop_back();
    heapify_down(heap, 0, heap.size());
}

template <typename T>
void MinHeap<T>::buildHeap(std::vector<T>& vec) {   
    for (int i = (vec.size() / 2) - 1; i >= 0; --i) {
        heapify_down(vec, i, vec.size());
    }
    heap = vec;
}

template <typename T>
void MinHeap<T>::heapSort(std::vector<T>& vec) {
    buildHeap(vec);
    for (int i = vec.size() - 1; i > 0; --i) {
        std::swap(vec[0], vec[i]);
        heapify_down(vec, 0, i);
    }
}

#endif