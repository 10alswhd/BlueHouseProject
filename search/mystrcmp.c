int mystrncmp(char str[], char str2[], int n) {
  int i;
	for (i = 0; i < n; i++) {
		if (str[i] != str2[i]) {
			return 1;
		}
	}
	return 0;
}
