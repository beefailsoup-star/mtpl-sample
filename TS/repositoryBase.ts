export interface Entity {
  id: string;
  createdAt: Date;
  updatedAt: Date;
}

export interface FindOptions<T> {
  where?: Partial<T>;
  orderBy?: { [K in keyof T]?: "asc" | "desc" };
  skip?: number;
  take?: number;
}

export abstract class RepositoryBase<T extends Entity> {
  protected items: T[] = [];

  abstract getTableName(): string;

  async findById(id: string): Promise<T | null> {
    return this.items.find((item) => item.id === id) ?? null;
  }

  async findAll(options?: FindOptions<T>): Promise<T[]> {
    let result = [...this.items];
    if (options?.where) {
      result = result.filter((item) =>
        Object.entries(options.where!).every(([key, value]) => (item as any)[key] === value)
      );
    }
    if (options?.orderBy) {
      const [key, dir] = Object.entries(options.orderBy)[0];