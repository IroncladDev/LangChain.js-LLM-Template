export type SerializedOutputParser = SerializedRegexParser | SerializedCommaSeparatedListOutputParser;
/**
 * Class to parse the output of an LLM call.
 */
export declare abstract class BaseOutputParser {
    /**
     * Parse the output of an LLM call.
     *
     * @param text - LLM output to parse.
     * @returns Parsed output.
     */
    abstract parse(text: string): string | string[] | Record<string, string>;
    /**
     * Return the string type key uniquely identifying this class of parser
     */
    _type(): string;
    /**
     * Return a json-like object representing this output parser.
     */
    abstract serialize(): SerializedOutputParser;
    /**
     * Load an output parser from a json-like object describing the parser.
     */
    static deserialize(data: SerializedOutputParser): BaseOutputParser;
}
/**
 * Class to parse the output of an LLM call to a list.
 * @augments BaseOutputParser
 */
export declare abstract class ListOutputParser extends BaseOutputParser {
    abstract parse(text: string): string[];
}
type SerializedCommaSeparatedListOutputParser = {
    _type: "comma_separated_list";
};
/**
 * Class to parse the output of an LLM call as a comma-separated list.
 * @augments ListOutputParser
 */
export declare class CommaSeparatedListOutputParser extends ListOutputParser {
    parse(text: string): string[];
    serialize(): SerializedCommaSeparatedListOutputParser;
    static deserialize(_: SerializedCommaSeparatedListOutputParser): CommaSeparatedListOutputParser;
}
type SerializedRegexParser = {
    _type: "regex_parser";
    regex: string;
    output_keys: string[];
    default_output_key?: string;
};
/**
 * Class to parse the output of an LLM call into a dictionary.
 * @augments BaseOutputParser
 */
export declare class RegexParser extends BaseOutputParser {
    regex: string | RegExp;
    outputKeys: string[];
    defaultOutputKey?: string;
    constructor(regex: string | RegExp, outputKeys: string[], defaultOutputKey?: string);
    _type(): string;
    parse(text: string): Record<string, string>;
    serialize(): {
        _type: "regex_parser";
        regex: string;
        output_keys: string[];
        default_output_key: string | undefined;
    };
    static deserialize(data: SerializedRegexParser): RegexParser;
}
export {};
