class MinHeap {
  constructor() {
    this.heap = [];
  }

  getParentIndex(index) {
    return Math.floor((index - 1) / 2);
  }

  getLeftChildIndex(index) {
    return 2 * index + 1;
  }

  getRightChildIndex(index) {
    return 2 * index + 2;
  }

  swap(i, j) {
    [this.heap[i], this.heap[j]] = [this.heap[j], this.heap[i]];
  }

  insert(value) {
    this.heap.push(value);
    this.bubbleUp(this.heap.length - 1);
    return this;
  }

  bubbleUp(index) {
    while (index > 0) {
      const parent = this.getParentIndex(index);
      if (this.heap[parent] <= this.heap[index]) break;
      this.swap(parent, index);
      index = parent;
    }
  }

  extractMin() {
    if (this.heap.length === 0) return undefined;
    if (this.heap.length === 1) return this.heap.pop();
    const min = this.heap[0];
    this.heap[0] = this.heap.pop();
    this.bubbleDown(0);
    return min;
  }

  bubbleDown(index) {
    const length = this.heap.length;
    while (true) {
      let smallest = index;
      const left = this.getLeftChildIndex(index);
      const right = this.getRightChildIndex(index);
      if (left < length && this.heap[left] < this.heap[smallest]) smallest = left;
      if (right < length && this.heap[right] < this.heap[smallest]) smallest = right;
      if (smallest === index) break;
      this.swap(index, smallest);
      index = smallest;
    }
  }

  peek() {
    return this.heap.length > 0 ? this.heap[0] : undefined;
  }

  size() {
    return this.heap.length;
  }
}

class MaxHeap extends MinHeap {
  bubbleUp(index) {
    while (index > 0) {
      const parent = this.getParentIndex(index);
      if (this.heap[parent] >= this.heap[index]) break;
      this.swap(parent, index);
      index = parent;
    }
  }

  bubbleDown(index) {
    const length = this.heap.length;
    while (true) {
      let largest = index;
      const left = this.getLeftChildIndex(index);
      const right = this.getRightChildIndex(index);
      if (left < length && this.heap[left] > this.heap[largest]) largest = left;
      if (right < length && this.heap[right] > this.heap[largest]) largest = right;
      if (largest === index) break;
      this.swap(index, largest);
      index = largest;
    }
  }

  extractMax() {
    return this.extractMin();
  }
}

module.exports = { MinHeap, MaxHeap };
