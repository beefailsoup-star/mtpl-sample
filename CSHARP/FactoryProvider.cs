using System;
using System.Collections.Generic;

namespace MtplSample
{
    public abstract class PaymentProvider
    {
        public abstract string Name { get; }
        public abstract void Process(decimal amount);
    }

    public class StripeProvider : PaymentProvider
    {
        public override string Name => "Stripe";
        public override void Process(decimal amount)
        {
            LoggerService.Instance.LogInfo($"Processing ${amount} via Stripe.");
        }
    }

    public class SquareProvider : PaymentProvider
    {
        public override string Name => "Square";
        public override void Process(decimal amount)
        {
            LoggerService.Instance.LogInfo($"Processing ${amount} via Square.");
        }
    }

    public class PaymentProviderFactory
    {
        private readonly Dictionary<string, Func<PaymentProvider>> _providers = new();

        public PaymentProviderFactory()
        {
            Register("stripe", () => new StripeProvider());
            Register("square", () => new SquareProvider());
        }

        public void Register(string key, Func<PaymentProvider> factory)
        {
            _providers[key.ToLowerInvariant()] = factory;
        }

        public PaymentProvider Create(string key)
        {
            if (_providers.TryGetValue(key.ToLowerInvariant(), out var factory))
                return factory();
            throw new ArgumentException($"Unknown payment provider: {key}");
        }
    }
}
