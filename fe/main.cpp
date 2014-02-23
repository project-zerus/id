#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

#include "essence/libevhtp/evhtp.h"

void ping_cb(evhtp_request_t* req, void* a) {
  const char* str = "pong\n";
  evbuffer_add_printf(req->buffer_out, "%s", str);
  evhtp_send_reply(req, EVHTP_RES_OK);
}

int main(int argc, char ** argv) {
  evbase_t * evbase = event_base_new();
  evhtp_t  * htp    = evhtp_new(evbase, NULL);

  evhtp_set_cb(htp, "/ping", ping_cb, NULL);
  evhtp_use_threads(htp, NULL, 8, NULL);

  evhtp_bind_socket(htp, "0.0.0.0", 8081, 32768);

  event_base_loop(evbase, 0);

  evhtp_unbind_socket(htp);

  evhtp_free(htp);
  event_base_free(evbase);

  return 0;
}
