export function capitalize<T extends string>(str: T): Capitalize<T> {
  return (str.charAt(0).toUpperCase() + str.slice(1)) as Capitalize<T>
}

export function uncapitalize<T extends string>(str: T): Uncapitalize<T> {
  return (str.charAt(0).toLowerCase() + str.slice(1)) as Uncapitalize<T>
}

export function camelCase<T extends string>(str: T): string {
  return str.replace(/[-_\s]+(.)?/g, (_, c) => c ? c.toUpperCase() : '')
}

export function kebabCase(str: string): string {
  return str.replace(/([A-Z])/g, '-$1').replace(/[\s_]+/g, '-').toLowerCase().replace(/^-/, '')
}

export function snakeCase(str: string): string {
  return str.replace(/([A-Z])/g, '_$1').replace(/[\s-]+/g, '_').toLowerCase().replace(/^_/, '')
}

export function truncate(str: string, maxLength: number, suffix = '...'): string {
  if (str.length <= maxLength) return str
  return str.slice(0, maxLength - suffix.length) + suffix
}

export function randomString(length: number, chars = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789'): string {
  let result = ''
  for (let i = 0; i < length; i++) result += chars.charAt(Math.floor(Math.random() * chars.length))
  return result
}

export function isNotEmpty<T>(val: T | null | undefined): val is T {
  return val !== null && val !== undefined
}

export function interpolate(template: string, params: Record<string, string | number>): string {
  return template.replace(/\{\{(\w+)\}\}/g, (_, key) => String(params[key] ?? ''))
}
