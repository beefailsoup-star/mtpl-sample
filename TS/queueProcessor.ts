export type QueueTask<T> = () => Promise<T>

export interface QueueResult<T> {
  promise: Promise<T>
  resolve: (value: T) => void
  reject: (reason: unknown) => void
}

export class QueueProcessor<T> {
  private queue: QueueResult<T>[] = []
  private running = 0
  private paused = false

  constructor(private concurrency: number = 1) {}

  enqueue(task: QueueTask<T>): Promise<T> {
    return new Promise<T>((resolve, reject) => {
      this.queue.push({ promise: task(), resolve, reject })
      this.processNext()
    })
  }

  private async processNext(): Promise<void> {
    if (this.paused || this.running >= this.concurrency || this.queue.length === 0) return

    this.running++
    const item = this.queue.shift()!

    try {
      const result = await item.promise
      item.resolve(result)
    } catch (err) {
      item.reject(err)
    } finally {
      this.running--
      this.processNext()
    }
  }

  pause(): void {
    this.paused = true
  }

  resume(): void {
    this.paused = false
    for (let i = 0; i < this.concurrency; i++) this.processNext()
  }

  get pending(): number {
    return this.queue.length
  }

  get active(): number {
    return this.running
  }
}
