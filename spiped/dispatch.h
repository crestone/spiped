#ifndef _CONN_H_
#define _CONN_H_

#include <stdint.h>

/* Opaque structures. */
struct proto_secret;
struct sock_addr;

/**
 * conn_create(s, sas, decr, nofps, K, timeo, callback_dead, cookie):
 * Create a connection with one end at ${s} and the other end connecting to
 * the target addresses ${sas}.  If ${decr} is 0, encrypt the outgoing data;
 * if ${decr} is nonzero, decrypt the outgoing data.  If ${nofps} is non-zero,
 * don't use perfect forward secrecy.  Drop the connection if the handshake or
 * connecting to the target takes more than ${timeo} seconds.  When the
 * connection is dropped, invoke ${callback_dead}(${cookie}).
 */
int conn_create(int, struct sock_addr * const *, int, int,
    const struct proto_secret *, double, int (*)(void *), void *);

/**
 * conn_accept(s, sas, decr, nofps, K, nconn_max, timeo):
 * Start accepting connections on the socket ${s}.  Connect to the target
 * addresses ${sas}.  If ${decr} is 0, encrypt the outgoing connections; if
 * ${decr} is non-zero, decrypt the incoming connections.  Don't accept more
 * than ${nconn_max} connections.  If ${nofps} is non-zero, don't use perfect
 * forward secrecy.  Drop connections if the handshake or connecting to the
 * target takes more than ${timeo} seconds.
 */
int conn_accept(int, struct sock_addr * const *, int, int,
    const struct proto_secret *, size_t, double);

#endif /* !_CONN_H_ */