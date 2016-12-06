#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xbps.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <ctype.h>
#include <sys/time.h>
#include <limits.h>
#include <libgen.h>
#include "arg.h"

char *argv0;

struct sync_data {
	struct xbps_handle *xh;
	xbps_array_t archs;
};

struct xferstat {
	struct timeval start;
	struct timeval last;
};

static int
state_cb(const struct xbps_state_cb_data *xscd, void *arg)
{
	struct sync_data *sdp = arg;

	switch (xscd->state) {
	case XBPS_STATE_REPOSYNC:
		printf("[*] Updating `%s' ...\n", xscd->arg);
		break;
	/* case XBPS_STATE_UNPACK_FAIL: */
	/* case XBPS_STATE_UPDATE_FAIL: */
	/* case XBPS_STATE_CONFIGURE_FAIL: */
	/* case XBPS_STATE_REMOVE_FAIL: */
	/* case XBPS_STATE_VERIFY_FAIL: */
	/* case XBPS_STATE_DOWNLOAD_FAIL: */
	/* case XBPS_STATE_REPOSYNC_FAIL: */
	/* case XBPS_STATE_CONFIG_FILE_FAIL: */
		/* xbps_error_printf("%s\n", xscd->desc); */
		/* break; */
	default:
		xbps_dbg_printf(xscd->xhp, "desc='%s' arg='%s' \n", xscd->desc, xscd->arg);
	}
}

static int
search_repo_cb(struct xbps_repo *repo, void *arg, bool *done)
{
	xbps_array_t allkeys;
	struct sync_data *sd = arg;
	int rv = 0;

	printf("search_repo_cb %s\n", repo->uri);
	if (repo->idx == NULL)
		return 0;

	/* sd->repourl = repo->uri; */
	allkeys = xbps_dictionary_all_keys(repo->idx);
	/* rv = xbps_array_foreach_cb(repo->xhp, allkeys, repo->idx, search_array_cb, sd); */
	printf("allkeys[%d]\n", xbps_array_count(allkeys));
	xbps_object_release(allkeys);
	return rv;
}

static int
update_foreach_arch(struct xbps_handle *xhp, struct sync_data *sdp)
{
	struct xbps_handle *h;
	const char *arch;
	int rv = 0;

	for (unsigned int i = 0; i < xbps_array_count(sdp->archs); i++) {
		xbps_array_get_cstring_nocopy(sdp->archs, i, &arch);
		xhp->target_arch = arch;
		rv = xbps_rpool_foreach(xhp, search_repo_cb, sdp);
		if (rv != 0 && rv != ENOTSUP) {
			fprintf(stderr, "Failed to initialize rpool: %s\n", strerror(rv));
			return rv;
		}
		printf("foo\n");
	}

	printf("bar\n");
	xhp->target_arch = NULL;

	return rv;
	struct xbps
		xbps_array_get_cstring_nocopy(sdp->archs, i, &arch);
		xhp->target_arch = arch;
		if ((rv = xbps_rpool_sync(xhp, NULL)) != 0)
			printf("hmm?\n");
	}

	xhp->target_arch = NULL;

	return rv;
}

void
usage(void)
{
	fprintf(stderr, "usage: %s [-Sf] [-R repotab file] [-r repomap]\n", argv0);
	exit(1);
}

int main(int argc, char **argv)
{
	struct xbps_handle xh;
	struct xferstat xfer;
	struct sync_data sd;
	const char *rootdir, *cachedir, *confdir, *metadir;
	char *p, cwd[PATH_MAX-1];
	bool sync, update, force, dryrun, debug, verbose;
	int rv;

	rootdir = cachedir = confdir = metadir = NULL;
	sync = update = force = dryrun = debug = verbose = false;
	rv = 0;

	sd.archs = xbps_array_create();

	/* save cwd */
	memset(&cwd, 0, sizeof(cwd));
	p = getcwd(cwd, sizeof(cwd));
	assert(p);

	memset(&xh, 0, sizeof(xh));

	/* command line args */
	ARGBEGIN {
	case 'a':
		xbps_array_add_cstring_nocopy(sd.archs, EARGF(usage()));
		break;
	case 'R':
		xbps_repo_store(&xh, EARGF(usage()));
		break;
	case 'S':
		sync = true;
		break;
	case 'u':
		update = true;
		break;
	case 'f':
		force = true;
		break;
	case 'n':
		dryrun = true;
		break;
	case 'd':
		debug = true;
		break;
	case 'v':
		verbose = true;
		break;
	default:
		usage();
	} ARGEND;

	/*
	 * xbps defaults
	 */
	if (!rootdir)
		rootdir = xbps_xasprintf("%s", cwd);

	if (!cachedir)
		cachedir = xbps_xasprintf("%s/cache", cwd);

	if (!confdir)
		confdir = xbps_xasprintf("%s/conf", cwd);

	if (!metadir)
		metadir = xbps_xasprintf("%s/meta", cwd);

	/*
	 * initialize libxbps
	 */
	xbps_strlcpy(xh.rootdir, rootdir, sizeof(xh.rootdir));
	xbps_strlcpy(xh.cachedir, cachedir, sizeof(xh.cachedir));
	xbps_strlcpy(xh.confdir, confdir, sizeof(xh.confdir));
	xbps_strlcpy(xh.metadir, metadir, sizeof(xh.metadir));

	xh.state_cb = state_cb;
	xh.state_cb_data = &sd;
	/* xh.fetch_cb = fetch_file_progress_cb; */
	/* xh.fetch_cb_data = &xfer; */
	xh.flags |= XBPS_FLAG_IGNORE_CONF_REPOS       | \
							XBPS_FLAG_DISABLE_SYSLOG          | \
							(debug   ? XBPS_FLAG_DEBUG   : 0) | \
							(verbose ? XBPS_FLAG_VERBOSE : 0);

	if ((rv = xbps_init(&xh)) != 0) {
		fprintf(stderr, "failed to initialize libxbps: %s\n", strerror(rv));
		exit(EXIT_FAILURE);
	}

	if (sync && !dryrun)
		rv = sync_foreach_arch(&xh, &sd);

	if (!dryrun && (rv = xbps_pkgdb_lock(&xh)) != 0) {
		fprintf(stderr, "Failed to lock the pkgdb: %s\n", strerror(rv));
		exit(rv);
	}

	if (update) {
		rv = update_foreach_arch(&xh, &sd);
		/* rv = xbps_rpool_foreach(&xh, search_repo_cb, &sd); */
		/* if (rv != 0 && rv != ENOTSUP) { */
			/* fprintf(stderr, "Failed to initialize rpool: %s\n", */
					/* strerror(rv)); */
			/* return rv; */
		/* } */
	}

	exit(rv);
}
