export function throttle<T extends (...args: any[]) => any>(
  fn: T,
  interval: number
): (...args: Parameters<T>) => void {
  let lastCall = 0
  let timer: ReturnType<typeof setTimeout> | null = null
  let pending: Parameters<T> | null = null

  const throttled = (...args: Parameters<T>): void => {
    const now = Date.now()
    const remaining = interval - (now - lastCall)

    if (remaining <= 0) {
      if (timer !== null) { clearTimeout(timer); timer = null }
      lastCall = now
      pending = null
      fn(...args)
    } else if (!timer) {
      pending = args
      timer = setTimeout(() => {
        lastCall = Date.now()
        timer = null
        if (pending) { fn(...pending); pending = null }
      }, remaining)
    } else {
      pending = args
    }
  }

  throttled.cancel = (): void => {
    if (timer !== null) { clearTimeout(timer); timer = null }
    pending = null
  }

  throttled.flush = (): void => {
    if (timer !== null && pending) { clearTimeout(timer); timer = null; fn(...pending); pending = null }
  }

  return throttled
}
