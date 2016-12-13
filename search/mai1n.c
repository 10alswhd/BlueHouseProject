#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

#include <smartslog.h>

static void handler(sslog_subscription_t* sub) {
}

static void subscribe_request(sslog_node_t* node) {
    sslog_subscription_t* sub = sslog_new_subscription(node, true);
    sslog_sbcr_set_changed_handler(sub, &handler);

    sslog_triple_t* triple = sslog_new_triple_detached("subject", "predicate", SSLOG_TRIPLE_ANY, SSLOG_RDF_TYPE_URI, SSLOG_RDF_TYPE_LIT);
    sslog_sbcr_add_triple_template(sub, triple);

    if (sslog_sbcr_subscribe(sub) != SSLOG_ERROR_NO) {
        fprintf(stderr, "Can't subscribe\n");
    }
}

int main(void) {
    sslog_init();

    sslog_node_t* node = sslog_new_node("cpu_consumer_kp", "X", "127.0.0.1", 10010);
    if (sslog_node_join(node) != SSLOG_ERROR_NO) {
        fprintf(stderr, "Can't join node\n");
        return 1;
    }

    subscribe_request(node);
    sleep(10);

    sslog_node_leave(node);
    sslog_shutdown();
}
