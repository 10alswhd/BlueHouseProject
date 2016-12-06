ssize_t  simpleIndex(Table table, const char *name, int maxOut) {
	for (int i = 0; i < maxOut; i ++) {
		Method method = table[i];
		Dl_info info;
		int status = dladdr(method, &info);
		if (status != 0) {
			return -1;
		}
		const char *symbol = info.dli_sname;
		if (!strcmp(symbol, name)) {
			return i;
		}
	}
	return -1;
}
