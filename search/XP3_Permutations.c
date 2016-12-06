#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <math.h>

#define MAX_RULES 8 //Max amount of rules we can use (10 digits, need to discount first and last)
#define AMOUNT_RULES 8//The amount of rules to choose from (discounting 0 and 9, we have 8)

void permute(std::vector<int> rules, int k);
bool play(int *branchingAmount, std::vector<int> rulePerm);
void useRule(std::map<int, std::vector<int> > &currentBranches, std::string &currentString, int rule);
bool checkString(std::string inputString);

const std::string Q = "Q";
const std::string X = "X";
const std::string P = "P";

int main()
{
   //XP3 rules
   /*
      You must only use 10 of the following rules to obtain XP3 from Q.
      0. you must start with the string Q
      1. if you have a string whose last letter is Q, then you can add a P on the end.
      2. if you have a string which is of the form Xs where s is any string, then you can make Xss.
      3. if you have a string which contains QQQ you can replace the QQQ with P.
      4. if you have a string which contains PP you can delete the PP from the string.
      5. if you have a string which does not end with X then you can insert an X at the front.
      6. if you have a string which is exactly four letters long you may add an X to the end.
      7. if you have a string which contains an equal number of each letter X P and Q you may ring the bell.
      8. if you have a string which contains XX you may replace the XX with QQQ.
      9. if you have the string XP you can add 3 to the end, and have finished!
   */
   //Our rules
   std::vector<int> testRules;
   for(int i = 0; i < MAX_RULES; i++) {
      testRules.push_back(i+1);
   }
   //Loop structure to brute force all permutations
   permute(testRules, AMOUNT_RULES);

   return 0;
}

void permute(std::vector<int> rules, int k) {
   int n = rules.size();
   int totalValues = 0;
   int totalOutcomes = 0;
   if (k < 1 || k > n) {
      std::cout<<"ERROR\n"<<std::endl;
      return;
   }
   //Get indices
   std::vector<int> indexes;
   for(int i = 0; i < n; i++) {
      indexes.push_back(i);
   }

   int total = (int)pow(n, k);
   //std::map<int, std::vector<int> > branchRules; //rule, index's
   while (total-- > 0) {
      std::vector<int> rulePermutation;
      std::cout<<"Rules: ";
      for (int i = 0; i < n - (n - k); i++) {
         //Create the 8 set of rules we'll be using
         rulePermutation.push_back(rules[indexes[i]]);
         std::cout<<rules[indexes[i]]<<" ";
      }
      std::cout<<std::endl;
      //Play game with the permutation of rules and
      int branchingAmount = 0;
      if(play(&branchingAmount, rulePermutation)) {
         return;
      }
      totalValues++;
      totalOutcomes += branchingAmount;
      std::cout<<"Total Permutations: "<<totalValues<<std::endl;
      std::cout<<"Total Outcomes: "<<totalOutcomes<<"\n"<<std::endl;

      for (int i = 0; i < n; i++) {
         if (indexes[i] >= n - 1) {
            indexes[i] = 0;
         } else {
            indexes[i]++;
            break;
         }
      }
   }
}

/*int recursiveBranch(int inLevel, std::vector<int> rulePerm, std::map<int, std::vector<int> > inBranch, std::string inputString, int currentIndex) {
   std::map<int, std::vector<int> > branches;
   int branchAmount = 0;
   while(branchAmount == 0 || !branches.empty()) {
      std::string currentString = inputString;
      for(int i = currentIndex; i < rulePerm.size(); i++) {
         int currentRule = rulePerm[i];
         useRule(branches, currentString, currentRule);
         if(!branches.empty()) {
            branchAmount += recursiveBranch(inLevel+1, rulePerm, branches, currentString, i);
         }
      }
      //Check if final string is XP here
      if(checkString(currentString)) {
         return true;
      }
      branchAmount++;
   }
   return branchAmount;
}*/

bool play(int *branchingAmount, std::vector<int> rulePerm) {
   //Start string is Q every permutation
   std::string inputString = "QQQQQQQ";
   std::cout<<"Input: "<<inputString<<std::endl;
   //We want to loop over the permutation for all branches
   std::map<int, std::vector<int> > branches;
   int branchAmount = 0;
   while(branchAmount == 0 || !branches.empty()) {
      std::string currentString = inputString;
      for(int i = 0; i < rulePerm.size(); i++) {
         int currentRule = rulePerm[i];
         useRule(branches, currentString, currentRule);
      }
      //Check if final string is XP here
      if(checkString(currentString)) {
         return true;
      }
      branchAmount++;
   }
   std::cout<<"Amount of Branching: "<<branchAmount<<std::endl;
   *branchingAmount = branchAmount;
   return false;
}

void useRule(std::map<int, std::vector<int> > &currentBranches, std::string &currentString, int rule) {
   if(rule == 1) {
      //Last char of string, check if Q
      char ch = *currentString.rbegin();
      std::string lastLetter(1, ch);
      if(lastLetter == Q) {
         currentString.append(P);
      }
   } else if (rule == 2) {
      std::string firstLetter(1, currentString[0]);
      if(firstLetter == X && currentString.length() > 1) {
         //copy substring
         std::string temp = currentString.substr(1,currentString.length()-1);
         currentString.append(temp);
      }
   } else if (rule == 3) {
      //If no branching exists for this rule we must check incase
      std::map<int, std::vector<int> >::iterator it = currentBranches.find(rule);
      if(it == currentBranches.end()) {
         //Search for locations of "QQQ" and put them in in the map
         std::string searchString = "QQQ";
         size_t index = currentString.find(searchString);
         if(index != std::string::npos)
            currentBranches.insert(std::pair<int,std::vector<int> >(rule, std::vector<int>()));
         while(index != std::string::npos)
         {
             currentBranches[rule].push_back(index);
             index = currentString.find(searchString,index+1);
         }
      }
      //If no branching/branching has just been completed, do one of the branches
      //Get branch from map and process it if it exists
      it = currentBranches.find(rule);
      if(it != currentBranches.end() && (it->second).size() > 0) {
         currentString.replace((it->second)[0], 3, P);
         currentBranches[rule].erase(currentBranches[rule].begin());
         if(currentBranches[rule].size() == 0)
            currentBranches.erase(rule);
      }
   } /*else if (rule == 4) {
      int index = currentString.find("PP");
      if(index != std::string::npos) {
         currentString.erase(index, 2);
      }
   } else if (rule == 5) {
      char ch = *currentString.rbegin();
      std::string lastLetter(1, ch);
      if(lastLetter != X) {
         currentString.insert(0,X);
      }
   } else if (rule == 6) {
      if(currentString.length() == 4) {
         currentString.append(X);
      }
   } else if (rule == 7) {
      //Ring the bell... Maybe
   } else if (rule == 8) {
      int index = currentString.find("XX");
      if(index != std::string::npos) {
         currentString.replace(index, 2, "QQQ");
      }
   }*/
   return;
}

bool checkString(std::string inputString) {
   std::cout<<"Outcome: "<<inputString<<std::endl;
   //Check if theres no Q (milestone!)
   /*int index = inputString.find("Q");
   if(index == std::string::npos) {
      return true;
   }*/
   //Or check if theres an XP
   if(inputString == "XP") {
      return true;
   }
   return false;
}
