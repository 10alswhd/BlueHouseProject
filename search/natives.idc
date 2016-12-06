#include <idc.idc>

static main() {
	GetNatives();
}

static FindNativeNameAddr(name) {
	auto addr;
	addr = FindText(0, SEARCH_DOWN | SEARCH_CASE, 0, 0, name);
	while (addr != BADADDR) {
		GetNativeAddr(addr);
		Message("Found '%s' at %x\n", name, addr);
		addr = FindText(addr, SEARCH_DOWN | SEARCH_NEXT | SEARCH_CASE, 0, 0, name);
	}
}

static GetNativeAddr(name_loc) {
	auto xref;
	xref = DfirstB(name_loc);
	if (xref != BADADDR && XrefType() == dr_O) {
		Message("Found xref to %x at %x\n", name_loc, xref);
	}
}

static GetNatives() {
	auto filename;
	auto file;
	auto name;

	filename = AskFile(0, "*", "Choose a file that contains a list of native functions");
	if (filename == 0) {
		Message("Cancelled\n");
		return 0;
	}

	file = fopen(filename, "r");
	if (file == 0) {
		Warning("Couldn't open file '%s'\n", filename);
		return 0;
	}

	while ((name = readstr(file)) != -1) {
		name = substr(name, 0, strlen(name) - 1); // remove line break
		Message("name = %s\n", name);
		FindNativeNameAddr(name);
	}
}
