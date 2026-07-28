using System;

namespace MtplSample
{
    public interface IOrderState
    {
        string Status { get; }
        void Next(OrderContext context);
        void Cancel(OrderContext context);
    }

    public class OrderContext
    {
        public IOrderState State { get; set; }

        public OrderContext()
        {
            State = new PendingState();
        }

        public void Next() => State.Next(this);
        public void Cancel() => State.Cancel(this);

        public string GetStatus() => State.Status;
    }

    public class PendingState : IOrderState
    {
        public string Status => "Pending";

        public void Next(OrderContext context)
        {
            context.State = new ConfirmedState();
        }

        public void Cancel(OrderContext context)
        {
            context.State = new CancelledState();
        }
    }

    public class ConfirmedState : IOrderState
    {
        public string Status => "Confirmed";

        public void Next(OrderContext context)
        {
            context.State = new ShippedState();
        }

        public void Cancel(OrderContext context)
        {
            context.State = new CancelledState();
        }
    }

    public class ShippedState : IOrderState
    {
        public string Status => "Shipped";

        public void Next(OrderContext context)
        {
            context.State = new DeliveredState();
        }

        public void Cancel(OrderContext context)
        {
            throw new InvalidOperationException("Cannot cancel a shipped order.");
        }
    }

    public class DeliveredState : IOrderState
    {
        public string Status => "Delivered";

        public void Next(OrderContext context)
        {
            throw new InvalidOperationException("Order already delivered.");
        }

        public void Cancel(OrderContext context)
        {
            throw new InvalidOperationException("Cannot cancel a delivered order.");
        }
    }

    public class CancelledState : IOrderState
    {
        public string Status => "Cancelled";

        public void Next(OrderContext context)
        {
            throw new InvalidOperationException("Cannot progress a cancelled order.");
        }

        public void Cancel(OrderContext context)
        {
            throw new InvalidOperationException("Order is already cancelled.");
        }
    }
}
