export type NextFn = () => Promise<void> | void

export type Middleware<TContext> = (ctx: TContext, next: NextFn) => Promise<void> | void

export class MiddlewareChain<TContext> {
  private middlewares: Middleware<TContext>[] = []

  use(...mw: Middleware<TContext>[]): this {
    this.middlewares.push(...mw)
    return this
  }

  compose(context: TContext): Promise<void> {
    const stack = [...this.middlewares]
    let index = -1

    const dispatch = (i: number): Promise<void> => {
      if (i <= index) return Promise.reject(new Error('next() called multiple times'))
      index = i
      const middleware = stack[i]
      if (!middleware) return Promise.resolve()
      try {
        const result = middleware(context, () => dispatch(i + 1))
        return result instanceof Promise ? result : Promise.resolve(result)
      } catch (err) {
        return Promise.reject(err)
      }
    }

    return dispatch(0)
  }

  clear(): this {
    this.middlewares = []
    return this
  }
}
