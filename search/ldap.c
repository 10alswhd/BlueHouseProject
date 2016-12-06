#include <ruby.h>
#ifndef RSTRING_PTR
#define RSTRING_PTR(str) RSTRING(str)->ptr
#endif
#ifndef RSTRING_LEN
#define RSTRING_LEN(str) RSTRING(str)->len
#endif
#ifndef HAVE_RB_STR_SET_LEN
#define rb_str_set_len(str, length) (RSTRING_LEN(str) = (length))
#endif

#include <string.h>
#include <ldap.h>

#define GetLDAPStruct(obj)	(Check_Type(obj, cLDAP), (struct ldap*)DATA_PTR(obj))
#define GetHandler(obj)		(GetLDAPStruct(obj)->handler)
#define GetLDAPMsg(obj)		(Check_Type(obj, cLDAPMsg), ((struct ldap_msg*) DATA_PTR(obj))->msg)

VALUE cLDAP;
VALUE cLDAPMsg;
VALUE eLDAP;

static int store_result_count = 0;

struct ldap {
	LDAP* handler;
	char connection;
	char blocking;
	int async_in_progress;
	char busy;
};

struct ldap_msg {
	LDAPMessage* msg;
	char freed;
};

static struct ldap* get_ldap(VALUE obj)
{
	struct ldap* ld;
	Data_Get_Struct(obj, struct ldap, ld);
	return ld;
}

static void free_ldap(struct ldap* ld)
{
	/*if (ld->connection == Qtrue)
		ldap_unbind_s(&(ld->handler));*/
	xfree(ld);
}

static VALUE msg_free(VALUE obj);

static void free_ldapmsg(struct ldap_msg* mesg)
{
	if (mesg->freed == Qfalse) {
		ldap_msgfree(mesg->msg);
		store_result_count--;
	}
	xfree(mesg);
}

static void ldap_raise(int errno)
{
	VALUE e = rb_exc_new2(eLDAP, ldap_err2string(errno));
	rb_iv_set(e, "@errno", INT2FIX(errno));
	rb_exc_raise(e);
}

static VALUE ld_alloc(VALUE klass) {
	struct ldap* ld;
	VALUE obj;

	obj = Data_Make_Struct(klass, struct ldap, 0, free_ldap, ld);
	ld->connection = Qfalse;

	return obj;
}

typedef struct {
	LDAP* ld;
	char* base;
	int scope;
	char* filter;
	int attrsonly;
	LDAPMessage** res;
} SearchArgs;

static VALUE blocking_search(void* data)
{
	SearchArgs* args = (SearchArgs*)data;
	return (VALUE)ldap_search_s(args->ld, args->base, args->scope, args->filter, NULL, args->attrsonly, args->res);
}

static VALUE ldapmsg2obj(LDAPMessage* entry)
{
	VALUE obj;
	struct ldap_msg* msg;
	obj = Data_Make_Struct(cLDAPMsg, struct ldap_msg, 0, free_ldapmsg, msg);
	msg->msg = entry;
	msg->freed = Qfalse;
	rb_obj_call_init(obj, 0, NULL);
	return obj;
}

/* initialize(uri) */
static VALUE ld_initialize(VALUE self, VALUE rb_uri)
{
	int retval;
	char* uri;
	struct ldap* ld;
	LDAP* handler;

	uri = StringValuePtr(rb_uri);
	ld = get_ldap(self);
	handler = ld->handler;

	if ((retval = ldap_initialize(&handler, uri)) != LDAP_SUCCESS)
		ldap_raise(retval);

	ld->connection = Qtrue;

	return self;
}

static VALUE ld_search(VALUE self, VALUE filter)
{
	int loop = 0;
	struct ldap* ld;
	LDAP* handler;
	SearchArgs args;
	int result;
	LDAPMessage* entry;

	ld = get_ldap(self);
	handler = ld->handler;

	Check_Type(filter, T_STRING);
	if (ld->connection == Qfalse) {
		rb_raise(eLDAP, "search: not connected");
	}
	if (rb_block_given_p()) {
		#ifdef RUBY_VM
			args.ld = handler;
			args.base = NULL;
			args.scope = LDAP_SCOPE_SUBTREE;
			args.filter = StringValuePtr(filter);
			args.attrsonly = 0;
			result = (int)rb_thread_blocking_region(blocking_search, &args, RUBY_UBF_PROCESS, 0);
		#else
			result = ldap_search_s(handler, "", LDAP_SCOPE_SUBTREE, StringValuePtr(filter), NULL, 0);
		#endif
		if (result != LDAP_SUCCESS)
			ldap_raise(result);

		entry = ldap_first_entry(handler, *args.res);
		do {
			VALUE robj = ldapmsg2obj(entry);
			rb_ensure(rb_yield, robj, msg_free, robj);
		} while ((entry = ldap_next_entry(handler, entry)) != NULL);

		return self;
	}

}

static VALUE msg_free(VALUE obj)
{
	struct ldap_msg* mesg = DATA_PTR(obj);
	check_free(obj);
	ldap_msgfree(mesg->msg);
	mesg->freed = Qtrue;
	store_result_count--;
	return Qnil;
}

static VALUE error_error(VALUE obj)
{
	return rb_iv_get(obj, "@mesg");
}

static VALUE error_errno(VALUE obj)
{
	return rb_iv_get(obj, "@errno");
}

void Init_ldap(void)
{
	cLDAP = rb_define_class("LDAP", rb_cObject);
	cLDAPMsg = rb_define_class_under(cLDAP, "Message", rb_cObject);
	eLDAP = rb_define_class_under(cLDAP, "Error", rb_eStandardError);

	rb_define_alloc_func(cLDAP, ld_alloc);
	rb_define_method(cLDAP, "initialize", ld_initialize, 1);
	rb_define_method(cLDAP, "search", ld_search, 1);

	rb_define_method(eLDAP, "error", error_error, 0);
	rb_define_method(eLDAP, "errno", error_errno, 0);

#define rb_define_ldap_const(s) rb_define_const(eLDAP, #s, INT2NUM(s))
#include "error_const.h"	
}
