#include <string.h>

const char* tyext_foo_call_v1(const char* op, const char* payload) {
  if (op && strcmp(op, "foo.echo") == 0) {
    return payload;
  }
  if (op && strcmp(op, "foo.ping") == 0) {
    return "pong";
  }
  return "<none>";
}
