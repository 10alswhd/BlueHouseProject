// Debugger

// Runtime debugging routines.

// Classes: TExecutor

// File: debugger.h

// Module: Executor

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream.h>
#include <iomanip.h>
#include "common.h"
#include "exec.h"

void TExecutor::ReadCommand(void)
{
  //--Loop to prompt for and execute debugger commands until the null command
  for (;;) {
      cout << endl << COMMAND_PROMPT;

  //--Create the command parser if it hasn't already been created. 
  //--Doing so will cause it to read the first command input line.
  if (cmdToken == tcIdentifier) DoCommand();
  else if (cmdToken == tcSemicolon) break;
else Error(errUnexpectedToken);

//--The command must end with a semicolon.
if (cmdToken != tcSemicolon) {
   Error(errUnexpectedToken);
   while (cmdToken != tcSemicolon) GetCommandToken();
    }
  }
}

// DoCommand  Execute a debugger command

void TExecutor::DoCommand(void)
{
  char *cmdString = pCmdToken->String();
  errorCount = 0;

//--Statement trace
If (stricmp(cmdString, "trace") == 0) {
   traceStatementFlag = true;
   singleSteppingFlag = false;
   GetCommandToken();
}
else if (stricmp(cmdString, "untrace") == 0) {
   traceStatementFlag = false;
   GetCommandToken();
}

//--Single stepping
else if (stricmp(cmdString, "step") == 0) {
   singleSteppingFlag = false;
   GetCommandToken();
}

// -- Breakpoints
else if (stricmp(cmdString, "break") == 0) SetBreakPoing();
else if (stricmp(cmdString, "unbreak") == 0) RemoveBreakPoint();

//--Routine entry/exit trace
else if (stricmp(cmdString, "routine") {
   traceRoutineFlag = true;
   GetCommandToken();
}
else if (stricmp(cmdString, "routine") == 0) {
   traceRoutineFlag = false;
   GetCommandToken();
}

//--Watches 
else if (striCmp(cmdString, "watch") == 0) setWatch(true, true);
else if (striCmp(cmdString, "fetch") == 0) setWatch(true, false);
else if (striCmp(cmdString, "store") == 0) setWatch(false, true);
else if (striCmp(cmdString, "unwatch") == 0) RemoveWatch();

//--Show and assign
else if (stricmp(cmdString, "show") == 0) ShowValue()
else if (stricmp(cmdString, "assign") == 0) doAssignment();

//where
else if (stricmp(cmdString, "where") == 0) {
  PrintStatement();
  GetCommandToken()
}

//--Stop
else if (stricmp(cmdString, "stop") == 0) {
  cout << endl << "Program stopped." << endl;
  exit(Exit_Success);
   }
}

//Print statement  Print the current statement.

void TExecutor::PrintStatement(void)
{
  cout << endl << "At" << currentLineNumber << ":";
  RecreateStatement();
}

// Print line number

void TExecutor::PrintStatement(void)
{
   cout << "<" << currentLineNumber << ">";
}

//Set breakpoint  Set a breakpoint or print the line numbers of all the current breakpoints.

void TExecutor::SetBreakpoint(void)
{
  GetCommandToken();

  switch (cmdToken) {

  case tcSemicolon:

  //--No line number list all breakpoints.
  if (pBreakPointList) {
     cout << "Breakpoints at the following lines:" << endl;
     for (TBreakpointItem *pbp = pBreakpointList;
     pbp; pbp = pbp->next) {
     cout << setw(10) << pbp ->linenumber << endl;
    }
}
else cout << "No breakpoints set." << endl;

break;

case tcNumber:

// set a breakpoint at the specified line by allocating a breakpoint item and inserting it into the sorted list.
if (pCmdToken->Type() == tyInteger) {
   int number = pCmdToken->Value().integer;
   TBreakpointItem **ppbp = &pBreakpointList;

  // Search for the insertion point.
  while (*ppbp) {
     if (number <= (*ppbp)->lineNumber) break;
     else ppbp = &(*ppbp)->next;
}

//-Insert if not already in list.
if (!(*ppbp) || (number < (*ppbp)->lineNumber)) {
    new TBreakpointItem(*ppbp, number);
   }
}
else Error(errUnexpectedToken);

GetCommandToken();
break;

default:
   Error(errUnexpectedToken);
   break;
  }
}

// RemoveBreakpoint  Remove a specific breakpoint, or remove all the current breakpoints

void TExecutor::RemoveBreakpoint(void)
{
  GetCommandtoken();
  
  switch (cmdToken) {

  case tcSemicolon:

  //--No line number; remove all breakpoints.
  RemoveBreakpointList();
  break;

  case tcNumber:
  
  //--Remove the breakpoint at the specified line.
  if (pCmdToken->Type() == tyInteger) == tyInteger) {
  int number = pCmdToken->Value().integer;
  TBreakPointItem **ppbp = &pBreakpointList;

  //-Search for the line number to delete
  while (*ppbp) {
    TBreakpointItem *next = (*ppbp)->next;
    if (number == (*ppbp)->lineNumber) {
       delete *ppbp;
       *ppbp = next;
       break;
      }
      else ppbp = &(*ppbp)->next;
   }
}
else Error(errUnexpectedToken);

GetCommandToken();
break;

default:
  Error(errUnexpectedToken);  
  break;
  }
}

