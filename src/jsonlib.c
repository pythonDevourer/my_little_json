#include <stdio.h>
#include "jsonlib.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>


char *get_dir(char *path) {
    char *slash_index = strrchr(path, '/');

    if (!slash_index) {
        char *dot = malloc(2);
        strcpy(dot, ".");
        return dot;
    }

    size_t len = slash_index - path;
    char *dir = malloc(len + 1);
    if (!dir) return NULL;

    strncpy(dir, path, len);
    dir[len] = '\0';

    return dir;
}


void json_load(JSON *json_file) {
    FILE *fp = open_json(json_file, "r");
    if (!fp) return;

    fseek(fp, 0, SEEK_END);
    long filesize = ftell(fp);
    rewind(fp);

    size_t readsize = (json_file->buffersize > 0 && json_file->buffersize < filesize)
                        ? json_file->buffersize
                        : filesize;

    json_file->content = malloc(readsize + 1);
    if (!json_file->content) {
        perror("malloc failed");
        fclose(fp);
        return;
    }

    size_t read_bytes = fread(json_file->content, sizeof(char), readsize, fp);
    if (read_bytes != readsize) {
        perror("failed to read bytes");
    }
    json_file->content[read_bytes] = '\0';

    if (json_file->type == JSON_TYPE_UNKNOWN) {
        switch(json_file->content[0]) {
            case '[':
                json_file->type = JSON_TYPE_ARRAY;
                break;
            case '{':
                json_file->type = JSON_TYPE_OBJECT;
                break;
        }
    }
    fclose(fp);
}

void json_dump(JSON *json_file, char *content) {
    FILE *fp = open_json(json_file, "w");
    if (!fp) return;

    json_file->content = content;

    printf("%s", content);
    switch(content[0]) {
        case '[':
            json_file->type = JSON_TYPE_ARRAY;
            break;
        case '{':
            json_file->type = JSON_TYPE_OBJECT;
            break;
        default:
            json_file->type = JSON_TYPE_UNKNOWN;
            break;
    }

    fclose(fp);
}



FILE *open_json(JSON *json_file, char *mode) {
    
    char *dir = get_dir(json_file->path);
    if (mkdir(dir, 0777) && errno != EEXIST) {
        perror("mkdir failed");
        free(dir);
        return NULL;
    }
    free(dir);

    FILE *fp = fopen(json_file->path, mode);
    if (!fp) {
        perror("failed to open file");
        return NULL;
    }
    return fp;
}