using System;
using System.Collections.Generic;

namespace MtplSample
{
    public interface IShippingStrategy
    {
        string Name { get; }
        decimal CalculateCost(double weight, double distance);
    }

    public class StandardShipping : IShippingStrategy
    {
        public string Name => "Standard";

        public decimal CalculateCost(double weight, double distance)
        {
            return (decimal)(weight * 0.5 + distance * 0.1);
        }
    }

    public class ExpressShipping : IShippingStrategy
    {
        public string Name => "Express";

        public decimal CalculateCost(double weight, double distance)
        {
            return (decimal)(weight * 1.0 + distance * 0.3) + 10;
        }
    }

    public class OvernightShipping : IShippingStrategy
    {
        public string Name => "Overnight";

        public decimal CalculateCost(double weight, double distance)
        {
            return (decimal)(weight * 2.0 + distance * 0.5) + 25;
        }
    }

    public class StrategyResolver
    {
        private readonly Dictionary<string, IShippingStrategy> _strategies = new();

        public StrategyResolver()
        {
            Register(new StandardShipping());
            Register(new ExpressShipping());
            Register(new OvernightShipping());
        }

        public void Register(IShippingStrategy strategy)
        {
            _strategies[strategy.Name.ToLowerInvariant()] = strategy;
        }

        public IShippingStrategy Resolve(string name)
        {
            if (_strategies.TryGetValue(name.ToLowerInvariant(), out var strategy))
                return strategy;
            throw new ArgumentException($"Unknown shipping strategy: {name}");
        }

        public decimal Calculate(string strategyName, double weight, double distance)
        {
            var strategy = Resolve(strategyName);
            return strategy.CalculateCost(weight, distance);
        }
    }
}
