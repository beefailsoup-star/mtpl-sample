using System;
using System.Linq.Expressions;

namespace MtplSample
{
    public interface ISpecification<T>
    {
        bool IsSatisfiedBy(T entity);
        Expression<Func<T, bool>> ToExpression();
    }

    public class Specification<T> : ISpecification<T>
    {
        private readonly Expression<Func<T, bool>> _expression;

        public Specification(Expression<Func<T, bool>> expression)
        {
            _expression = expression ?? throw new ArgumentNullException(nameof(expression));
        }

        public bool IsSatisfiedBy(T entity)
        {
            return _expression.Compile()(entity);
        }

        public Expression<Func<T, bool>> ToExpression()
        {
            return _expression;
        }

        public static Specification<T> operator &(Specification<T> left, Specification<T> right)
        {
            var leftExpr = left.ToExpression();
            var rightExpr = right.ToExpression();
            var param = Expression.Parameter(typeof(T));
            var body = Expression.AndAlso(
                Expression.Invoke(leftExpr, param),
                Expression.Invoke(rightExpr, param)
            );
            return new Specification<T>(Expression.Lambda<Func<T, bool>>(body, param));
        }

        public static Specification<T> operator |(Specification<T> left, Specification<T> right)
        {
            var leftExpr = left.ToExpression();
            var rightExpr = right.ToExpression();
            var param = Expression.Parameter(typeof(T));
            var body = Expression.OrElse(
                Expression.Invoke(leftExpr, param),
                Expression.Invoke(rightExpr, param)
            );
            return new Specification<T>(Expression.Lambda<Func<T, bool>>(body, param));
        }

        public static Specification<T> operator !(Specification<T> spec)
        {
            var expr = spec.ToExpression();
            var body = Expression.Not(expr.Body);
            return new Specification<T>(Expression.Lambda<Func<T, bool>>(body, expr.Parameters));
        }
    }

    public class ProductPriceSpecification : Specification<Product>
    {
        public ProductPriceSpecification(decimal maxPrice)
            : base(p => p.Price <= maxPrice) { }
    }

    public class ProductInStockSpecification : Specification<Product>
    {
        public ProductInStockSpecification()
            : base(p => p.Stock > 0) { }
    }
}
