struct UpperLower {
    int shortest_dah;
    int longest_dit;
};

/**
 * @author Jonathan Wheeler
 * @date 11 February 2016
 *
 * Accepts a digital input taken from a photodiode. 
 * @return an array of characters
 */
public char[] morse2ascii(bool morse[], int max_morse_dits_and_dahs = 2048) {
  // Search through the array and find short and long signals.
  int signal_lengths[][] = new int[2][2*max_morse_dits_and_dahs] // 2* to account for spaces, index 0 is 0 for space, 1 is signal, index 1 is length
  
  int i, j, l = 0;
  while(++i < morse.length && j < signal_lengths.length){
    if (morse[i]) { // Morse channel is on
      if (i >= 1 && (morse[i-1]) {
        // This is a continuation of a 'high' signal
        l++; // Increment the length
      } else {
        // This is the beginning of a 'high' signal
        signal_lengths[0][j] = 0; // This was a space
        signal_lengths[1][j++];
        l = 0;
      }
    } else { // Morse channel is off
      if (i >= 0 && (!morse[i-1])) {
        // This is a continuation of a 'low' signal 
        l++;
      } else {
        // Morse channel is on a falling edge
        signal_lengths[0][j] = 1; // This was sound;
        signal_lengths[1][j++] = l; // Write the length to the arary 
        l = 0; // Reset length
      }
    }
    

  } // End while loop, either we have reached the end of the file or we have more than signal_lengths.length samples
  
  // TODO: Sort the list
  
  // TODO: Step through the list and find the differences
  
  // TODO: Get the max difference and assign longest dit and shortest dah
  
  // TODO: Convert dits and dahs and group based on space length
  
  // TODO: Convert dits and dahs using a table
  
  // TODO: Return an array of characters
  
  //TODO: Garbage collection
  
}
