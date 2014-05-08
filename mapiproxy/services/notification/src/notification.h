#pragma once

#include <amqp.h>
#include <talloc.h>

#define DEFAULT_CONFIG_FILE "/etc/openchange/notification-service.cfg"

struct context {
	TALLOC_CTX		*mem_ctx;

	amqp_connection_state_t	broker_conn;
	amqp_socket_t		*broker_socket;

	const char	*broker_host;
	int		broker_port;
	const char	*broker_user;
	const char	*broker_pass;
	const char	*broker_vhost;
	const char	*broker_exchange;

	const char	*broker_new_mail_queue;
	const char      *broker_new_mail_routing_key;
	const char	*broker_new_mail_consumer_tag;

	const char 	*mapistore_backends_path;
	const char	*mapistore_backend;
	struct loadparm_context	 	*lp_ctx;
	struct mapistore_context 	*mstore_ctx;
	struct ldb_context		*ocdb_ctx;
};

void notification_register_message(TALLOC_CTX *, const struct context *,
		const char *, const char *, uint32_t);

char *broker_err(TALLOC_CTX *, amqp_rpc_reply_t);
