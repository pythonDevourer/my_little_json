#include <stdio.h>
#include "jsonlib.h"
#include <stdlib.h>

JSON testjson = {
    .buffer = 1024,
    .path = "test/test.json"
};

int main() {

    json_dump(&testjson, "{ \"name\": \"he\" }");

    return 0;
}