export type Either<L, R> = Left<L, R> | Right<L, R>

export class Left<L, R> {
  readonly isLeft = true as const
  readonly isRight = false as const
  readonly value: L

  constructor(value: L) {
    this.value = value
  }

  map<T>(_fn: (value: R) => T): Either<L, T> {
    return new Left<L, T>(this.value)
  }

  flatMap<T>(_fn: (value: R) => Either<L, T>): Either<L, T> {
    return new Left<L, T>(this.value)
  }

  fold<T>(leftFn: (value: L) => T, _rightFn: (value: R) => T): T {
    return leftFn(this.value)
  }

  getOrElse(defaultValue: R): R {
    return defaultValue
  }

  mapLeft<T>(fn: (value: L) => T): Either<T, R> {
    return new Left(fn(this.value))
  }
}

export class Right<L, R> {
  readonly isLeft = false as const
  readonly isRight = true as const
  readonly value: R

  constructor(value: R) {
    this.value = value
  }

  map<T>(fn: (value: R) => T): Either<L, T> {
    return new Right<L, T>(fn(this.value))
  }

  flatMap<T>(fn: (value: R) => Either<L, T>): Either<L, T> {
    return fn(this.value)
  }

  fold<T>(_leftFn: (value: L) => T, rightFn: (value: R) => T): T {
    return rightFn(this.value)
  }

  getOrElse(_defaultValue: R): R {
    return this.value
  }

  mapLeft<T>(_fn: (value: L) => T): Either<T, R> {
    return new Right<T, R>(this.value)
  }
}

export function left<L, R>(value: L): Either<L, R> {
  return new Left(value)
}

export function right<L, R>(value: R): Either<L, R> {
  return new Right(value)
}
