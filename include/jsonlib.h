#ifndef JSONLIB_H
#define JSONLIB_H


typedef struct json_struct {
    int buffersize;
    char *path;
    char *content;
} JSON;


FILE *open_json(JSON *json_file, char *mode);
void json_dump(JSON *json_file, char *content);
void json_load(JSON *json_file);
char *get_dir(char *path);

#endif