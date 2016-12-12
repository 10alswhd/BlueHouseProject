func divide(dividend: Float, by divisor: Float) -> Float {
    if divisor == 0.0 {
        fatalError("Division by zero is not allowed")
    }
    return dividend / divisor
}
