export function pick<T extends Record<string, any>, K extends keyof T>(obj: T, keys: K[]): Pick<T, K> {
  const result = {} as Pick<T, K>
  for (const key of keys) if (key in obj) result[key] = obj[key]
  return result
}

export function omit<T extends Record<string, any>, K extends keyof T>(obj: T, keys: K[]): Omit<T, K> {
  const result = { ...obj } as any
  for (const key of keys) delete result[key]
  return result as Omit<T, K>
}

export function deepClone<T>(obj: T): T {
  if (obj === null || typeof obj !== 'object') return obj
  if (obj instanceof Date) return new Date(obj.getTime()) as any
  if (Array.isArray(obj)) return obj.map(deepClone) as any
  const cloned = {} as any
  for (const key in obj) {
    if (Object.prototype.hasOwnProperty.call(obj, key)) cloned[key] = deepClone(obj[key])
  }
  return cloned
}

export function merge<T extends Record<string, any>, U extends Record<string, any>>(target: T, source: U): T & U {
  const result = { ...target } as any
  for (const key in source) {
    if (Object.prototype.hasOwnProperty.call(source, key)) {
      if (source[key] !== null && typeof source[key] === 'object' && !Array.isArray(source[key]) && typeof result[key] === 'object' && result[key] !== null) {
        result[key] = merge(result[key], source[key])
      } else {
        result[key] = source[key]
      }
    }
  }
  return result
}

export function keys<T extends Record<string, any>>(obj: T): (keyof T)[] {
  return Object.keys(obj) as (keyof T)[]
}

export function values<T extends Record<string, any>, V = T[keyof T]>(obj: T): V[] {
  return Object.values(obj) as V[]
}

export function entries<T extends Record<string, any>, K extends keyof T = keyof T>(obj: T): [K, T[K]][] {
  return Object.entries(obj) as [K, T[K]][]
}

export function isEmpty(obj: Record<string, any>): boolean {
  return Object.keys(obj).length === 0
}
