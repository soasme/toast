#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "peppapeg.h"
#include "lang-json.h"

char* read_file(const char* path) {
    char* buf = NULL;
    FILE* f = fopen (path, "rb");

    if (f == NULL) {
        fprintf(stderr, "failed to open file: %s.\n", path);
        goto finalize;
    }

    fseek(f, 0, SEEK_END);
    long length = ftell(f);
    fseek (f, 0, SEEK_SET);

    buf = calloc(length+2, sizeof(char));

    if (fread(buf, sizeof(char), length, f) != length) {
        fprintf(stderr, "failed to read file: %s.\n", path);
        goto finalize;
    }

    buf[length] = '\0';

finalize:

    if (f)
        fclose(f);

    return buf;
}

int
main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "usage: toast <lang> <path>\n");
        exit(1);
    }

    const char* lang = argv[1];
    const char* path = argv[2];

    if (strcmp(lang, "json") == 0) {
        P4_Error err = P4_Ok;
        char* json_input = NULL;
        P4_Grammar* json_grammar = NULL;
        P4_Source* json_source = NULL;
        P4_Token* json_root = NULL;

        json_grammar = ToastCreateJsonGrammar();
        if (json_grammar == NULL) {
            err = P4_MemoryError;
            fprintf(stderr, "failed to create json grammar.\n");
            goto json_finalize;
        }

        json_input = read_file(path);
        if (json_input == NULL) {
            err = P4_ValueError;
            goto json_finalize;
        }

        json_source = P4_CreateSource(json_input, ToastJsonEntry);
        if (json_source == NULL) {
            err = P4_MemoryError;
            fprintf(stderr, "failed to create json source.\n");
            goto json_finalize;
        }

        if ((err = P4_Parse(json_grammar, json_source)) != P4_Ok) {
            fprintf(stderr, "failed to parse json: %s.\n", P4_GetErrorMessage(json_source));
            goto json_finalize;
        }

        json_root = P4_GetSourceAst(json_source);
        if (json_root == NULL) {
            err = P4_ValueError;
            fprintf(stderr, "failed to get json parse tree root.\n");
            goto json_finalize;
        }

        P4_JsonifySourceAst(json_grammar, stdout, json_root);

json_finalize:

        if (json_input) free(json_input);
        if (json_source) P4_DeleteSource(json_source);
        if (json_grammar) P4_DeleteGrammar(json_grammar);
        return err;
    }

    fprintf(stderr, "unknown lang: %s\n", lang);
}
