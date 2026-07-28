export type PaymentMethod = "credit_card" | "debit_card" | "paypal" | "stripe" | "crypto";

export interface PaymentRequest {
  amount: number;
  currency: string;
  method: PaymentMethod;
  metadata?: Record<string, string>;
}

export interface PaymentResult {
  success: boolean;
  transactionId: string;
  amount: number;
  currency: string;
  timestamp: Date;
  error?: string;
}

export interface PaymentGateway {
  processPayment(request: PaymentRequest): Promise<PaymentResult>;
  refundPayment(transactionId: string, amount?: number): Promise<PaymentResult>;
  getStatus(transactionId: string): Promise<PaymentResult>;
}

export class StripeGateway implements PaymentGateway {
  async processPayment(request: PaymentRequest): Promise<PaymentResult> {
    return { success: true, transactionId: crypto.randomUUID(), amount: request.amount, currency: request.currency, timestamp: new Date() };
  }
  async refundPayment(transactionId: string, amount?: number): Promise<PaymentResult> {
    return { success: true, transactionId, amount: amount ?? 0, currency: "USD", timestamp: new Date() };
  }