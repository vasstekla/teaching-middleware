#include <stdio.h>

#include <zmq.hpp>

int main () {

    // Context with single thread.
    zmq::context_t context (1);

    // Socket of subscriber type in publish-subscribe pattern.
    zmq::socket_t subscriber (context, ZMQ_SUB);

    // Connect to one of the available transports.
    // subscriber.connect ("ipc://example");
    subscriber.connect ("tcp://localhost:8888");

    // Set an accept-all filter on the subscription.
    // The default filter is discard-all.
    subscriber.setsockopt (ZMQ_SUBSCRIBE, NULL, 0);

    while (true) {

        zmq::message_t message;

        subscriber.recv (&message);
        printf ("Message: %s\n", (char *) message.data ());

        // Note the message is deallocated here.
    }
}
