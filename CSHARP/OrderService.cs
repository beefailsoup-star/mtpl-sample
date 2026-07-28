using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace MtplSample
{
    public class OrderService
    {
        private readonly IOrderRepository _orderRepo;
        private readonly IProductRepository _productRepo;
        private readonly IPaymentProcessor _paymentProcessor;

        public OrderService(IOrderRepository orderRepo, IProductRepository productRepo, IPaymentProcessor paymentProcessor)
        {
            _orderRepo = orderRepo;
            _productRepo = productRepo;
            _paymentProcessor = paymentProcessor;
        }

        public async Task<OrderResult> PlaceOrderAsync(OrderRequest request)
        {
            var product = await _productRepo.GetByIdAsync(request.ProductId);
            if (product == null)
                return OrderResult.Failure("Product not found.");

            if (product.Stock < request.Quantity)
                return OrderResult.Failure("Insufficient stock.");

            var total = product.Price * request.Quantity;
            var paymentResult = await _paymentProcessor.ChargeAsync(request.PaymentToken, total);

            if (!paymentResult.Success)
                return OrderResult.Failure("Payment failed: " + paymentResult.ErrorMessage);

            var order = new Order
            {
                Id = Guid.NewGuid(),
                ProductId = request.ProductId,
                Quantity = request.Quantity,
                TotalAmount = total,
                Status = OrderStatus.Confirmed,
                CreatedAt = DateTime.UtcNow
            };

            await _orderRepo.AddAsync(order);
            return OrderResult.Success(order.Id);
        }
    }

    public class OrderRequest
    {
        public Guid ProductId { get; set; }
        public int Quantity { get; set; }
        public string PaymentToken { get; set; }
    }

    public class OrderResult
    {
        public bool IsSuccess { get; private set; }
        public Guid OrderId { get; private set; }
        public string ErrorMessage { get; private set; }

        public static OrderResult Success(Guid orderId) => new() { IsSuccess = true, OrderId = orderId };
        public static OrderResult Failure(string error) => new() { IsSuccess = false, ErrorMessage = error };
    }

    public class Order
    {
        public Guid Id { get; set; }
        public Guid ProductId { get; set; }
        public int Quantity { get; set; }
        public decimal TotalAmount { get; set; }
        public OrderStatus Status { get; set; }
        public DateTime CreatedAt { get; set; }
    }

    public enum OrderStatus { Pending, Confirmed, Shipped, Delivered, Cancelled }

    public interface IOrderRepository
    {
        Task AddAsync(Order order);
    }

    public interface IProductRepository
    {
        Task<Product> GetByIdAsync(Guid id);
    }
}
