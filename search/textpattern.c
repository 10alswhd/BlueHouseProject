int main() {
                char str[255];
                int wiersz = 1;
                int kolumna = 1;
                char *word;
                char *search_word = "dupa";
                char pauzy[] = " ,.-";
               
                FILE *f = fopen("file.txt", "r"); 
               
                while (fgets(str, sizeof(str), f)) {
                              
                               word = strtok(str, pauzy);
                               while(word != NULL) {
                                               if (strcmp(word, search_word) == 0) {
                                                               printf("%d,%d ", kolumna, wiersz);
                                               }
                                               kolumna++;
                                               schowek = strtok(NULL, pauzy);
                               }
                               wiersz++;
                               kolumna = 1;
                }
                fclose(f);             
}
