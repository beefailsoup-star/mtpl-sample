interface PriorityQueueItem<T> {
  value: T
  priority: number
}

class PriorityQueue<T> {
  private items: PriorityQueueItem<T>[] = []

  enqueue(value: T, priority: number): void {
    this.items.push({ value, priority })
    this.bubbleUp(this.items.length - 1)
  }

  dequeue(): T | undefined {
    if (this.isEmpty()) return undefined
    const top = this.items[0]
    const bottom = this.items.pop()
    if (this.items.length > 0 && bottom) {
      this.items[0] = bottom
      this.sinkDown(0)
    }
    return top.value
  }

  peek(): T | undefined {
    return this.items[0]?.value
  }

  isEmpty(): boolean {
    return this.items.length === 0
  }

  size(): number {
    return this.items.length
  }

  private bubbleUp(index: number): void {
    while (index > 0) {
      const parent = Math.floor((index - 1) / 2)
      if (this.items[index].priority >= this.items[parent].priority) break
      this.swap(index, parent)
      index = parent
    }
  }

  private sinkDown(index: number): void {
    const length = this.items.length
    while (true) {
      let smallest = index
      const left = 2 * index + 1
      const right = 2 * index + 2
      if (left < length && this.items[left].priority < this.items[smallest].priority) smallest = left
      if (right < length && this.items[right].priority < this.items[smallest].priority) smallest = right
      if (smallest === index) break
      this.swap(index, smallest)
      index = smallest
    }
  }

  private swap(i: number, j: number): void {
    [this.items[i], this.items[j]] = [this.items[j], this.items[i]]
  }

  toArray(): T[] {
    return [...this.items].sort((a, b) => a.priority - b.priority).map(i => i.value)
  }
}

export { PriorityQueue, type PriorityQueueItem }
