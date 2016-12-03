#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <openssl/sha.h>
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <curl/curl.h>
#include <ccgi.h>

// #define MY_SECRET_KEY "----------------------------------------"


int g_SignatureLength;

char* aws_signature( char* key, ...)
{
  int i, len;
  char* data;

  va_list argp;

  static char hmac[EVP_MAX_MD_SIZE];

  len = 0;
  va_start( argp, key );

  while (1)
  {
    char* arg = va_arg( argp, char* );

    if ( arg == NULL )
    {
      break;
    }

    len += strlen( arg );
  }

  va_end( argp );

  data = (char*)malloc( sizeof(char) * (len+1) );

  if (data)
  {

    va_start( argp, key );

    len = 0;
    while (1)
    {
      char* arg = va_arg( argp, char* );
  
      if ( arg == NULL )
      {
        break;
      }

      strncpy( data+len, arg, strlen(arg) );
      len += strlen(arg);
  
    }
  
    va_end( argp );

    data[len] = 0;

    HMAC( EVP_sha256(),
          key,  strlen(key),
          data, strlen(data),
          hmac, &g_SignatureLength
        );
    free(data);
  }

  return hmac;
};

/* return the utc date+time in xml format */
const char* xml_datetime()
{
/*"YYYY-mm-ddTHH:MM:SS.000Z\"*/
/* 1234567890123456789012345 */
#define MAX 25
  static char output[MAX+1];
  time_t now = time(NULL);

  strftime( output, MAX+1, "%Y-%m-%dT%H:%M:%S.000Z", gmtime( &now ) );
#undef MAX
  return output;
}

int main( int argc, char* argv[] )
{
  CGI_varlist *vl;
  const char* author;
  int i;

  fputs("Content-type: application/json\r\n\r\n", stdout);

  if ((vl = CGI_get_all("/tmp/cgi-upload-XXXXXX")) == 0) {
      fputs("CGI_get_all() failed\r\n", stdout);
      return 0;
  }

  author = CGI_lookup(vl,"Author");
  if (author == NULL)
  {
    printf("No author\n");
    return (0);
  }

  const char* timestamp             = xml_datetime();
  const char* url_param_key         = "AWSAccessKeyId=--------------------";
  const char* url_param_author_0    = "&Author=";
  const char* url_param_operation   = "&Operation=ItemSearch&ResponseGroup=Medium&SearchIndex=Books&Service=AWSECommerceService&Sort=salesrank";
  const char* url_param_timestamp_0 = "&Timestamp=";
  const char* url_param_version     = "&Version=2009-03-31";
  const char* url_target            = "http://ecs.amazonaws.com/onca/xml?";
  const char* url_param_signature_0 = "&Signature=";

  char* url_param_author_1          = CGI_encode_url( author, NULL );
  char* url_param_timestamp_1       = CGI_encode_url( timestamp, NULL );

  char* signature = aws_signature(
    MY_SECRET_KEY,
    "GET\n",
    "ecs.amazonaws.com\n",
    "/onca/xml\n",
    url_param_key,
    url_param_author_0,
    url_param_author_1,
    url_param_operation,
    url_param_timestamp_0,
    url_param_timestamp_1,
    url_param_version,
    NULL /* required */
  );

  char* base64_signature       = CGI_encode_base64( signature, g_SignatureLength );
  char* url_param_signature_1  = CGI_encode_url( base64_signature, NULL );

  char  url_raw[1024];

  strcpy( url_raw, url_target );
  strcat( url_raw, url_param_key );
  strcat( url_raw, url_param_author_0 );
  strcat( url_raw, url_param_author_1 );
  strcat( url_raw, url_param_operation );
  strcat( url_raw, url_param_timestamp_0 );
  strcat( url_raw, url_param_timestamp_1 );
  strcat( url_raw, url_param_version );
  strcat( url_raw, url_param_signature_0 );
  strcat( url_raw, url_param_signature_1 );

  char* url_hex = CGI_encode_hex( url_raw, strlen( url_raw ) );

  fputs( "{\n",             stdout );
  fputs( "\"UrlRaw\" :",    stdout );
  fputs( "\"",              stdout );
  fputs( url_raw,           stdout );
  fputs( "\",\n",             stdout );
  fputs( "\"UrlHex\" :",    stdout );
  fputs( "\"",              stdout );
  fputs( url_hex,           stdout );
  fputs( "\"\n",              stdout );
  fputs( "}\n",             stdout );

  CGI_free_varlist(vl);

  free( base64_signature );
  free( url_param_signature_1 );
  free( url_param_author_1 );
  free( url_param_timestamp_1 );
  free( url_hex );
 
  return (0);
}
