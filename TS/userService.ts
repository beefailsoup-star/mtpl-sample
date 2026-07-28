export interface User {
  id: string;
  email: string;
  name: string;
  avatar?: string;
  isActive: boolean;
  createdAt: Date;
  updatedAt: Date;
}

export interface CreateUserDto {
  email: string;
  name: string;
  password: string;
  avatar?: string;
}

export interface UpdateUserDto {
  name?: string;
  avatar?: string;
  isActive?: boolean;
}

export interface UserFilter {
  search?: string;
  isActive?: boolean;
  page?: number;
  limit?: number;
}

export class UserService {
  constructor(private api: { get<T>(path: string): Promise<T>; post<T>(path: string, body: unknown): Promise<T>; put<T>(path: string, body: unknown): Promise<T>; delete<T>(path: string): Promise<T> }) {}

  async getUsers(filter?: UserFilter): Promise<{ users: User[]; total: number }> {
    const params = new URLSearchParams();
    if (filter?.search) params.set("search", filter.search);
    if (filter?.isActive !== undefined) params.set("isActive", String(filter.isActive));
    if (filter?.page) params.set("page", String(filter.page));
    if (filter?.limit) params.set("limit", String(filter.limit));
    const qs = params.toString();
    return this.api.get