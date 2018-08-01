// #include "uv.h"
// #include "v8.h"
// #include "node.h"


// extern int v8_thread_pool_size;
extern void _register_embedtest();
extern void _register_android();
// extern void PlatformInit();
using namespace node;

NODE_EXTERN int node_embed_execute(const char * script) {
  // atexit([]() { uv_tty_reset_mode(); });
  int argc = 2;
  const char ** argv = new const char*[2];
  argv[0] = "node";
  argv[1] = script;
  PlatformInit();
  // node::performance::performance_node_start = PERFORMANCE_NOW();

  // This needs to run *before* V8::Initialize().  The const_cast is not
  // optional, in case you're wondering.
  int exec_argc;
  const char** exec_argv;
  Init(&argc, const_cast<const char**>(argv), &exec_argc, &exec_argv);

  // TODO init modules here.
#define V(modname) _register_##modname();
  V(embedtest);
  V(android);
#undef V
  // _register_atest();

  v8_platform.Initialize(v8_thread_pool_size, uv_default_loop());
  V8::Initialize();
  // performance::performance_v8_start = PERFORMANCE_NOW();
  v8_initialized = true;
  const int exit_code =
      Start(uv_default_loop(), argc, argv, exec_argc, exec_argv);
  v8_initialized = false;
  V8::Dispose();

  // uv_run cannot be called from the time before the beforeExit callback
  // runs until the program exits unless the event loop has any referenced
  // handles after beforeExit terminates. This prevents unrefed timers
  // that happen to terminate during shutdown from being run unsafely.
  // Since uv_run cannot be called, uv_async handles held by the platform
  // will never be fully cleaned up.
  v8_platform.Dispose();

  delete[] exec_argv;
  exec_argv = nullptr;

  return exit_code;
}