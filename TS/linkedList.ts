export class ListNode<T> {
  value: T
  next: ListNode<T> | null = null
  prev: ListNode<T> | null = null

  constructor(value: T) {
    this.value = value
  }
}

export class LinkedList<T> {
  private head: ListNode<T> | null = null
  private tail: ListNode<T> | null = null
  private length = 0

  get size(): number {
    return this.length
  }

  get first(): T | null {
    return this.head?.value ?? null
  }

  get last(): T | null {
    return this.tail?.value ?? null
  }

  append(value: T): void {
    const node = new ListNode(value)
    if (!this.tail) {
      this.head = this.tail = node
    } else {
      this.tail.next = node
      node.prev = this.tail
      this.tail = node
    }
    this.length++
  }

  prepend(value: T): void {
    const node = new ListNode(value)
    if (!this.head) {
      this.head = this.tail = node
    } else {
      node.next = this.head
      this.head.prev = node
      this.head = node
    }
    this.length++
  }

  removeFirst(): T | null {
    if (!this.head) return null
    const value = this.head.value
    this.head = this.head.next
    if (this.head) this.head.prev = null
    else this.tail = null
    this.length--
    return value
  }

  removeLast(): T | null {
    if (!this.tail) return null
    const value = this.tail.value
    this.tail = this.tail.prev
    if (this.tail) this.tail.next = null
    else this.head = null
    this.length--
    return value
  }

  find(predicate: (value: T) => boolean): T | null {
    let current = this.head
    while (current) {
      if (predicate(current.value)) return current.value
      current = current.next
    }
    return null
  }

  toArray(): T[] {
    const result: T[] = []
    let current = this.head
    while (current) { result.push(current.value); current = current.next }
    return result
  }

  clear(): void {
    this.head = this.tail = null
    this.length = 0
  }

  *[Symbol.iterator](): Iterator<T> {
    let current = this.head
    while (current) { yield current.value; current = current.next }
  }
}
