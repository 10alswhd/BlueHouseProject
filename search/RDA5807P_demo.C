/*
  PROJETO: Radio FM com RDA5807P
  MCU: PIC18F4550
  Compilador: MikroC PRO PIC
  Autor: Tiago
  Blog: microcontrolandos.blogspot.com.br
  Bibliotecas utilizadas: RDA5807P, SSD1306, Conversions
*/

/* pinos */
sbit Soft_I2C_Sda at RD0_Bit;
sbit Soft_I2C_Scl at RD1_Bit;
sbit Soft_I2C_Sda_Direction at TRISD0_Bit;
sbit Soft_I2C_Scl_Direction at TRISD1_Bit;

/* constantes */
const int UP = 5;
const int DOWN = 6;
const int SEARCH = 7;

/* variáveis */
char flags = 0; //armazena os estados dos botões
RDA5807P radio; //configurações do módulo
RDA5807PInfo info; //informação da rádio selecionada
char msg[12]; //usado para armazenar a conversão de um número em string

void main() 
{
  ADCON1 = 15;  //desliga o conversor analogico
  CMCON = 7;    //desliga o comparador analogico
  TRISB = 255;  //defina todos os pinos como entrada
  Soft_I2C_Init(); //iniciliza a comunicacao I2C
  INTCON2.NOT_RBPU = 0; //habilita os resistores de pull-up
  RDA5807P_Init( &radio ); //inicializa o módulo
  SSD1306_Init(); //inicializa o display
  SSD1306_Clear(); //limpa o display
  SSD1306_Out8( 0, 4, "RADIO FM", 0 ); //escreve um texto
  SSD1306_Out8( 5, 0, "SINAL:", 1 ); //escreve um texto
     
  while( 1 )
  {
    if( !PORTB.UP ) flags.UP = 1; //botao UP foi pressionado
    else if( !PORTB.DOWN ) flags.DOWN = 1; //botao DOWN foi pressionado
    else if( !PORTB.SEARCH ) flags.SEARCH = 1; //botao SEARCH foi pressionado
            
    if( PORTB.UP && flags.UP ) //botao UP foi liberado
    {
      flags.UP = 0; //limpa a flag
      RDA5807P_Up( &radio ); //incrementa a frequência atual do rádio
    }
    else if( PORTB.DOWN && flags.DOWN ) //botao DOWN foi liberado
    {
      flags.DOWN = 0; //limpa a flag
      RDA5807P_Down( &radio ); //decrementa a frequência atual do rádio
    }
    else if( PORTB.SEARCH && flags.SEARCH ) //botao SEARCH foi liberado
    {
      flags.SEARCH = 0; //limpa a flag
      RDA5807P_Search( &radio, 1 ); //realiza a busca por estações de rádio
    }
            
    info = RDA5807P_Read( &radio ); //realiza a leitura da informação da rádio atual
            
    /* Exibe a frequência no display */
    WordToStr( info.FREQUENCY / 100, msg ); //converte a frequência( MHz ) em string
    SSD1306_Chr8( 3, 4, msg[1], 1 );
    SSD1306_Chr8( 3, 5, msg[2], 1 );
    SSD1306_Chr8( 3, 6, msg[3], 1 );
    SSD1306_Chr8( 3, 7, '.', 1 );
    SSD1306_Chr8( 3, 8, msg[4], 1 );
    SSD1306_Out8( 3, 9, "MHz", 1 );

    /* Exibe a força de sinal da rádio atual */
    ByteToStr( info.LEVEL, msg ); //converte o valor do sinal em string
    SSD1306_Out8( 5, 6, msg + 1, 1 );
    
    Delay_ms( 80 );
  }
}
