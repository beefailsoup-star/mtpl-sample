export interface AuthUser {
  id: string;
  email: string;
  roles: string[];
  permissions: string[];
}

export type AuthGuardResult = { allowed: true; user: AuthUser } | { allowed: false; reason: string };

export function hasRole(user: AuthUser, requiredRoles: string[]): boolean {
  return requiredRoles.some((role) => user.roles.includes(role));
}

export function hasPermission(user: AuthUser, requiredPermissions: string[]): boolean {
  return requiredPermissions.every((perm) => user.permissions.includes(perm));
}

export function authorize(
  user: AuthUser | null,
  options: { roles?: string[]; permissions?: string[] }
): AuthGuardResult {
  if (!user) return { allowed: false, reason: "Not authenticated" };
  if (options.roles?.length && !hasRole(user, options.roles)) {
    return { allowed: false, reason: "Insufficient roles" };
  }
  if (options.permissions?.length && !hasPermission(user, options.permissions)) {
    return { allowed: false, reason: "Insufficient permissions" };
  }
  return