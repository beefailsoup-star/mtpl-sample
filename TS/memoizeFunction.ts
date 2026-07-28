export function memoize<T extends (...args: any[]) => any>(
  fn: T,
  keyFn?: (...args: Parameters<T>) => string
): T & { clear: () => void } {
  const cache = new Map<string, ReturnType<T>>()

  const memoized = (...args: Parameters<T>): ReturnType<T> => {
    const key = keyFn ? keyFn(...args) : JSON.stringify(args)
    if (cache.has(key)) return cache.get(key)!
    const result = fn(...args)
    cache.set(key, result)
    return result
  }

  memoized.clear = (): void => cache.clear()

  return memoized as any
}

export function memoizeAsync<T extends (...args: any[]) => Promise<any>>(
  fn: T,
  keyFn?: (...args: Parameters<T>) => string
): T & { clear: () => void } {
  const cache = new Map<string, ReturnType<T>>()

  const memoized = (...args: Parameters<T>): ReturnType<T> => {
    const key = keyFn ? keyFn(...args) : JSON.stringify(args)
    if (cache.has(key)) return cache.get(key)!
    const promise = fn(...args)
    cache.set(key, promise)
    return promise
  }

  memoized.clear = (): void => cache.clear()

  return memoized as any
}
