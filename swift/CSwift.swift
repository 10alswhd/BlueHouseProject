prefix func ++(inout x: Int) -> Int {
    x = x + 1
    return x
}

postfix func ++(inout x: Int) -> Int {
    let oldX = x
    x = x + 1
    return oldX
}
