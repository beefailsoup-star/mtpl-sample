export type EnvSchema<T> = {
  [K in keyof T]: EnvField<T[K]>
}

export type EnvField<T> = {
  env: string
  default: T
  parser?: (raw: string) => T
}

export class EnvParser<T extends Record<string, any>> {
  constructor(private schema: EnvSchema<T>) {}

  parse(envSource: Record<string, string | undefined> = process.env): T {
    const result = {} as T
    for (const key in this.schema) {
      const field = this.schema[key]
      const raw = envSource[field.env]
      if (raw === undefined) {
        result[key] = field.default
      } else {
        result[key] = field.parser ? field.parser(raw) : (raw as unknown as T[typeof key])
      }
    }
    return result
  }
}

export const envParsers = {
  number: (raw: string): number => {
    const val = Number(raw)
    if (isNaN(val)) throw new Error(`Cannot parse '${raw}' as number`)
    return val
  },
  boolean: (raw: string): boolean => {
    if (raw === 'true' || raw === '1') return true
    if (raw === 'false' || raw === '0') return false
    throw new Error(`Cannot parse '${raw}' as boolean`)
  },
  json: <T>(raw: string): T => JSON.parse(raw),
}
