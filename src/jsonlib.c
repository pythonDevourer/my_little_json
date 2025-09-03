#include <stdio.h>
#include "jsonlib.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

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
    
}




void json_dump(JSON *json_file, char *content) {

    FILE *fp = open_json(json_file);
   
    fprintf(fp, content);

}


FILE *open_json(JSON *json_file) {
    
    char *dir = get_dir(json_file->path);
    mkdir(dir, 0777);
    free(dir);

    FILE *fp = fopen(json_file->path, "w");
    if (!fp) {
        perror("failed to open file");
        return NULL;
    }
    return fp;
}