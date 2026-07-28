export type QueryParams = Record<string, string | string[] | undefined>

export interface ParsedUrl {
  protocol: string
  hostname: string
  port: string
  pathname: string
  search: string
  hash: string
  query: QueryParams
}

export function parseUrl(url: string): ParsedUrl {
  const parsed = new URL(url)
  const query: QueryParams = {}
  parsed.searchParams.forEach((value, key) => {
    const existing = query[key]
    if (existing === undefined) { query[key] = value; return }
    query[key] = Array.isArray(existing) ? [...existing, value] : [existing, value]
  })
  return {
    protocol: parsed.protocol.replace(':', ''),
    hostname: parsed.hostname,
    port: parsed.port,
    pathname: parsed.pathname,
    search: parsed.search,
    hash: parsed.hash,
    query,
  }
}

export function buildUrl(base: string, pathname: string, query?: QueryParams): string {
  const url = new URL(pathname, base)
  if (query) {
    for (const [key, value] of Object.entries(query)) {
      if (value === undefined) continue
      if (Array.isArray(value)) value.forEach(v => url.searchParams.append(key, v))
      else url.searchParams.set(key, value)
    }
  }
  return url.toString()
}

export function getQueryParam(url: string, key: string): string | null {
  return new URL(url).searchParams.get(key)
}

export function getQueryParams(url: string, key: string): string[] {
  return new URL(url).searchParams.getAll(key)
}

export function appendQueryParam(url: string, key: string, value: string): string {
  const parsed = new URL(url)
  parsed.searchParams.append(key, value)
  return parsed.toString()
}

export function setQueryParam(url: string, key: string, value: string): string {
  const parsed = new URL(url)
  parsed.searchParams.set(key, value)
  return parsed.toString()
}
