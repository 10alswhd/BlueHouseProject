int dkim_exim_query_dns_txt(char *name, char *answer) {
  dns_answer dnsa;
  dns_scan   dnss;
  dns_record *rr;

  if (dns_lookup(&dnsa, (uschar *)name, T_TXT, NULL) != DNS_SUCCEED) return PDKIM_FAIL;

  /* Search for TXT record */
  for (rr = dns_next_rr(&dnsa, &dnss, RESET_ANSWERS);
       rr != NULL;
       rr = dns_next_rr(&dnsa, &dnss, RESET_NEXT))
    if (rr->type == T_TXT) break;

  /* Copy record content to the answer buffer */
  if (rr != NULL) {
    int rr_offset = 0;
    int answer_offset = 0;
    while (rr_offset < rr->size) {
      uschar len = (rr->data)[rr_offset++];
      snprintf(answer+(answer_offset),
               PDKIM_DNS_TXT_MAX_RECLEN-(answer_offset),
               "%.*s", (int)len, (char *)((rr->data)+rr_offset));
      rr_offset+=len;
      answer_offset+=len;
    }
  }
  else return PDKIM_FAIL;

  return PDKIM_OK;
}
