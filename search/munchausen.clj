#!/usr/bin/env clojure
(defn ** [x n]
  (. (. java.math.BigInteger (valueOf x)) (pow n)))

(defn raise-to-itself [number]
  (** number number))

(defn digits [number]
  ; convert the number to a string,
  ; and convert each char to an int.
  ;
  ; subtract 48 because casting a char
  ; to an int returns the ASCII
  ; representation of that char.
  (map #(- (int %) 48) (str number))) 

(defn munchausen? [number]
  ; if the sum of the digits raised to
  ; themselves is equal to the number 
  ; itself, then it is a munchausen number.
  (= (apply + (map raise-to-itself (digits number))) number))

(def munchausen (filter munchausen? (range 5000)))
(println munchausen)
