# ifndef TOAST_LANG_ES6_H
# define TOAST_LANG_ES6_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "peppapeg.h"

P4_Grammar*  Toast_LoadES6Grammar() {
    return P4_LoadGrammar(
        "PrimaryExpression = Literal / RegularExpressionLiteral;\n"
        "Literal = ((NullLiteral / BooleanLiteral / NumericLiteral) !(IdentifierStart / IdentifierPart)) / StringLiteral;\n"
        "@lifted CommonToken = IdentifierName / Punctuator / NumericLiteral / StringLiteral / Template;\n"
        "@squashed @tight IdentifierName = IdentifierStart IdentifierPart*;\n"
        "@squashed IdentifierStart = UnicodeIDStart / \"$\" / \"_\" / (\"\\\\\" UnicodeEscapeSequence);\n"
        "@squashed IdentifierPart = UnicodeIDContinue / \"$\" / \"_\" / (\"\\\\\" UnicodeEscapeSequence) / \"\\u{200C}\" / \"\\u{200D}\";\n"
        "UnicodeIDStart = ID_Start / Other_ID_Start;\n"
        "UnicodeIDContinue = ID_Continue / Other_ID_Continue / Other_ID_Start;\n"
        "ID_Start = [\\u{0041}-\\u{005a}] / [\\u{0061}-\\u{007a}] / \"\\u{00aa}\" / \"\\u{00b5}\" / \"\\u{00ba}\" / [\\u{00c0}-\\u{00d6}] / [\\u{00d8}-\\u{00f6}];\n"
        "Other_ID_Start = \"\\u{2118}\" / \"\\u{212e}\" / [\\u{309b}-\\u{309c}];\n"
        "ID_Continue = [\\u{0030}-\\u{0039}] / [\\u{0041}-\\u{005a}] / \"\\u{005f}\" / [\\u{0061}-\\u{007a}] / \"\\u{00aa}\" / \"\\u{00b5}\" / \"\\u{00b7}\" / \"\\u{00ba}\" / [\\u{00c0}-\\u{00d6}] / [\\u{00d8}-\\u{00f6}];\n"
        "Other_ID_Continue = \"\\u{1369}\" / \"\\u{00B7}\" / \"\\u{0387}\" / \"\\u{19DA}\";\n"
        "Punctuator = \"{\" / \"}\" / \"(\" / \")\" / \"[\" / \"]\" / \".\" / \";\" / \",\" / \"<=\" / \">=\" / \"<\" / \">\" / \"===\" / \"!==\" / \"==\" / \"!=\" / \"++\" / \"--\" / \"*=\" / \"*\" / \"%=\" / \"%\" / \"+=\" / \"+\" / \"-=\" / \"-\" / \"<<=\" / \"<<\" / \">>>=\" / \">>>\" / \">>=\" / \">>\" / \"&&\" / \"||\" / \"^=\" / \"^\" / \"!\" / \"~\" / \"&=\" / \"&\" / \"|=\" / \"|\" / \"?\" / \":\" / \"=>\" / \"=\";\n"
        "@squashed StringLiteral = (\"\\\"\" DoubleStringCharacters? \"\\\"\") / (\"'\" SingleStringCharacters? \"'\");\n"
        "DoubleStringCharacters = DoubleStringCharacter+;\n"
        "SingleStringCharacters = SingleStringCharacter+;\n"
        "@squashed DoubleStringCharacter = (!(\"\\\"\" / \"\\\\\" / LineTerminator) SourceCharacter) / (\"\\\\\" EscapeSequence) / LineContinuation;\n"
        "@squashed SingleStringCharacter = (!(\"'\" / \"\\\\\" / LineTerminator) SourceCharacter) / (\"\\\\\" EscapeSequence) / LineContinuation;\n"
        "LineContinuation = \"\\\\\" LineTerminatorSequence;\n"
        "EscapeSequence = (CharacterEscapeSequence / (\"0\" !DecimalDigit)) / HexEscapeSequence / UnicodeEscapeSequence;\n"
        "CharacterEscapeSequence = SingleEscapeCharacter / NonEscapeCharacter;\n"
        "SingleEscapeCharacter =  \"'\" / \"\\\"\" / \"\\\\\" / \"b\" / \"f\" / \"n\" / \"r\" / \"t\" / \"v\";\n"
        "NonEscapeCharacter = !(EscapeCharacter / LineTerminator) SourceCharacter;\n"
        "SourceCharacter = [\\u{0001}-\\u{FFFC}]; # 0000-FFFC? \n"
        "EscapeCharacter = SingleEscapeCharacter / DecimalDigit / \"x\" / \"u\";\n"
        "HexEscapeSequence = \"x\" HexDigit HexDigit;\n"
        "UnicodeEscapeSequence = \"u\" HexDigit{4} / \"u{\" HexDigit{4} \"}\";\n"
        "NullLiteral = \"null\";\n"
        "BooleanLiteral = \"true\" / \"false\";\n"
        "@squashed NumericLiteral = HexIntegerLiteral / BinaryIntegerLiteral / OctalIntegerLiteral / DecimalLiteral ;\n"
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
        "Template = NoSubstitutionTemplate / TemplateHead;"
        "@lifted NoSubstitutionTemplate = \"\\u{0060}\" TemplateCharacters? \"\\u{0060}\";\n"
        "TemplateHead = \"\\u{0060}\" TemplateCharacters? \"${\";\n"
        "@nonterminal TemplateSubstitutionTail = TemplateMiddle / TemplateTail;\n"
        "TemplateMiddle = \"}\" TemplateCharacters? \"${\";\n"
        "TemplateTail = \"}\" TemplateCharacters? \"\\u{0060}\";\n"
        "@squashed TemplateCharacters = TemplateCharacter+;\n"
        "TemplateCharacter = (\"$\" !\"{\") / (\"\\\\\" EscapeSequence) / LineContinuation / LineTerminatorSequence / (!(\"\\u{0060}\" / \"\\\\\" / \"$\" / LineTerminator) SourceCharacter);\n"
        "RegularExpressionLiteral = \"/\" RegularExpressionBody \"/\" RegularExpressionFlags;\n"
        "@squashed RegularExpressionBody = RegularExpressionFirstChar RegularExpressionChars;\n"
        "RegularExpressionChars = RegularExpressionChar*;\n"
        "RegularExpressionFirstChar = (!(\"*\" / \"\\\\\" / \"/\" / \"[\") RegularExpressionNonTerminator) / RegularExpressionBackslashSequence / RegularExpressionClass;\n"
        "RegularExpressionChar = (!(\"\\\\\" / \"/\" / \"[\") RegularExpressionNonTerminator) / RegularExpressionBackslashSequence / RegularExpressionClass;\n"
        "RegularExpressionBackslashSequence = \"\\\\\" RegularExpressionNonTerminator;\n"
        "RegularExpressionNonTerminator = !LineTerminator SourceCharacter;\n"
        "RegularExpressionClass = \"[\" RegularExpressionClassChars \"]\";\n"
        "RegularExpressionClassChars = RegularExpressionClassChar*;\n"
        "RegularExpressionClassChar = (!(\"]\" / \"\\\\\") RegularExpressionNonTerminator) / RegularExpressionBackslashSequence;\n"
        "RegularExpressionFlags = IdentifierPart*;\n"

        "WhiteSpace = \"\\u{0009}\" / \"\\u{000B}\" / \"\\u{000C}\" / \"\\u{0020}\" / \"\\u{00A0}\" / \"\\u{FEFF}\" / [\\u{02B0}-\\u{02FF}];\n"
        "LineTerminator = \"\\u{000A}\" / \"\\u{000D}\" / \"\\u{2028}\" / \"\\u{2029}\";\n"
        "LineTerminatorSequence = \"\\u{000A}\" / (\"\\u{000D}\" !\"\\u{000A}\") / \"\\u{2028}\" / \"\\u{2029}\" / (\"\\u{000D}\\u{000A}\");\n"
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
