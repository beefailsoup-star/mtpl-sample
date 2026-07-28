export interface PaginationParams {
  page: number
  pageSize: number
}

export interface Page<T> {
  items: T[]
  total: number
  page: number
  pageSize: number
  totalPages: number
  hasNext: boolean
  hasPrev: boolean
}

export function paginate<T>(
  items: T[],
  params: PaginationParams
): Page<T> {
  const { page, pageSize } = params
  const total = items.length
  const totalPages = Math.ceil(total / pageSize) || 1
  const start = (page - 1) * pageSize
  const paged = items.slice(start, start + pageSize)

  return {
    items: paged,
    total,
    page,
    pageSize,
    totalPages,
    hasNext: page < totalPages,
    hasPrev: page > 1,
  }
}

export function paginationParams(query: Record<string, string | undefined>, defaults: PaginationParams = { page: 1, pageSize: 20 }): PaginationParams {
  return {
    page: Math.max(1, parseInt(query.page ?? String(defaults.page), 10) || defaults.page),
    pageSize: Math.max(1, Math.min(100, parseInt(query.pageSize ?? String(defaults.pageSize), 10) || defaults.pageSize)),
  }
}

export function getOffset(params: PaginationParams): number {
  return (params.page - 1) * params.pageSize
}
