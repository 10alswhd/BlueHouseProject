<?php
/**
 * Permutations
 *
 * Returns an array of strings containing all the
 * ($alphabet ^ $output_length) permutations
 *
 * @alphabet (string|array) set of at least two elements to choose from
 * @output_length (int) the number of elements in each output string
 * 
 * permutations(“ab”, 3); ==> aaa, aab, aba, abb, baa, bab, bba, bbb
 *
 */
function permutations ($alphabet, $output_length=1) {
 
  $output = array();
 
  if ($alphabet AND ($output_length > 0)) {
 
    // Handles both string alphabets and array alphabets
    if (is_string ($alphabet)) {
      $alphabet_length = strlen ($alphabet);
      $symbol = str_split ($alphabet);
    } elseif (is_array ($alphabet)) {
      $alphabet_length = count ($alphabet);
      $symbol = $alphabet;
    } else {
      return $output;
    }
 
    if ($alphabet_length < 2) return $output;
 
    // Creates a -1 index in order to avoid the out-of-bounds
    // warning during the last loop of the do-while structure
    $pointer = array_fill (-1, $output_length+1, 0);
 
    // How much iterations to perform
    $iterations = pow ($alphabet_length, $output_length);
 
    // To avoid all the "- 1"...
    $alphabet_length--;
    $output_length--;
 
    // Do the job
    for ($i=0; $i < $iterations; $i++) {
      $permutation = "";
      for ($c = 0; $c <= $output_length; $c++) {
        $permutation .= $symbol[$pointer[$c]];
      }
      $output[] = $permutation;
 
      // Updates the pointers
      $c = $output_length;
 
      do {
        $pointer[$c]++;
        if ($pointer[$c] <= $alphabet_length) {
          break;
        } else {
          $pointer[$c] = 0;
          $c--;
        }
      } while (TRUE);
    }
  }
 
  return $output;
?>
