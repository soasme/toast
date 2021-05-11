# ifndef TOAST_LANG_ES6_H
# define TOAST_LANG_ES6_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "peppapeg.h"

P4_Grammar*  Toast_LoadES6Grammar() {
    return P4_LoadGrammar(
        "NullLiteral = \"null\";\n"
        "BooleanLiteral = \"true\" / \"false\";\n"
        "@squashed NumericLiteral = HexIntegerLiteral / BinaryIntegerLiteral / OctalIntegerLiteral / DecimalIntegerLiteral;\n"
        "@squashed @tight DecimalLiteral = (DecimalIntegerLiteral (\".\" DecimalDigits?)? ExponentPart?) / (\".\" DecimalDigits ExponentPart?);\n"
        "DecimalIntegerLiteral = \"0\" / (NonZeroDigit DecimalDigits?);\n"
        "DecimalDigits = DecimalDigit+;\n"
        "DecimalDigit = [0-9];\n"
        "NonZeroDigit = [1-9];\n"
        "ExponentPart = i\"e\" SignedInteger;\n"
        "SignedInteger = (\"+\" / \"-\")? DecimalDigits;\n"
        "@squashed @tight BinaryIntegerLiteral = (\"0b\" / \"0B\") BinaryDigits;\n"
        "@squashed @tight BinaryDigits = BinaryDigit+;\n"
        "BinaryDigit = [0-1];\n"
        "@squashed @tight OctalIntegerLiteral = (\"0o\" / \"0O\") OctalDigits;\n"
        "@squashed @tight OctalDigits = OctalDigit+;\n"
        "OctalDigit = [0-7];\n"
        "@squashed @tight HexIntegerLiteral = (\"0x\" / \"0X\") HexDigits;\n"
        "@squashed @tight HexDigits = HexDigit+;\n"
        "HexDigit = [a-f] / [A-F] / [0-9];\n"
    );
}

P4_Error Toast_ParseES6(char* input) {
    P4_Error err = P4_Ok;
    P4_Grammar* es6_grammar = NULL;
    P4_Source* es6_source = NULL;
    P4_Token* es6_root = NULL;

    es6_grammar = Toast_LoadES6Grammar();
    if (es6_grammar == NULL) {
        err = P4_MemoryError;
        fprintf(stderr, "failed to create es6 grammar.\n");
        goto finalize;
    }

    es6_source = P4_CreateSource(input, 1);
    if (es6_source == NULL) {
        err = P4_MemoryError;
        fprintf(stderr, "failed to create es6 source.\n");
        goto finalize;
    }

    if ((err = P4_Parse(es6_grammar, es6_source)) != P4_Ok) {
        fprintf(stderr, "failed to parse es6: %s.\n", P4_GetErrorMessage(es6_source));
        goto finalize;
    }

    es6_root = P4_GetSourceAst(es6_source);
    if (es6_root == NULL) {
        err = P4_ValueError;
        fprintf(stderr, "failed to get es6 parse tree root.\n");
        goto finalize;
    }

    P4_JsonifySourceAst(es6_grammar, stdout, es6_root);

finalize:

    if (es6_source) P4_DeleteSource(es6_source);
    if (es6_grammar) P4_DeleteGrammar(es6_grammar);

    return err;
}

#ifdef __cplusplus
}
#endif

# endif
