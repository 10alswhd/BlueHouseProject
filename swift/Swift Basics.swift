//: Playground
import UIKit

// we can use semicolons
let cat = "🐱"; print(cat)

// integer
print(UInt8.min)
print(UInt8.max)

print(Int.min)
print(Int.max)

print(UInt.min)
print(UInt.max)

// floating point numbers
let d: Double = 100 // 64bit
print(d)

let f: Float = 100 // 64bit
print(f)

// interferance
let r = 1_000 + 0.1
print(r)

let integer = 1
print(integer)
let binary = 0b01
print(binary)
let octa = 0o21
print(octa)
let hexa = 0x11
print(hexa)
let bool = Bool(true)
if bool {
    print(bool)
}


// Conversions
let d1 = Double(1)
print(d1)

// type aliases
typealias MY_INT = Int
let myInt: MY_INT = 100
print(myInt)

// tuples (grouping values into one variable)
var tuple = (1, "Hi")
print (tuple)

var (f1, f2 ) = (1, "Hi")
print(f1)
print(f2)

// optional values
let s1 = "123"
let i1 = Int(s1)
print(i1)

var i2:Int? = 100
i2 = nil
if i2 == nil {
    print(i2)
}

// forced unwrapping
print("i am 100% sure i1 has value \(i1!).")

// optional biding
if let i3 = i2 {
    print(i3)
} else {
    print("Nothing there")
}

if let i4: Int? = 0, i5:Int? = 1 where i4 < i5 {
    print("It is smaller")
}
