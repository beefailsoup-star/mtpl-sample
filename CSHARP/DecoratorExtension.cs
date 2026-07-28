using System;

namespace MtplSample
{
    public interface ICoffee
    {
        string GetDescription();
        double GetCost();
    }

    public class Espresso : ICoffee
    {
        public string GetDescription() => "Espresso";
        public double GetCost() => 2.50;
    }

    public abstract class CoffeeDecorator : ICoffee
    {
        protected readonly ICoffee _coffee;

        protected CoffeeDecorator(ICoffee coffee)
        {
            _coffee = coffee;
        }

        public virtual string GetDescription() => _coffee.GetDescription();
        public virtual double GetCost() => _coffee.GetCost();
    }

    public class MilkDecorator : CoffeeDecorator
    {
        public MilkDecorator(ICoffee coffee) : base(coffee) { }

        public override string GetDescription() => $"{_coffee.GetDescription()}, Milk";
        public override double GetCost() => _coffee.GetCost() + 0.50;
    }

    public class SugarDecorator : CoffeeDecorator
    {
        public SugarDecorator(ICoffee coffee) : base(coffee) { }

        public override string GetDescription() => $"{_coffee.GetDescription()}, Sugar";
        public override double GetCost() => _coffee.GetCost() + 0.25;
    }

    public class WhippedCreamDecorator : CoffeeDecorator
    {
        public WhippedCreamDecorator(ICoffee coffee) : base(coffee) { }

        public override string GetDescription() => $"{_coffee.GetDescription()}, Whipped Cream";
        public override double GetCost() => _coffee.GetCost() + 0.75;
    }

    public static class DecoratorExtensions
    {
        public static ICoffee WithMilk(this ICoffee coffee) => new MilkDecorator(coffee);
        public static ICoffee WithSugar(this ICoffee coffee) => new SugarDecorator(coffee);
        public static ICoffee WithWhippedCream(this ICoffee coffee) => new WhippedCreamDecorator(coffee);
    }
}
