const ENTITY_MAP: Record<string, string> = {
  '&': '&amp;',
  '<': '&lt;',
  '>': '&gt;',
  '"': '&quot;',
  "'": '&#39;',
}

export function escapeHTML(str: string): string {
  return str.replace(/[&<>"']/g, ch => ENTITY_MAP[ch] || ch)
}

const TAG_RE = /<\/?[^>]+>/g

export function stripTags(str: string, allowedTags?: string[]): string {
  if (!allowedTags || allowedTags.length === 0) return str.replace(TAG_RE, '')
  const allowed = new Set(allowedTags.map(t => t.toLowerCase()))
  return str.replace(TAG_RE, tag => {
    const match = tag.match(/<\/?(\w+)/)
    if (match && allowed.has(match[1].toLowerCase())) return tag
    return ''
  })
}

export function sanitizeEmail(email: string): string {
  return email.trim().toLowerCase()
}

export function sanitizeNumeric(input: string): string {
  return input.replace(/[^0-9.-]/g, '')
}

export function sanitizeAlphanumeric(input: string, extras?: string): string {
  const allowed = extras ? `a-zA-Z0-9${extras.replace(/[-[\]{}()*+?.,\\^$|#\s]/g, '\\$&')}` : 'a-zA-Z0-9'
  return input.replace(new RegExp(`[^${allowed}]`, 'g'), '')
}
