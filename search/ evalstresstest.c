#include "stdafx.h"
#include <glib.h>
#include <mono/mini/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/threads.h>
extern "C" { 
	#include <mono/metadata/mono-debug.h>
}
#include <mono/metadata/mono-gc.h>

#define MONO_DEBUGGER 1

int _tmain (int argc, _TCHAR* argv[])
{
#if MONO_DEBUGGER
	char* options = "--debugger-agent=transport=dt_socket,embedding=1,defer=y";
	mono_jit_parse_options (1, &options);
	mono_debug_init ( (MonoDebugFormat)1);
#endif

	MonoDomain* domain = mono_jit_init_version ("Root Domain", "v2.0.50727");
	MonoMethodDesc* desc = mono_method_desc_new ("Evaluator.Test:Run()", 1);

	for (int i = 0; i < 500; ++i)
	{
		MonoDomain* child = mono_domain_create_appdomain ("Child Domain", NULL);
		mono_thread_push_appdomain_ref(child);
		mono_domain_set (child, FALSE);

		MonoAssembly* ass = mono_domain_assembly_open (mono_domain_get (), "Evaluator.dll");
		MonoImage* img = mono_assembly_get_image (ass);
		MonoMethod* m = mono_method_desc_search_in_image (desc,img);
		MonoObject* exc;
		MonoObject* ret = mono_runtime_invoke (m, 0, 0, &exc);
		if (exc)
		{
			printf("ERROR!");
			break;
		}

		mono_domain_set (mono_get_root_domain (), 0);
		mono_thread_pop_appdomain_ref ();
		mono_domain_unload (child);

		mono_gc_collect (mono_gc_max_generation ());
	}

	return 0;
}
