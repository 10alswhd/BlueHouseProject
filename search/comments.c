  if (tbsTable[searchPos] >= key)    // If the value in the search position
      {                                  // is greater than the number for
         upperbound = searchPos - 1;    // which we are searching, change
      }                                // upperbound to the search position
      else                            // minus one.
      {                              // Else, change lowerbound to search.
         lowerbound = searchPos + 1;// position plus one.
      }
