type Listener<T> = (state: T) => void
type Unsubscribe = () => void

export class StateStore<T extends Record<string, any>> {
  private state: T
  private listeners = new Set<Listener<T>>()

  constructor(initial: T) {
    this.state = { ...initial }
  }

  getState(): Readonly<T> {
    return this.state as Readonly<T>
  }

  setState(partial: Partial<T> | ((prev: T) => Partial<T>)): void {
    const patch = typeof partial === 'function' ? partial(this.state) : partial
    this.state = { ...this.state, ...patch }
    this.listeners.forEach(l => l(this.state))
  }

  subscribe(listener: Listener<T>): Unsubscribe {
    this.listeners.add(listener)
    return () => { this.listeners.delete(listener) }
  }

  destroy(): void {
    this.listeners.clear()
  }
}
