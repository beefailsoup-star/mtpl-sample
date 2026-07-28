using System;
using System.Threading.Tasks;

namespace MtplSample
{
    public interface IPaymentProcessor
    {
        Task<PaymentResult> ChargeAsync(string token, decimal amount);
    }

    public class PaymentResult
    {
        public bool Success { get; set; }
        public string TransactionId { get; set; }
        public string ErrorMessage { get; set; }

        public static PaymentResult Ok(string txId) => new() { Success = true, TransactionId = txId };
        public static PaymentResult Fail(string error) => new() { Success = false, ErrorMessage = error };
    }

    public class CreditCardProcessor : IPaymentProcessor
    {
        public async Task<PaymentResult> ChargeAsync(string token, decimal amount)
        {
            await Task.Delay(100);
            if (string.IsNullOrWhiteSpace(token))
                return PaymentResult.Fail("Invalid payment token.");
            return PaymentResult.Ok(Guid.NewGuid().ToString("N"));
        }
    }

    public class PayPalProcessor : IPaymentProcessor
    {
        public async Task<PaymentResult> ChargeAsync(string token, decimal amount)
        {
            await Task.Delay(150);
            if (amount <= 0)
                return PaymentResult.Fail("Invalid amount.");
            return PaymentResult.Ok("PP-" + Guid.NewGuid().ToString("N"));
        }
    }

    public class CryptoProcessor : IPaymentProcessor
    {
        public async Task<PaymentResult> ChargeAsync(string token, decimal amount)
        {
            await Task.Delay(200);
            if (amount > 10000)
                return PaymentResult.Fail("Exceeds crypto limit.");
            return PaymentResult.Ok("CR-" + Guid.NewGuid().ToString("N"));
        }
    }
}
