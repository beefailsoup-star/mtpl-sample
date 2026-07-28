export interface CurrencyOptions {
  currency?: string
  locale?: string
  decimals?: number
}

export interface PercentOptions {
  locale?: string
  decimals?: number
}

export function formatCurrency(value: number, options: CurrencyOptions = {}): string {
  const { currency = 'USD', locale = 'en-US', decimals } = options
  const opts: Intl.NumberFormatOptions = { style: 'currency', currency }
  if (decimals !== undefined) opts.minimumFractionDigits = decimals
  return new Intl.NumberFormat(locale, opts).format(value)
}

export function formatPercent(value: number, options: PercentOptions = {}): string {
  const { locale = 'en-US', decimals } = options
  const opts: Intl.NumberFormatOptions = { style: 'percent' }
  if (decimals !== undefined) opts.minimumFractionDigits = decimals
  return new Intl.NumberFormat(locale, opts).format(value)
}

export function formatOrdinal(value: number, locale = 'en-US'): string {
  if (locale !== 'en-US') return value.toLocaleString(locale)
  const suffixes = ['th', 'st', 'nd', 'rd']
  const v = value % 100
  const suffix = v >= 11 && v <= 13 ? 'th' : suffixes[value % 10] || 'th'
  return `${value}${suffix}`
}

export function formatCompact(value: number, locale = 'en-US'): string {
  return new Intl.NumberFormat(locale, { notation: 'compact' }).format(value)
}

export function formatNumber(value: number, locale = 'en-US', options?: Intl.NumberFormatOptions): string {
  return new Intl.NumberFormat(locale, options).format(value)
}
