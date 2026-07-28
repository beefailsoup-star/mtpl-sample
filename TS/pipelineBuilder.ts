export type StageFn<T, R> = (input: T) => R | Promise<R>

export class PipelineBuilder<T, R = T> {
  private stages: StageFn<any, any>[] = []

  addStage<U>(stage: StageFn<R, U>): PipelineBuilder<T, U> {
    this.stages.push(stage)
    return this as any as PipelineBuilder<T, U>
  }

  async execute(input: T): Promise<R> {
    let result: any = input
    for (const stage of this.stages) {
      result = await Promise.resolve(stage(result))
    }
    return result as R
  }
}

export function pipeline<T>(): PipelineBuilder<T, T> {
  return new PipelineBuilder<T, T>()
}
