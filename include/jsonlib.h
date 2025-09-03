#ifndef JSONLIB_H
#define JSONLIB_H


typedef enum {
    JSON_TYPE_ARRAY,
    JSON_TYPE_OBJECT
} JSONType;

typedef struct json_struct {
    JSONType type;
    int buffersize;
    char *path;
    char *content;
} JSON;


FILE *open_json(JSON *json_file, char *mode);
void json_dump(JSON *json_file, char *content);
void json_load(JSON *json_file);
char *get_dir(char *path);

#endif