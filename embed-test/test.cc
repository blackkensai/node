// #include "node.h"
#include "node_api.h"
#include "node-embed.h"

int main(int argc, char **argv) {
    // using namespace node;
    node_embed_execute("test.js");
    return 0;
}