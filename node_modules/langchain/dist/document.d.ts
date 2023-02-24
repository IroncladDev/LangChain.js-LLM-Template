export interface DocumentParams {
    pageContent: string;
    metadata: Record<string, any>;
}
/**
 * Interface for interacting with a document.
 */
export declare class Document implements DocumentParams {
    pageContent: string;
    metadata: Record<string, any>;
    constructor(fields?: Partial<DocumentParams>);
}
