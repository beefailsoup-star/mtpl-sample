type Listener<T = any> = (payload: T) => void;

interface EventMap {
  [event: string]: Listener[];
}

export class EventBus {
  private events: EventMap = {};

  on<T = any>(event: string, listener: Listener<T>): void {
    if (!this.events[event]) this.events[event] = [];
    this.events[event].push(listener as Listener);
  }

  off<T = any>(event: string, listener: Listener<T>): void {
    if (!this.events[event]) return;
    this.events[event] = this.events[event].filter(l => l !== listener);
  }

  emit<T = any>(event: string, payload: T): void {
    if (!this.events[event]) return;
    for (const listener of this.events[event]) {
      listener(payload);
    }
  }

  once<T = any>(event: string, listener: Listener<T>): void {
    const wrapper = (payload: T) => {
      listener(payload);