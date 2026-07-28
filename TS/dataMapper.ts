export interface DataMapper<TSource, TTarget> {
  map(source: TSource): TTarget
}

export interface AsyncDataMapper<TSource, TTarget> {
  map(source: TSource): Promise<TTarget>
}

export class AutoMapper<TSource extends Record<string, any>, TTarget extends Record<string, any>>
  implements DataMapper<TSource, TTarget>
{
  constructor(
    private mapping: { [K in keyof TTarget]?: keyof TSource | ((src: TSource) => TTarget[K]) }
  ) {}

  map(source: TSource): TTarget {
    const result = {} as TTarget
    for (const key in this.mapping) {
      const mapper = this.mapping[key]!
      result[key] = typeof mapper === 'function'
        ? (mapper as (src: TSource) => TTarget[typeof key])(source)
        : source[mapper]
    }
    return result
  }
}

export class ArrayMapper<TSource, TTarget> implements DataMapper<TSource[], TTarget[]> {
  constructor(private itemMapper: DataMapper<TSource, TTarget>) {}

  map(source: TSource[]): TTarget[] {
    return source.map(s => this.itemMapper.map(s))
  }
}
