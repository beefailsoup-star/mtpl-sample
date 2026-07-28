export function chunk<T>(arr: T[], size: number): T[][] {
  const result: T[][] = []
  for (let i = 0; i < arr.length; i += size) result.push(arr.slice(i, i + size))
  return result
}

export function unique<T>(arr: T[]): T[] {
  return [...new Set(arr)]
}

export function uniqueBy<T, K>(arr: T[], keyFn: (item: T) => K): T[] {
  const seen = new Set<K>()
  const result: T[] = []
  for (const item of arr) {
    const key = keyFn(item)
    if (!seen.has(key)) { seen.add(key); result.push(item) }
  }
  return result
}

export function shuffle<T>(arr: T[]): T[] {
  const result = [...arr]
  for (let i = result.length - 1; i > 0; i--) {
    const j = Math.floor(Math.random() * (i + 1));
    [result[i], result[j]] = [result[j], result[i]]
  }
  return result
}

export function groupBy<T, K extends string | number | symbol>(arr: T[], keyFn: (item: T) => K): Record<K, T[]> {
  const result = {} as Record<K, T[]>
  for (const item of arr) {
    const key = keyFn(item)
    if (!result[key]) result[key] = []
    result[key].push(item)
  }
  return result
}

export function partition<T>(arr: T[], predicate: (item: T) => boolean): [T[], T[]] {
  const pass: T[] = []
  const fail: T[] = []
  for (const item of arr) (predicate(item) ? pass : fail).push(item)
  return [pass, fail]
}

export function flatten<T>(arr: T[][]): T[] {
  return ([] as T[]).concat(...arr)
}

export function range(start: number, end: number, step = 1): number[] {
  const result: number[] = []
  if (step > 0) for (let i = start; i < end; i += step) result.push(i)
  else for (let i = start; i > end; i += step) result.push(i)
  return result
}

export function zip<T, U>(a: T[], b: U[]): [T, U][] {
  const len = Math.min(a.length, b.length)
  const result: [T, U][] = []
  for (let i = 0; i < len; i++) result.push([a[i], b[i]])
  return result
}
