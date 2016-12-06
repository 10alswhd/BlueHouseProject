#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <tevent.h>
#include <talloc.h>
#include <param.h>
#include <ldb.h>
#include <dcerpc.h>
#include <samba/session.h>

#define REMOTE_HOST "192.168.56.12"

struct ldb_context	*samdb_connect_url(TALLOC_CTX *, struct tevent_context *, struct loadparm_context *, struct auth_session_info *, unsigned int, const char *);

int main(void) {
	TALLOC_CTX			*mem_ctx;
	struct tevent_context		*ev_ctx;
	struct loadparm_context		*lp_ctx;
	const char			*url;
	int				ret;
	struct ldb_context 		*ldb_ctx;
	struct ldb_result		*res;
	struct auth_session_info 	*session_info;

	mem_ctx = talloc_autofree_context();
	ev_ctx = tevent_context_init(mem_ctx);
	lp_ctx = loadparm_init_global(true);
	session_info = system_session(lp_ctx);
	url = "ldap://" REMOTE_HOST;

	ldb_ctx = samdb_connect_url(mem_ctx, ev_ctx, lp_ctx, session_info,
	                            LDB_FLG_RECONNECT, url);

	while (true) {
		printf("Searching...\n");
		ret = ldb_search(ldb_ctx, mem_ctx, &res,
				 ldb_get_default_basedn(ldb_ctx),
				 LDB_SCOPE_SUBTREE, NULL, "(cn=*)");

		if (ret != LDB_SUCCESS) {
			printf("ldb_search failed (%s): %s\n", 
			       ldb_strerror(ret), ldb_errstring(ldb_ctx));
			break;
		}

		printf("%d results\n", res->count);
		system("ssh root@" REMOTE_HOST " service samba-ad-dc restart");
		sleep(10);
	}

	talloc_free(mem_ctx);
	return 0;
}
