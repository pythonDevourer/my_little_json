#ifndef JSONLIB_H
#define JSONLIB_H


typedef struct json_struct {
    int buffer;
    char *path;
} JSON;


FILE *open_json(JSON *json_file);
void json_dump(JSON *json_file, char *content);
char *get_dir(char *path);

#endif