export interface ApiResponse<T> {
  data: T;
  status: number;
  message: string;
  timestamp: number;
}

export interface ApiError {
  code: string;
  message: string;
  details?: Record<string, string[]>;
}

export type HttpMethod = "GET" | "POST" | "PUT" | "PATCH" | "DELETE";

export interface RequestConfig {
  headers?: Record<string, string>;
  params?: Record<string, string>;
  timeout?: number;
  retries?: number;
}

export class ApiClient {
  constructor(private baseUrl: string, private defaultConfig?: RequestConfig) {}

  async get<T>(path: string, config?: RequestConfig): Promise<ApiResponse<T>> {
    const url = this.buildUrl(path, config?.params);
    const res = await fetch(url, { method: "GET", headers: this.mergeHeaders(config) });
    return this.handleResponse<T>(res);
  }

  async post<T>(path: string, body: unknown, config?: RequestConfig): Promise<ApiResponse<T>> {
    const res = await fetch(this.buildUrl(path), {
      method: "POST",
      headers: this.mergeHeaders(config),
      body: JSON.stringify(body),
    });
    return this.handleResponse<T>(res);
  }

  async put<T>(path: string, body: unknown, config?: RequestConfig): Promise<ApiResponse<T>> {
    const res = await fetch(this.build