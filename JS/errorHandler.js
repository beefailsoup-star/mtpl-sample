class AppError extends Error {
  constructor(message, statusCode = 500, code = 'INTERNAL_ERROR') {
    super(message);
    this.name = this.constructor.name;
    this.statusCode = statusCode;
    this.code = code;
    Error.captureStackTrace(this, this.constructor);
  }
}

class ValidationError extends AppError {
  constructor(message = 'Validation failed', errors = []) {
    super(message, 400, 'VALIDATION_ERROR');
    this.errors = errors;
  }
}

class NotFoundError extends AppError {
  constructor(message = 'Resource not found') {
    super(message, 404, 'NOT_FOUND');
  }
}

class AuthError extends AppError {
  constructor(message = 'Authentication failed') {
    super(message, 401, 'AUTH_ERROR');
  }
}

function handleError(err) {
  if (err instanceof AppError) {
    return {
      success: false,
      error: {
        message: err.message,
        code: err.code,
        statusCode: err.statusCode,
        ...(err.errors && { errors: err.errors })
      }
    };
  }
  return {
    success: false,
    error: {
      message: err.message || 'Internal server error',
      code: 'INTERNAL_ERROR',
      statusCode: 500
    }
  };
}

module.exports = { AppError, ValidationError, NotFoundError, AuthError, handleError };
