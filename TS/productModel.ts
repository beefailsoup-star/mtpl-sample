export type ProductCategory = "electronics" | "clothing" | "food" | "books" | "other";

export interface Product {
  id: string;
  sku: string;
  name: string;
  description: string;
  price: number;
  category: ProductCategory;
  tags: string[];
  stock: number;
  isAvailable: boolean;
  createdAt: Date;
  updatedAt: Date;
}

export interface ProductVariant {
  id: string;
  productId: string;
  name: string;
  price: number;
  stock: number;
  attributes: Record<string, string>;
}

export class ProductModel {
  constructor(private data: Product) {}

  get id(): string { return this.data.id; }
  get name(): string { return this.data.name; }
  get price(): number { return this.data.price; }
  get category(): ProductCategory { return this.data.category; }