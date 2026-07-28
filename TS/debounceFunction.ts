export function debounce<T extends (...args: any[]) => any>(
  fn: T,
  delay: number
): (...args: Parameters<T>) => void {
  let timer: ReturnType<typeof setTimeout> | null = null

  const debounced = (...args: Parameters<T>): void => {
    if (timer !== null) clearTimeout(timer)
    timer = setTimeout(() => {
      timer = null
      fn(...args)
    }, delay)
  }

  debounced.cancel = (): void => {
    if (timer !== null) { clearTimeout(timer); timer = null }
  }

  debounced.flush = (...args: Parameters<T>): void => {
    if (timer !== null) { clearTimeout(timer); timer = null }
    fn(...args)
  }

  return debounced
}
