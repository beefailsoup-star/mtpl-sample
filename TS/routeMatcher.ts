export type RouteParams = Record<string, string>

export interface MatchResult<T extends RouteParams = RouteParams> {
  params: T
  path: string
}

type ParamExtractor = (segment: string) => string | undefined

export class RouteMatcher<T extends RouteParams = RouteParams> {
  private paramNames: string[] = []
  private regex: RegExp

  constructor(pattern: string) {
    const parts = pattern.split('/')
    const reParts = parts.map(part => {
      if (part.startsWith(':')) {
        this.paramNames.push(part.slice(1))
        return '([^/]+)'
      }
      if (part === '*') {
        this.paramNames.push('wildcard')
        return '(.*)'
      }
      return part.replace(/[.*+?^${}()|[\]\\]/g, '\\$&')
    })
    this.regex = new RegExp(`^${reParts.join('/')}$`)
  }

  match(path: string): MatchResult<T> | null {
    const m = path.match(this.regex)
    if (!m) return null
    const params = {} as T
    for (let i = 0; i < this.paramNames.length; i++) {
      params[this.paramNames[i] as keyof T] = m[i + 1] as T[keyof T]
    }
    return { params, path }
  }
}
