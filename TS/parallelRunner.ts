export interface ParallelResult<T> {
  successes: { index: number; value: T }[]
  errors: { index: number; error: unknown }[]
}

export async function parallelAll<T>(
  tasks: (() => Promise<T>)[],
  concurrency: number = Infinity
): Promise<T[]> {
  const results: T[] = []
  let index = 0

  const worker = async (): Promise<void> => {
    while (index < tasks.length) {
      const i = index++
      results[i] = await tasks[i]()
    }
  }

  const workers = Array.from({ length: Math.min(concurrency, tasks.length) }, () => worker())
  await Promise.all(workers)
  return results
}

export async function parallelSettled<T>(
  tasks: (() => Promise<T>)[],
  concurrency: number = Infinity
): Promise<ParallelResult<T>> {
  const result: ParallelResult<T> = { successes: [], errors: [] }
  let index = 0

  const worker = async (): Promise<void> => {
    while (index < tasks.length) {
      const i = index++
      try {
        const value = await tasks[i]()
        result.successes.push({ index: i, value })
      } catch (error) {
        result.errors.push({ index: i, error })
      }
    }
  }

  const workers = Array.from({ length: Math.min(concurrency, tasks.length) }, () => worker())
  await Promise.all(workers)
  return result
}
