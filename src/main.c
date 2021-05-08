#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "peppapeg.h"
#include "lang-json.h"

static char* readFile(const char* path) {
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
        P4_Error    err         = P4_InternalError;
        char*       json_input  = readFile(path);

        if (json_input)
            err = ToastParseJson(json_input);

        free(json_input);
        return err;
    }

    fprintf(stderr, "unknown lang: %s\n", lang);
}
