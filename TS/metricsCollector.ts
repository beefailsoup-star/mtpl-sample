export interface Counter {
  inc(value?: number): void
  reset(): void
  get(): number
}

export function createCounter(name: string, labels?: Record<string, string>): Counter {
  let value = 0
  const labelStr = labels ? JSON.stringify(labels) : ''
  return {
    inc(v = 1): void { value += v },
    reset(): void { value = 0 },
    get(): number { return value },
  }
}

export interface Gauge {
  set(value: number): void
  inc(value?: number): void
  dec(value?: number): void
  reset(): void
  get(): number
}

export function createGauge(name: string, labels?: Record<string, string>): Gauge {
  let value = 0
  return {
    set(v: number): void { value = v },
    inc(v = 1): void { value += v },
    dec(v = 1): void { value -= v },
    reset(): void { value = 0 },
    get(): number { return value },
  }
}

export interface Histogram {
  observe(value: number): void
  reset(): void
  get(): { count: number; sum: number; min: number; max: number; avg: number }
}

export function createHistogram(name: string, labels?: Record<string, string>): Histogram {
  let count = 0
  let sum = 0
  let min = Infinity
  let max = -Infinity

  return {
    observe(value: number): void {
      count++
      sum += value
      if (value < min) min = value
      if (value > max) max = value
    },
    reset(): void {
      count = 0; sum = 0; min = Infinity; max = -Infinity
    },
    get() {
      return { count, sum, min: min === Infinity ? 0 : min, max: max === -Infinity ? 0 : max, avg: count ? sum / count : 0 }
    },
  }
}
