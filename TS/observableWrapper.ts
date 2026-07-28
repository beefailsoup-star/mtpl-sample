export type Observer<T> = (value: T) => void
export type Unsubscribe = () => void

export class Observable<T> {
  private observers = new Set<Observer<T>>()

  constructor(private value: T) {}

  get(): T {
    return this.value
  }

  set(next: T): void {
    this.value = next
    this.observers.forEach(fn => fn(next))
  }

  subscribe(observer: Observer<T>): Unsubscribe {
    this.observers.add(observer)
    return () => this.observers.delete(observer)
  }

  pipe<R>(...operators: Operator<T, any>[]): Observable<R> {
    let source: Observable<any> = this
    for (const op of operators) source = op(source)
    return source as Observable<R>
  }
}

export type Operator<T, R> = (source: Observable<T>) => Observable<R>

export function map<T, R>(fn: (value: T) => R): Operator<T, R> {
  return (source: Observable<T>) => {
    const dest = new Observable<R>(fn(source.get()))
    source.subscribe(val => dest.set(fn(val)))
    return dest
  }
}

export function filter<T>(predicate: (value: T) => boolean): Operator<T, T> {
  return (source: Observable<T>) => {
    const dest = new Observable<T>(source.get())
    source.subscribe(val => { if (predicate(val)) dest.set(val) })
    return dest
  }
}

export function distinctUntilChanged<T>(compareFn?: (a: T, b: T) => boolean): Operator<T, T> {
  return (source: Observable<T>) => {
    let prev = source.get()
    const dest = new Observable<T>(prev)
    source.subscribe(val => {
      const equal = compareFn ? compareFn(prev, val) : prev === val
      if (!equal) { prev = val; dest.set(val) }
    })
    return dest
  }
}
