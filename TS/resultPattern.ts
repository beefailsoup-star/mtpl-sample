export type Result<T, E = Error> = Ok<T, E> | Err<T, E>

export class Ok<T, E = Error> {
  readonly success = true as const
  readonly value: T

  constructor(value: T) {
    this.value = value
  }

  isOk(): this is Ok<T, E> {
    return true
  }

  isErr(): this is Err<T, E> {
    return false
  }

  map<R>(fn: (value: T) => R): Result<R, E> {
    return new Ok(fn(this.value))
  }

  mapErr<F>(_fn: (error: E) => F): Result<T, F> {
    return this as any as Result<T, F>
  }

  unwrap(): T {
    return this.value
  }

  unwrapOr(_fallback: T): T {
    return this.value
  }

  unwrapOrElse(fn: (error: E) => T): T {
    return this.value
  }
}

export class Err<T, E = Error> {
  readonly success = false as const
  readonly error: E

  constructor(error: E) {
    this.error = error
  }

  isOk(): this is Ok<T, E> {
    return false
  }

  isErr(): this is Err<T, E> {
    return true
  }

  map<R>(_fn: (value: T) => R): Result<R, E> {
    return this as any as Result<R, E>
  }

  mapErr<F>(fn: (error: E) => F): Result<T, F> {
    return new Err(fn(this.error))
  }

  unwrap(): never {
    throw this.error instanceof Error ? this.error : new Error(String(this.error))
  }

  unwrapOr(fallback: T): T {
    return fallback
  }

  unwrapOrElse(fn: (error: E) => T): T {
    return fn(this.error)
  }
}

export function ok<T, E = Error>(value: T): Ok<T, E> {
  return new Ok(value)
}

export function err<T, E = Error>(error: E): Err<T, E> {
  return new Err(error)
}
