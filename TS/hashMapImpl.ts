export class HashMapEntry<K, V> {
  constructor(
    public key: K,
    public value: V,
    public next: HashMapEntry<K, V> | null = null
  ) {}
}

const DEFAULT_CAPACITY = 16
const LOAD_FACTOR = 0.75

export class HashMap<K, V> {
  private buckets: (HashMapEntry<K, V> | null)[]
  private _size = 0

  constructor(capacity = DEFAULT_CAPACITY) {
    this.buckets = new Array(capacity).fill(null)
  }

  get size(): number {
    return this._size
  }

  put(key: K, value: V): void {
    const index = this.hash(key)
    let entry = this.buckets[index]
    while (entry) {
      if (this.equals(entry.key, key)) { entry.value = value; return }
      entry = entry.next
    }
    this.buckets[index] = new HashMapEntry(key, value, this.buckets[index])
    this._size++
    if (this._size > this.buckets.length * LOAD_FACTOR) this.resize()
  }

  get(key: K): V | undefined {
    const entry = this.findEntry(key)
    return entry?.value
  }

  has(key: K): boolean {
    return this.findEntry(key) !== null
  }

  delete(key: K): boolean {
    const index = this.hash(key)
    let entry = this.buckets[index]
    let prev: HashMapEntry<K, V> | null = null
    while (entry) {
      if (this.equals(entry.key, key)) {
        if (prev) prev.next = entry.next
        else this.buckets[index] = entry.next
        this._size--
        return true
      }
      prev = entry
      entry = entry.next
    }
    return false
  }

  clear(): void {
    this.buckets = new Array(this.buckets.length).fill(null)
    this._size = 0
  }

  keys(): K[] {
    const result: K[] = []
    for (const bucket of this.buckets) {
      let entry = bucket
      while (entry) { result.push(entry.key); entry = entry.next }
    }
    return result
  }

  values(): V[] {
    const result: V[] = []
    for (const bucket of this.buckets) {
      let entry = bucket
      while (entry) { result.push(entry.value); entry = entry.next }
    }
    return result
  }

  entries(): [K, V][] {
    const result: [K, V][] = []
    for (const bucket of this.buckets) {
      let entry = bucket
      while (entry) { result.push([entry.key, entry.value]); entry = entry.next }
    }
    return result
  }

  forEach(fn: (key: K, value: V) => void): void {
    for (const [key, value] of this.entries()) fn(key, value)
  }

  private findEntry(key: K): HashMapEntry<K, V> | null {
    let entry = this.buckets[this.hash(key)]
    while (entry) {
      if (this.equals(entry.key, key)) return entry
      entry = entry.next
    }
    return null
  }

  private hash(key: K): number {
    if (typeof key === 'string') {
      let hash = 0
      for (let i = 0; i < key.length; i++) { hash = (hash << 5) - hash + key.charCodeAt(i); hash |= 0 }
      return Math.abs(hash) % this.buckets.length
    }
    if (typeof key === 'number') return Math.abs(key) % this.buckets.length
    return Math.abs(String(key).length) % this.buckets.length
  }

  private equals(a: K, b: K): boolean {
    return a === b
  }

  private resize(): void {
    const entries = this.entries()
    this.buckets = new Array(this.buckets.length * 2).fill(null)
    this._size = 0
    for (const [key, value] of entries) this.put(key, value)
  }
}
