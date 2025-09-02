#include <stdio.h>
#include "jsonlib.h"

FILE *open_json(char *path) {
    FILE *fp = fopen(&path, "wr+");
    if (!fp) {
        return 1;
    }
    return fp
}