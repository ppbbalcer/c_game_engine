#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>

#define SERVER_PORT 8900

uv_loop_t *loop;
uv_tcp_t client;

void alloc_buffer(uv_handle_t *h, size_t suggested_size, uv_buf_t *buf)
{
	buf->base = malloc(suggested_size);
	buf->len = suggested_size;
}

void echo_read(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf)
{
	printf("in: %s\n", buf->base);
	uv_write_t req;
	uv_buf_t b;
	b.base = "ROTFL";
	b.len = 6;
	uv_write(&req, stream, &b, 1, NULL);
}

void on_new_connection(uv_stream_t *server, int status)
{
	uv_tcp_init(loop, &client);
	if (uv_accept(server, (uv_stream_t*)&client) == 0) {
		uv_read_start((uv_stream_t*)&client, alloc_buffer, echo_read);
	} else {
		uv_close((uv_handle_t*)&client, NULL);
	}
}

int main()
{
	loop = uv_default_loop();

	uv_tcp_t server;
	uv_tcp_init(loop, &server);

	struct sockaddr_in addr;
	uv_ip4_addr("0.0.0.0", SERVER_PORT, &addr);
	uv_tcp_bind(&server, (const struct sockaddr*)&addr, 0);
	int r = uv_listen((uv_stream_t*)&server, 10, on_new_connection);
	if (r) {
		return 1;
	}

	return uv_run(loop, UV_RUN_DEFAULT);
}
