
// This is an object we want to JSON encode. We need to know if it's a dictionary or array.
let instance: AnyObject = [1, 2, 3] as! AnyObject

// Checking if an object is a non-parameterized generic type is not supported
if instance is Array { // Argument for generic parameter 'T' could not be inferred
    println("It's an array")
}

// When combing the two `is` checks, each independently invalid, the compiler shows the wrong errror.
// Thanks to @eridius for helping debug this.
if instance is Array || instance is Dictionary { // Binary operator '||' cannot be applied to two Bool operands
    println("It's an array or dictionary")
}