// SetWatch   Set a watch or print all the variables currently watched
// fFlag : true to watch fetches, else false
// sFlag : true to watch stores, else false

void TExecutor::SetWatch(int fFlag, int sFlag)
{
   GetCommandToken();
  
   switch (cmdToken) {

     case tcSemicolon:

     //--No variable: list all watches.
     if (pWatchList) {
       cout << "Watching the following variables:" << endl;
       for (TWatchItem *pw = pWatchList;
          pw; pw = pw->next) {
         cout << "  " << pw->pId->String() << "\t";
         if (pw->fetchFlag) cout << " (fetch)";
         if (pw->storeFlag) cout << " (store)";
         cout << endl;
       }
   }
   else cout << "No watches set." << endl;

   break;

   case tcIdentifier: {

   //-- Set a watch on a specified variable by allocating a watch item and inserting it into the sorted list.
   TWatchItem **ppw = &pWatchList;
   char *watchString = pCmdToken->String();
   TSymtabNode *pWatchId = pCmdParser->DebugSearchAll(watchString);

   if (pWatch) {
 
   //--Search for the insertion point.
   while (*ppw) {
      int cmp = strcmp(watchString, (*ppw)->pId->String());
   if ((cmp < 0) || ((cmp == 0) && (pWatchId == (*ppw)->pId))) break;
   else ppw = &(*ppw)->next;
}

//--Insert if not already in list.
if (!(*ppw) || (pWatchId != (*ppw)->pId)) {
   new TWatchItem(*ppw, pWatchId, fFlag, sFlag);
  }
} else Error(errUndefinedIndentifier);

GetCommandToken();
break;
}

default:
   Error(errUnexprectedToken);
   break;
  }
}

//Remove watch Stop watching a specific variable or stop watching all variables

void TExecutor::RemoveWatch(void)
{
  GetCommandToken();

  switch (cmdToken) {

    case tcSemicolon:

      //-No variable: remove all watches.
      RemoveWatchList();
      break;

   case tcIdentifier: {

   //--Remove the watch of the specified variable.
   TWatchItem **ppw = &pWatchList;
   TSymtabNode *pWatchId = pCmdParser->DebugSearchAll(pcmdToken->String());

   if (pWatchId) {

    //-Search for the watched variable to delete.
    while (*ppw) { 
       TWatchItem *next = (*ppw)->next;
       if (pWatchId == (*ppw)->pId) {
          delete *ppw;
          *ppw = next;
          break;
        }

        default:
         Error(errUnexpectdToken);
         break;
     }
}

// ShowValue  Print the value of an expression.

void TExecutor::ShowValue(void)
{
   SaveState();
   pCmdParser->ParseCommandExpression(pIcode, cmdToken);

  //--Execute the command expression and print its value.
  if (errorCount == 0) {
      GetToken();
      TType *pType = ExecuteExpression();
      cout << "  ==> ";
      TraceDataValue((ptype->IsScalar()) ? TOS() : TOS()->address, pType);
}

delete pIcode;
RestoreState();
}

// DoAssignment  Assign a new value to a variable.

void TExecutor::DoAssignment(void)
{
  SaveState();
  TSymtabNode *pTargetId = pCmdParser->ParseCommandAssignment(pIcode, cmdToken);

//-Execute the assignment
if (errorCount == 0) {
   GetToken();
   ExecuteAssignment(pTargetId);
}

delete pIcode;
RestoreState();
}

//RecreateStatement  Recreate a statement from the intermediate code.

static const TTokencode tlStatementRecreateEnd[ ] = {
tcSemicolon, tcEnd, tcElse, tcUNTIL, tcDummy };

void TExecutor::RecreateStatement(void)
{
  const int bufferSize = 60;
  char buffer[bufferSize]; // buffer for recreated stmt
  int xBuffer = 0; buffer index
  int currIsDelimiter = false //true if current token is a delimeter, else false
  int prevIsDelimiter = // likewise for previous token

  SaveState();

//--Loop to get tokens until the end of the statement or the next line marker
do {
     int len = strlen(pToken->String()); // token string length
     
    //--Print the buffer if it's full.
   if (xBuffer + len > = bufferSize) {
      cout << "t\" << buffer << endl;
      xBuffer = 0;
   }
  //--Append a blank only if both the previous and the current tokens are not delimiters and we're not
  // already at the end of the buffer.
  If (!previousIsDelimiter && !currIsDelimiter && (xBuffer < bufferSize -1)) {
      buffer[xBuffer] = ' ';
      ++xBuffer;
   }
}  while ((currentLineNumber == saveLineNumber) && !TokenIn(token, tlStatementRecreateEnd));
//--Flush the buffer
if (xBuffer > 0) {
  buffer[xBuffer = '\0';
  cout << "\t" << buffer << endl;
  }
RestoreState();
}
