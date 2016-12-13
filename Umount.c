bsdName = (CFStringRef) IORegistryEntrySearchCFProperty(device
     , kIOServicePlane
     , CFSTR( kIOBSDNameKey )
     , NULL
     , kIORegistryIterateRecursively);
                        
/* Ahora ya podemos ver si está latch activado o no para desmontar el disco */
char* bsdNameChar = malloc(CFStringGetLength(bsdName) * sizeof(char));
if (bsdNameChar) {
  if (CFStringGetCString(bsdName, bsdNameChar, CFStringGetLength(bsdName) +1, kCFStringEncodingASCII)) {
       
    /* Hacemos la petición a latch usando el SDK para C */
    buffer = operationStatus(pAccountId, operationId);
    if(buffer == NULL || strcmp(buffer,"") == 0) {
     fprintf(stderr, "Error contacting latch servers");
      return 1;
    }

    /* Si el estado es off, entonces desmontamos el disco */
    if (strstr(buffer, "\"status\":\"off\"") != NULL) {
      fprintf (stdout, "Status: latch locked\n"); 
      fprintf(stderr, "Ejecting %s...\n", bsdNameChar);
      int size = strlen("/usr/sbin/diskutil") + strlen(" eject") + strlen(bsdNameChar) + 2;

      char *command = (char *) malloc(size);
      snprintf(command, size, "/usr/sbin/diskutil eject %s", bsdNameChar);
      system(command);
      free(command);
      /* Si está a on, lo dejamos conectarse sin problemas */
    } else if (strstr(buffer, "\"status\":\"on\"") != NULL){
      fprintf (stdout, "Status: latch not locked\n");
    } else {
      fprintf(stderr, "Ouch. Something went wrong, are you really paired?\n");
      return 1;
    }                    
  }
}
