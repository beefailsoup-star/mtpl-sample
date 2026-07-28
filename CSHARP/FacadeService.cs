using System;

namespace MtplSample
{
    public class OrderVerificationService
    {
        public bool VerifyStock(Guid productId, int quantity)
        {
            return quantity > 0 && quantity < 100;
        }
    }

    public class PaymentGatewayService
    {
        public bool ProcessPayment(string token, decimal amount)
        {
            return !string.IsNullOrEmpty(token) && amount > 0;
        }
    }

    public class ShippingService
    {
        public string ArrangeShipping(Guid orderId, string address)
        {
            return $"SHIP-{orderId:N}-{address.GetHashCode():X}";
        }
    }

    public class NotificationService
    {
        public void SendConfirmation(string email, Guid orderId)
        {
            LoggerService.Instance.LogInfo($"Confirmation sent to {email} for order {orderId}.");
        }
    }

    public class FacadeService
    {
        private readonly OrderVerificationService _verification = new();
        private readonly PaymentGatewayService _payment = new();
        private readonly ShippingService _shipping = new();
        private readonly NotificationService _notification = new();

        public bool PlaceOrder(Guid productId, int quantity, string paymentToken, string email, string address)
        {
            if (!_verification.VerifyStock(productId, quantity))
                return false;

            if (!_payment.ProcessPayment(paymentToken, quantity * 10m))
                return false;

            var orderId = Guid.NewGuid();
            var tracking = _shipping.ArrangeShipping(orderId, address);
            _notification.SendConfirmation(email, orderId);

            LoggerService.Instance.LogInfo($"Order {orderId} placed. Tracking: {tracking}");
            return true;
        }
    }
}
