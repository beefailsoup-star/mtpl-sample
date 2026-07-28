export interface TokenPayload {
  sub: string;
  email: string;
  roles: string[];
  iat: number;
  exp: number;
}

export interface TokenPair {
  accessToken: string;
  refreshToken: string;
}

export class TokenManager {
  private accessToken: string | null = null;
  private refreshToken: string | null = null;
  private onRefresh: (refreshToken: string) => Promise<TokenPair>;

  constructor(onRefresh: (refreshToken: string) => Promise<TokenPair>) {
    this.onRefresh = onRefresh;
  }

  setTokens(pair: TokenPair): void {
    this.accessToken = pair.accessToken;
    this.refreshToken = pair.refreshToken;
    this.storeTokens(pair);
  }

  getAccessToken(): string | null {
    if (!this.accessToken) this.accessToken = this.loadAccessToken();
    return this.accessToken;
  }

  async refreshAccessToken(): Promise<string> {
    if (!this.refreshToken) throw new Error("No refresh token available");
    const pair = await this.onRefresh(this.refreshToken);
    this.setTokens(pair);
    return pair.accessToken;
  }

  isTokenExpired