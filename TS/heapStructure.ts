export abstract class Heap<T> {
  protected data: T[] = []
  protected abstract compare(a: T, b: T): boolean

  get size(): number {
    return this.data.length
  }

  peek(): T | undefined {
    return this.data[0]
  }

  push(value: T): void {
    this.data.push(value)
    this.bubbleUp(this.data.length - 1)
  }

  pop(): T | undefined {
    if (this.data.length === 0) return undefined
    const top = this.data[0]
    const last = this.data.pop()!
    if (this.data.length > 0) {
      this.data[0] = last
      this.sinkDown(0)
    }
    return top
  }

  private bubbleUp(index: number): void {
    while (index > 0) {
      const parent = (index - 1) >> 1
      if (this.compare(this.data[index], this.data[parent])) {
        [this.data[index], this.data[parent]] = [this.data[parent], this.data[index]]
        index = parent
      } else break
    }
  }

  private sinkDown(index: number): void {
    const len = this.data.length
    while (true) {
      let smallest = index
      const left = (index << 1) + 1
      const right = left + 1
      if (left < len && this.compare(this.data[left], this.data[smallest])) smallest = left
      if (right < len && this.compare(this.data[right], this.data[smallest])) smallest = right
      if (smallest === index) break
      [this.data[index], this.data[smallest]] = [this.data[smallest], this.data[index]]
      index = smallest
    }
  }

  toArray(): T[] {
    return [...this.data]
  }
}

export class MinHeap<T> extends Heap<T> {
  protected compare(a: T, b: T): boolean {
    return a < b
  }
}

export class MaxHeap<T> extends Heap<T> {
  protected compare(a: T, b: T): boolean {
    return a > b
  }
}
