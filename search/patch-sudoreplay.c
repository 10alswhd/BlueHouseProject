--- ./plugins/sudoers/sudoreplay.c	2012-09-04 06:10:41.000000000 -0700
+++ sudoreplay-modified_for_rose.c	2012-11-06 09:30:09.000000000 -0800
@@ -690,22 +690,26 @@
 	    break;
 	case ')': /* end sub-expression */
 	    if (av[0][1] != '\0')
 		goto bad;
 	    /* pop */
 	    if (--stack_top < 0)
 		errorx(1, _("unmatched ')' in expression"));
 	    if (node_stack[stack_top])
 		sn->next = node_stack[stack_top]->next;
 	    debug_return_int(av - argv + 1);
-	bad:
+
+// DQ (11/5/2012): Problem location for label (until fixed in ROSE, captured in test2012_161.c)
+// bad:
 	default:
+// DQ (11/5/2012): Better equivalent location for label (supported in ROSE)
+bad:
 	    errorx(1, _("unknown search term \"%s\""), *av);
 	    /* NOTREACHED */
 	}
 
 	/* Allocate new search node */
 	newsn = ecalloc(1, sizeof(*newsn));
 	newsn->type = type;
 	newsn->or = or;
 	newsn->negated = not;
 	/* newsn->next = NULL; */
