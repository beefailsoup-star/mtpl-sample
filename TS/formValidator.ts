type ValidationRule<T> = {
  validate: (value: T) => boolean
  message: string
}

type FieldRules<T> = Record<keyof T, ValidationRule<any>[]>

type ValidationErrors<T> = Partial<Record<keyof T, string>>

export class FieldValidator<T> {
  private rules: ValidationRule<T>[] = []

  addRule(rule: ValidationRule<T>): this {
    this.rules.push(rule)
    return this
  }

  validate(value: T): string | null {
    for (const rule of this.rules) {
      if (!rule.validate(value)) return rule.message
    }
    return null
  }
}

export class FormValidator<T extends Record<string, any>> {
  private fields = new Map<keyof T, FieldValidator<any>>()

  field<K extends keyof T>(name: K): FieldValidator<T[K]> {
    let fv = this.fields.get(name) as FieldValidator<T[K]> | undefined
    if (!fv) {
      fv = new FieldValidator<T[K]>()
      this.fields.set(name, fv)
    }
    return fv
  }

  validate(data: T): ValidationErrors<T> {
    const errors: ValidationErrors<T> = {}
    for (const [key, validator] of this.fields) {
      const msg = validator.validate(data[key])
      if (msg !== null) errors[key] = msg
    }
    return errors
  }

  isValid(data: T): boolean {
    return Object.keys(this.validate(data)).length === 0
  }
}
