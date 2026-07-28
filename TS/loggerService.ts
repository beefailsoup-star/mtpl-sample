export type LogLevel = 'debug' | 'info' | 'warn' | 'error'

export interface Logger {
  debug(message: string, ...meta: unknown[]): void
  info(message: string, ...meta: unknown[]): void
  warn(message: string, ...meta: unknown[]): void
  error(message: string, ...meta: unknown[]): void
  setLevel(level: LogLevel): void
}

const LEVEL_RANK: Record<LogLevel, number> = { debug: 0, info: 1, warn: 2, error: 3 }

export class ConsoleLogger implements Logger {
  private level: LogLevel = 'debug'

  constructor(private prefix?: string) {}

  setLevel(level: LogLevel): void {
    this.level = level
  }

  debug(message: string, ...meta: unknown[]): void {
    this.log('debug', message, ...meta)
  }

  info(message: string, ...meta: unknown[]): void {
    this.log('info', message, ...meta)
  }

  warn(message: string, ...meta: unknown[]): void {
    this.log('warn', message, ...meta)
  }

  error(message: string, ...meta: unknown[]): void {
    this.log('error', message, ...meta)
  }

  private log(level: LogLevel, message: string, ...meta: unknown[]): void {
    if (LEVEL_RANK[level] < LEVEL_RANK[this.level]) return
    const timestamp = new Date().toISOString()
    const prefix = this.prefix ? ` [${this.prefix}]` : ''
    const formatted = `[${timestamp}] [${level.toUpperCase()}]${prefix} ${message}`
    if (level === 'error') console.error(formatted, ...meta)
    else if (level === 'warn') console.warn(formatted, ...meta)
    else console.log(formatted, ...meta)
  }
}

export class FileLogger implements Logger {
  private level: LogLevel = 'debug'
  private logs: string[] = []

  constructor(private filePath?: string) {}

  setLevel(level: LogLevel): void {
    this.level = level
  }

  debug(message: string, ...meta: unknown[]): void {
    this.write('debug', message, meta)
  }

  info(message: string, ...meta: unknown[]): void {
    this.write('info', message, meta)
  }

  warn(message: string, ...meta: unknown[]): void {
    this.write('warn', message, meta)
  }

  error(message: string, ...meta: unknown[]): void {
    this.write('error', message, meta)
  }

  private write(level: LogLevel, message: string, meta: unknown[]): void {
    if (LEVEL_RANK[level] < LEVEL_RANK[this.level]) return
    const timestamp = new Date().toISOString()
    const entry = `[${timestamp}] [${level.toUpperCase()}] ${message}${meta.length ? ' ' + JSON.stringify(meta) : ''}`
    this.logs.push(entry)
    if (this.filePath) {
      try { require('fs').appendFileSync(this.filePath, entry + '\n') } catch { /* ignore */ }
    }
  }

  getLogs(): string[] {
    return [...this.logs]
  }

  clear(): void {
    this.logs = []
  }
}

export class NullLogger implements Logger {
  debug(_message: string, ..._meta: unknown[]): void {}
  info(_message: string, ..._meta: unknown[]): void {}
  warn(_message: string, ..._meta: unknown[]): void {}
  error(_message: string, ..._meta: unknown[]): void {}
  setLevel(_level: LogLevel): void {}
}
