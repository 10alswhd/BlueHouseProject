import UIKit

//: # Collections
// This is bad
let badArray = ["one", "two", "apple",
                "orange", "elephant", "orangutan"]

// This is good
let goodArray = ["one",
                 "two",
                 "apple",
                 "orange",
                 "elephant",
                 "orangutan"]

//: # Chained Methods
// This is bad
let badBigWordCharCount = goodArray.flatMap {
  $0.characters.count }.filter { $0 > 10 }.reduce(0) { $0 + $1 }

// This is good
let goodBigWordCharCount = goodArray
  .map { $0.characters.count }
  .filter { $0 > 10 }
  .reduce(0) { $0 + $1 }

//: # Long method signatures
// This is bad
UIView.animateWithDuration(0.25, delay: 1, usingSpringWithDamping: 0.5,
                           initialSpringVelocity: 26, options: [],
                           animations: {}, completion: { _ in })

// This is good
UIView.animateWithDuration(0.25,
                           delay: 1,
                           usingSpringWithDamping: 0.5,
                           initialSpringVelocity: 26,
                           options: [],
                           animations: {},
                           completion: { _ in })
