#ifndef OPTAB_H_INCLUDED
#define OPTAB_H_INCLUDED
#include <iostream>
using namespace std;


string store[100];//stores the address assigned during pass1 wrt line no.
int store_count=0;string mod_record[100];int mod_count=0;//modification record---> when '+' with variable is used

string base;
string length;//length of file in bytes
string start_add;
int locctr;
string addr;
char buffer[256];
struct OpTable
{
  char mnemonic[8];
	char format;
	string  opcode;
};
const int optab_length=59;
OpTable temp;
bool start;
static OpTable OPTAB[]=
{
    {    "ADD",  '3',  "18"},
    {   "ADDF",  '3',  "58"},
    {   "ADDR",  '2',  "90"},
    {    "AND",  '3',  "40"},
    {  "CLEAR",  '2',  "B4"},
    {   "COMP",  '3',  "28"},
    {  "COMPF",  '3',  "88"},
    {  "COMPR",  '2',  "A0"},
    {    "DIV",  '3',  "24"},
    {   "DIVF",  '3',  "64"},
    {   "DIVR",  '2',  "9C"},
    {    "FIX",  '1',  "C4"},
    {  "FLOAT",  '1',  "C0"},
    {    "HIO",  '1',  "F4"},
    {      "J",  '3',  "3C"},
    {    "JEQ",  '3',  "30"},
    {    "JGT",  '3',  "34"},
    {    "JLT",  '3',  "38"},
    {   "JSUB",  '3',  "48"},
    {    "LDA",  '3',  "00"},
    {    "LDB",  '3',  "68"},
    {   "LDCH",  '3',  "50"},
    {    "LDF",  '3',  "70"},
    {    "LDL",  '3',  "08"},
    {    "LDS",  '3',  "6C"},
    {    "LDT",  '3',  "74"},
    {    "LDX",  '3',  "04"},
    {    "LPS",  '3',  "D0"},
    {    "MUL",  '3',  "20"},
    {   "MULF",  '3',  "60"},
    {   "MULR",  '2',  "98"},
    {   "NORM",  '1',  "C8"},
    {     "OR",  '3',  "44"},
    {     "RD",  '3',  "D8"},
    {    "RMO",  '2',  "AC"},
    {   "RSUB",  '3',  "4C"},
    { "SHIFTL",  '2',  "A4"},
    { "SHIFTR",  '2',  "A8"},
    {    "SIO",  '1',  "F0"},
    {    "SSK",  '3',  "EC"},
    {    "STA",  '3',  "0C"},
    {    "STB",  '3',  "78"},
    {   "STCH",  '3',  "54"},
    {    "STF",  '3',  "80"},
    {    "STI",  '3',  "D4"},
    {    "STL",  '3',  "14"},
    {    "STS",  '3',  "7C"},
    {   "STSW",  '3',  "E8"},
    {    "STT",  '3',  "84"},
    {    "STX",  '3',  "10"},
    {    "SUB",  '3',  "1C"},
    {   "SUBF",  '3',  "5C"},
    {   "SUBR",  '2',  "94"},
    {    "SVC",  '2',  "B0"},
    {     "TD",  '3',  "E0"},
    {    "TIO",  '1',  "F8"},
    {    "TIX",  '3',  "2C"},
    {   "TIXR",  '2',  "B8"},
    {     "WD",  '3',  "DC"},
};

struct SymbolTable
{
	string label;
	string address;
};
SymbolTable SYMTAB[20];
int symtab_ctr;

#endif // OPTAB_H_INCLUDED

