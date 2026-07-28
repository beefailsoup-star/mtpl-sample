export type DeepPartial<T> = T extends object ? { [P in keyof T]?: DeepPartial<T[P]> } : T;

export type DeepReadonly<T> = T extends object ? { readonly [P in keyof T]: DeepReadonly<T[P]> } : T;

export type RequiredKeys<T, K extends keyof T> = Omit<T, K> & { [P in K]-?: T[P] };

export type OptionalKeys<T, K extends keyof T> = Omit<T, K> & { [P in K]?: T[P] };

export type NonFunctionKeys<T> = { [K in keyof T]: T[K] extends (...args: any[]) => any ? never : K }[keyof T];

export type FunctionKeys<T> = { [K in keyof T]: T[K] extends (...args: any[]) =>