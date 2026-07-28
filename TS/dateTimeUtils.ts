export type DateInput = Date | string | number

export function toDate(input: DateInput): Date {
  if (input instanceof Date) return new Date(input)
  if (typeof input === 'number') return new Date(input)
  const d = new Date(input)
  return isNaN(d.getTime()) ? new Date(NaN) : d
}

export function formatDate(date: DateInput, locale = 'en-US', options?: Intl.DateTimeFormatOptions): string {
  const d = toDate(date)
  if (isNaN(d.getTime())) return 'Invalid Date'
  return new Intl.DateTimeFormat(locale, options).format(d)
}

export function formatRelative(date: DateInput, base: DateInput = Date.now()): string {
  const diff = toDate(date).getTime() - toDate(base).getTime()
  const abs = Math.abs(diff)
  const seconds = Math.floor(abs / 1000)
  const minutes = Math.floor(seconds / 60)
  const hours = Math.floor(minutes / 60)
  const days = Math.floor(hours / 24)

  const suffix = diff >= 0 ? 'from now' : 'ago'
  if (days > 0) return `${days} day(s) ${suffix}`
  if (hours > 0) return `${hours} hour(s) ${suffix}`
  if (minutes > 0) return `${minutes} minute(s) ${suffix}`
  return `${seconds} second(s) ${suffix}`
}

export function addDays(date: DateInput, days: number): Date {
  const d = toDate(date)
  d.setDate(d.getDate() + days)
  return d
}

export function addMonths(date: DateInput, months: number): Date {
  const d = toDate(date)
  d.setMonth(d.getMonth() + months)
  return d
}

export function startOfDay(date: DateInput): Date {
  const d = toDate(date)
  d.setHours(0, 0, 0, 0)
  return d
}

export function endOfDay(date: DateInput): Date {
  const d = toDate(date)
  d.setHours(23, 59, 59, 999)
  return d
}

export function differenceInDays(a: DateInput, b: DateInput): number {
  const diff = toDate(a).getTime() - toDate(b).getTime()
  return Math.floor(diff / 86400000)
}

export function isLeapYear(year: number): boolean {
  return (year % 4 === 0 && year % 100 !== 0) || year % 400 === 0
}
