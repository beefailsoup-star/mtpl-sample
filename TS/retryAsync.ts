export interface RetryOptions {
  maxAttempts?: number
  delay?: number
  backoff?: 'fixed' | 'exponential' | 'linear'
  onRetry?: (attempt: number, error: unknown) => void
}

const sleep = (ms: number) => new Promise(resolve => setTimeout(resolve, ms))

export async function retry<T>(
  fn: () => Promise<T>,
  options: RetryOptions = {}
): Promise<T> {
  const { maxAttempts = 3, delay = 1000, backoff = 'exponential', onRetry } = options

  let lastError: unknown

  for (let attempt = 1; attempt <= maxAttempts; attempt++) {
    try {
      return await fn()
    } catch (err) {
      lastError = err
      if (attempt === maxAttempts) break
      if (onRetry) onRetry(attempt, err)

      let waitTime: number
      if (backoff === 'fixed') waitTime = delay
      else if (backoff === 'linear') waitTime = delay * attempt
      else waitTime = delay * Math.pow(2, attempt - 1)

      await sleep(waitTime)
    }
  }

  throw lastError
}
