export type DatabaseType = "postgres" | "mysql" | "sqlite" | "mongodb";

export interface ConnectionConfig {
  host: string;
  port: number;
  database: string;
  username: string;
  password: string;
  poolSize?: number;
  timeout?: number;
}

export interface QueryResult<T> {
  rows: T[];
  rowCount: number;
  duration: number;
}

export interface DatabaseAdapter {
  connect(config: ConnectionConfig): Promise<void>;
  disconnect(): Promise<void>;
  query<T>(sql: string, params?: unknown[]): Promise<QueryResult<T>>;
  transaction<T>(fn: (adapter: DatabaseAdapter) => Promise<T>): Promise<T>;
  isConnected(): boolean;
}

export class PostgresAdapter implements DatabaseAdapter {
  private connected = false;
  async connect(config: ConnectionConfig): Promise<void> { this.connected = true; }
  async disconnect(): Promise<void> { this.connected = false; }
  async query<T>(sql: string, params?: unknown[]): Promise<QueryResult<T>> {
    return { rows: [], rowCount: 0, duration: 0 };
  }