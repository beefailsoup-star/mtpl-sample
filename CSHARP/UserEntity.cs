using System;
using System.Collections.Generic;
using System.Text.RegularExpressions;

namespace MtplSample
{
    public class UserEntity
    {
        private string _email;
        private string _password;

        public Guid Id { get; private set; } = Guid.NewGuid();
        public string Username { get; set; }
        public DateTime CreatedAt { get; private set; } = DateTime.UtcNow;
        public bool IsActive { get; set; } = true;

        public string Email
        {
            get => _email;
            set
            {
                if (!IsValidEmail(value))
                    throw new ArgumentException("Invalid email format.");
                _email = value;
            }
        }

        public string Password
        {
            set
            {
                if (string.IsNullOrWhiteSpace(value) || value.Length < 8)
                    throw new ArgumentException("Password must be at least 8 characters.");
                _password = value;
            }
        }

        public List<string> Roles { get; } = new();

        public void AssignRole(string role)
        {
            if (!Roles.Contains(role))
                Roles.Add(role);
        }

        public bool HasRole(string role) => Roles.Contains(role);

        private static bool IsValidEmail(string email)
        {
            if (string.IsNullOrWhiteSpace(email)) return false;
            return Regex.IsMatch(email, @"^[^@\s]+@[^@\s]+\.[^@\s]+$", RegexOptions.IgnoreCase);
        }
    }
}
