using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;

namespace MtplSample
{
    public abstract class ValidatorBase<T>
    {
        private readonly List<ValidationRule> _rules = new();

        protected void AddRule(Expression<Func<T, object>> property, Func<T, bool> predicate, string errorMessage)
        {
            _rules.Add(new ValidationRule
            {
                PropertyName = GetPropertyName(property),
                Predicate = predicate,
                ErrorMessage = errorMessage
            });
        }

        public ValidationResult Validate(T entity)
        {
            var errors = new List<ValidationError>();

            foreach (var rule in _rules)
            {
                if (!rule.Predicate(entity))
                {
                    errors.Add(new ValidationError
                    {
                        PropertyName = rule.PropertyName,
                        Message = rule.ErrorMessage
                    });
                }
            }

            return new ValidationResult { IsValid = !errors.Any(), Errors = errors };
        }

        private static string GetPropertyName(Expression<Func<T, object>> expression)
        {
            return expression.Body switch
            {
                MemberExpression m => m.Member.Name,
                UnaryExpression { Operand: MemberExpression m } => m.Member.Name,
                _ => throw new InvalidOperationException("Invalid expression")
            };
        }

        private class ValidationRule
        {
            public string PropertyName { get; set; }
            public Func<T, bool> Predicate { get; set; }
            public string ErrorMessage { get; set; }
        }
    }

    public class ValidationResult
    {
        public bool IsValid { get; set; }
        public List<ValidationError> Errors { get; set; } = new();
        public string ErrorSummary => string.Join("; ", Errors.Select(e => $"{e.PropertyName}: {e.Message}"));
    }

    public class ValidationError
    {
        public string PropertyName { get; set; }
        public string Message { get; set; }
    }
}
