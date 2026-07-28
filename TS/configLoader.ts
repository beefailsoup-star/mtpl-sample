export type ConfigSchema<T> = {
  [K in keyof T]: ConfigField<T[K]>
}

export type ConfigField<T> = {
  default: T
  validator?: (value: unknown) => boolean
  description?: string
}

export class ConfigLoader<T extends Record<string, any>> {
  constructor(private schema: ConfigSchema<T>) {}

  load(source: Record<string, unknown>): T {
    const config = {} as T
    for (const key in this.schema) {
      const field = this.schema[key]
      const raw = key in source ? source[key] : field.default
      if (field.validator && !field.validator(raw)) {
        throw new Error(`Config validation failed for '${String(key)}': received ${JSON.stringify(raw)}`)
      }
      config[key] = raw as T[typeof key]
    }
    return config
  }

  getDefaults(): T {
    const config = {} as T
    for (const key in this.schema) config[key] = this.schema[key].default
    return config
  }
}
