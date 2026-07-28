export type InterceptorFn = (config: RequestInit) => RequestInit | Promise<RequestInit>;
export type ResponseInterceptorFn = (response: Response) => Response | Promise<Response>;

export interface HttpInterceptor {
  requestInterceptors: InterceptorFn[];
  responseInterceptors: ResponseInterceptorFn[];
}

export class InterceptorChain {
  private interceptors: HttpInterceptor = {
    requestInterceptors: [],
    responseInterceptors: [],
  };

  addRequestInterceptor(fn: InterceptorFn): void {
    this.interceptors.requestInterceptors.push(fn);
  }

  addResponseInterceptor(fn: ResponseInterceptorFn): void {
    this.interceptors.responseInterceptors.push(fn);
  }

  async applyRequest(config: RequestInit): Promise<RequestInit> {
    let chain = config;
    for (const fn of this.interceptors.requestInterceptors) {
      chain = await fn(chain);
    }
    return chain;
  }

  async applyResponse(response: Response): Promise<Response> {
    let chain = response;
    for (const fn of this.interceptors.responseInterceptors) {
      chain = await fn(chain);
    }
    return chain;
  }

  clear(): void {
    this.interceptors.requestInterceptors = [];
    this