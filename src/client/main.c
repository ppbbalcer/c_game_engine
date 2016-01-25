#include "render.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
void alloc_cb(uv_handle_t* handle, size_t size, uv_buf_t *buf) {
	*buf = uv_buf_init(malloc(size), size);
}


void on_read(uv_stream_t* tcp, ssize_t nread, const uv_buf_t *buf) {
	if (nread >= 0) {
		//printf("read: %s\n", tcp->data);
		printf("read: %s\n", buf->base);
	}
	else {
		//we got an EOF
		uv_close((uv_handle_t *) tcp, NULL);
	}

	//cargo-culted
	free(buf->base);
}

void on_connect(uv_connect_t *req, int status)
{
	uv_buf_t b;
	b.base = "HEYA";
	b.len = 5;
	uv_write_t req1;

	uv_write(&req1, req->handle, &b, 1, NULL);
	uv_read_start(req->handle, alloc_cb, on_read);
}

uv_loop_t *loop;*/


int
main()
{
	render_start();
	struct scene *s = object_create(OBJECT_SCENE_MENU, NULL, NULL);
	scene_set_current(s);

	render_do();
	render_stop();

	object_destroy(s);

	return 0;
	/*uv_tcp_t s;
	uv_connect_t c;

	loop = uv_default_loop();

	uv_tcp_init(loop, &s);
	uv_tcp_keepalive(&s, 1, 60);

	struct sockaddr_in dest;
	uv_ip4_addr("127.0.0.1", 8900, &dest);
	uv_tcp_connect(&c, &s, (const struct sockaddr *)&dest, on_connect);

	return uv_run(loop, UV_RUN_DEFAULT);*/
}
