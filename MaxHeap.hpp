#ifndef MAXHEAP_HPP
#define MAXHEAP_HPP

#include <iostream>
#include <vector>

template<typename T>
class MaxHeap {
    private:
        std::vector<T> heap;
    public: 
        MaxHeap() = default;
        MaxHeap(const MaxHeap& other) : heap{other.heap} {}
        MaxHeap(MaxHeap&& other) noexcept : heap{std::move(other.heap)} {}
        ~MaxHeap() = default;

        std::vector<T>& getHeap() { return heap; }
        
        MaxHeap& operator=(const MaxHeap& other);
        MaxHeap& operator=(MaxHeap&& other) noexcept;

        void heapify_up(size_t i);
        void heapify_down(std::vector<int>& vec, size_t i, size_t n);

        void insert(T val);
        void pop();
        T& top() { if (!heap.empty()) return heap.front(); }
        
        void buildHeap(std::vector<T>& vec);
        void heapSort(std::vector<T>& vec);
}; 

template <typename T>
MaxHeap<T>& MaxHeap<T>::operator=(const MaxHeap& other) {
    if (this != &other) {
        heap = other.heap;
    }
    return *this;
}

template <typename T>
MaxHeap<T>& MaxHeap<T>::operator=(MaxHeap&& other) noexcept {
    if (this != &other) {
        heap = std::move(other.heap);
    }
    return *this;
}

template <typename T>
void MaxHeap<T>::heapify_up(size_t i) {
    while (i > 0) { 
        int p = (i - 1) / 2;

        if (heap[i] > heap[p]) std::swap(heap[i], heap[p]);
        else break;

        i = p;
    }
}

template <typename T>
void MaxHeap<T>::heapify_down(std::vector<int>& vec, size_t i, size_t n) {    
    int lc = 2 * i + 1;
    int rc = 2 * i + 2;
    int max = i;

    if (lc < n && heap[lc] > heap[max]) max = lc;
    if (rc < n && heap[rc] > heap[max]) max = rc;

    if(max == i) return;

    std::swap(heap[max], heap[i]);
    heapify_down(heap, max, n);
}

template <typename T>
void MaxHeap<T>::insert(T val) {
    heap.push_back(val);
    heapify_up(heap.size() - 1);
}

template <typename T>
void MaxHeap<T>::pop() {
    std::swap(heap[0], heap[heap.size() - 1]);
    heap.pop_back();
    heapify_down(heap, 0, heap.size());
}

template <typename T>
void MaxHeap<T>::buildHeap(std::vector<T>& vec) {   
    for (int i = (vec.size() / 2) - 1; i >= 0; --i) {
        heapify_down(vec, i, vec.size());
    }
    heap = vec;
}

template <typename T>
void MaxHeap<T>::heapSort(std::vector<T>& vec) {
    buildHeap(vec);
    for (int i = vec.size() - 1; i > 0; --i) {
        std::swap(vec[0], vec[i]);
        heapify_down(vec, 0, i);
    }
}

std::vector<int>& HeapSort(std::vector<int>& vec) {
    MaxHeap<int> maxheap;
    maxheap.buildHeap(vec);
    std::vector<int>& v = maxheap.getHeap();  

    for (int i = vec.size() - 1; i > 0; --i) {
        std::swap(v[0], v[i]);
        maxheap.heapify_down(v, 0, i);   
    }  
    
    vec = maxheap.getHeap();
    return vec;
}


#endif