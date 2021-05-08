# ifndef TOAST_LANG_Json_H
# define TOAST_LANG_Json_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "peppapeg.h"

typedef enum {
    ToastJsonEntry        = 1,
    ToastJsonValue,
    ToastJsonObject,
    ToastJsonObjectItem,
    ToastJsonArray,
    ToastJsonString,
    ToastJsonTrue,
    ToastJsonFalse,
    ToastJsonNull,
    ToastJsonNumber,
    ToastJsonEscape,
    ToastJsonUnicodeEscape,
    ToastJsonMinus,
    ToastJsonPlus,
    ToastJsonIntegral,
    ToastJsonFractional,
    ToastJsonExponent,
    ToastJsonWhitespace,
} ToastJsonRuleID;

P4_Grammar*  ToastLoadJsonGrammar() {
    return P4_LoadGrammar(
        "@lifted\n"
        "entry = &. value !.;\n"

        "@lifted\n"
        "value = object / array / string / number / true / false / null;\n"

        "object = \"{\" (item (\",\" item)*)? \"}\";\n"
        "item = string \":\" value;\n"

        "array = \"[\" (value (\",\" value)*)? \"]\";\n"

        "@tight\n"
        "string = \"\\\"\" ([\\u{20}-\\u{21}] / [\\u{23}-\\u{5b}] / [\\u{5d}-\\u{10ffff}] / escape )* \"\\\"\";\n"

        "true = \"true\";\n"
        "false = \"false\";\n"
        "null = \"null\";\n"

        "@tight @squashed\n"
        "number = minus? integral fractional? exponent?;\n"

        "@tight @squashed @lifted\n"
        "escape = \"\\\\\" (\"\\\"\" / \"/\" / \"\\\\\" / \"b\" / \"f\" / \"n\" / \"r\" / \"t\" / unicode);\n"

        "@tight @squashed"
        "unicode = \"u\" ([0-9] / [a-f] / [A-F]){4};\n"

        "minus = \"-\";\n"
        "plus = \"+\";\n"

        "@squashed @tight\n"
        "integral = \"0\" / [1-9] [0-9]*;\n"

        "@squashed @tight\n"
        "fractional = \".\" [0-9]+;\n"

        "@tight"
        "exponent = i\"e\" (plus / minus)? [0-9]+;\n"

        "@spaced @lifted\n"
        "whitespace = \" \" / \"\\r\" / \"\\n\" / \"\\t\";\n"
    );
}

P4_Error ToastParseJson(char* input) {
    P4_Error err = P4_Ok;
    P4_Grammar* json_grammar = NULL;
    P4_Source* json_source = NULL;
    P4_Token* json_root = NULL;

    json_grammar = ToastLoadJsonGrammar();
    if (json_grammar == NULL) {
        err = P4_MemoryError;
        fprintf(stderr, "failed to create json grammar.\n");
        goto finalize;
    }

    json_source = P4_CreateSource(input, ToastJsonEntry);
    if (json_source == NULL) {
        err = P4_MemoryError;
        fprintf(stderr, "failed to create json source.\n");
        goto finalize;
    }

    if ((err = P4_Parse(json_grammar, json_source)) != P4_Ok) {
        fprintf(stderr, "failed to parse json: %s.\n", P4_GetErrorMessage(json_source));
        goto finalize;
    }

    json_root = P4_GetSourceAst(json_source);
    if (json_root == NULL) {
        err = P4_ValueError;
        fprintf(stderr, "failed to get json parse tree root.\n");
        goto finalize;
    }

    P4_JsonifySourceAst(json_grammar, stdout, json_root);

finalize:

    if (json_source) P4_DeleteSource(json_source);
    if (json_grammar) P4_DeleteGrammar(json_grammar);

    return err;
}

#ifdef __cplusplus
}
#endif

# endif
