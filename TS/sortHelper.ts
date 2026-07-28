export type SortDirection = 'asc' | 'desc'

export interface SortConfig<T> {
  field: keyof T
  direction: SortDirection
}

export type Comparator<T> = (a: T, b: T) => number

export function createComparator<T>(...comparators: Comparator<T>[]): Comparator<T> {
  return (a: T, b: T): number => {
    for (const cmp of comparators) {
      const result = cmp(a, b)
      if (result !== 0) return result
    }
    return 0
  }
}

export function fieldComparator<T, K extends keyof T>(field: K, direction: SortDirection = 'asc'): Comparator<T> {
  return (a: T, b: T): number => {
    const va = a[field]
    const vb = b[field]
    if (va === vb) return 0
    if (va == null) return 1
    if (vb == null) return -1
    const cmp = va < vb ? -1 : 1
    return direction === 'asc' ? cmp : -cmp
  }
}

export function sortBy<T>(items: T[], config: SortConfig<T> | SortConfig<T>[]): T[] {
  const configs = Array.isArray(config) ? config : [config]
  const comparator = createComparator(...configs.map(c => fieldComparator(c.field, c.direction)))
  return [...items].sort(comparator)
}

export function stringComparator(direction: SortDirection = 'asc'): Comparator<string> {
  return (a: string, b: string): number => {
    const cmp = a.localeCompare(b)
    return direction === 'asc' ? cmp : -cmp
  }
}

export function numberComparator(direction: SortDirection = 'asc'): Comparator<number> {
  return (a: number, b: number): number => direction === 'asc' ? a - b : b - a
}

export function dateComparator(direction: SortDirection = 'asc'): Comparator<Date> {
  return (a: Date, b: Date): number => direction === 'asc' ? a.getTime() - b.getTime() : b.getTime() - a.getTime()
}
