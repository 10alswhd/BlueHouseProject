#include <fontconfig/fontconfig.h>
#include <stdio.h>

int
main (int argc, char* argv[])
{
	char* key = "monospace";
	FcObjectSet* os = NULL;
	// configure the search pattern
	FcPattern* pat = FcNameParse((FcChar8*)key);
	if (!pat) {
		printf("Parse pattern failed\n");
		return -1;
	}

	FcConfigSubstitute(NULL, pat, FcMatchPattern);
	FcDefaultSubstitute(pat);

	FcFontSet* fs = FcFontSetCreate();

	FcResult result;
	FcPattern* match = FcFontMatch(NULL, pat, &result);
	if (match) {
		FcFontSetAdd(fs, match);
	}
	FcPatternDestroy(pat);

	const FcChar8* format = (const FcChar8*)"%{=fcmatch}\n";

	printf("Font num: %d\n", fs->nfont);
	if (fs) {
		int i;
		for (i = 0; i < fs->nfont; i++) {
			FcPattern* font;
			font = FcPatternFilter(fs->fonts[i], os);
			FcChar8* s;
			s = FcPatternFormat(font, format);
			if (s) {
				printf("%s", s);
				FcStrFree(s);
			}
			FcPatternDestroy(font);
		}
		FcFontSetDestroy(fs);
	}

	FcFini();

	return 0;
}
