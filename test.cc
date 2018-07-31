// #include "node.h"
#include "node_api.h"
int node_embed_execute(const char * script);

int main(int argc, char **argv) {
    // using namespace node;
    node_embed_execute("test.js");
    return 0;
}