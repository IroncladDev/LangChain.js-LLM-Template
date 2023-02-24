export type InputValues = Record<string, any>;
export type OutputValues = Record<string, any>;
export type MemoryVariables = Record<string, any>;
export declare abstract class BaseMemory {
    abstract loadMemoryVariables(values: InputValues): Promise<MemoryVariables>;
    abstract saveContext(inputValues: InputValues, OutputValues: Promise<OutputValues>): Promise<void>;
}
