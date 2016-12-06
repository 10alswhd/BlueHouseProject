#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

/*                                                                                                                                                            
  Usage: $ g++ -std=c++11 regex_search_sample.cpp && ./a.out                                                                                                  
                                                                                                                                                              
  // example                                                                                                                                                  
  -- file.txt                                                                                                                                                 
  TX77845                                                                                                                                                     
  DC20500-0001                                                                                                                                                
                                                                                                                                                              
  -- output                                                                                                                                                   
  1: TX77845                                                                                                                                                  
  2: DC20500-0001                                                                                                                                             
        : -0001                                                                                                                                               
*/

void use()
{
  ifstream in("file.txt"); // インプットファイル                                                                                                              
  if (!in) // ファイルオープンを確認                                                                                                                          
    cerr << "no file\n";

  regex pat{R"(\w{2}\s*\d{5}(-\d{4})?)"}; // US郵便番号のパターン                                                                                             

  int lineno = 0;
  for (string line; getline(in, line);) {
    ++lineno;
    smatch matches; // マッチした文字列はここに入る                                                                                                           
    if (regex_search(line, matches, pat)) {
      cout << lineno << ": " << matches[0] << '\n'; // 完全一致                                                                                               
      if (1 < matches.size() && matches[1].matched)
        cout << "\t: " << matches[1] << '\n'; //サブマッチ                                                                                                    
    }
  }
}

int main() {
  use();
  return 0;
}
