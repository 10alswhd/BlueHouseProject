// Int→String
var i:Int = 10
print(String(i,radix:2))    // 1010
print(String(i,radix:8))    // 12
print(String(i,radix:10))   // 10
print(String(i,radix:16))   // a
// String→Int
var s:String = "10"
print(Int(s,radix:2)!)      // 2
print(Int(s,radix:8)!)      // 8
print(Int(s,radix:10)!)     // 10
print(Int(s,radix:16)!)     // 16
