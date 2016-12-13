func curry<A, B>(_ function: (A) -> B) -> (A) -> B {
    return { (`a`: A) -> B in function(`a`) }
}

func curry<A, B, C>(_ function: (A, B) -> C) -> (A) -> (B) -> C {
    return { (`a`: A) -> (B) -> C in { (`b`: B) -> C in function(`a`, `b`) } }
}

func curry<A, B, C, D>(_ function: (A, B, C) -> D) -> (A) -> (B) -> (C) -> D {
    return { (`a`: A) -> (B) -> (C) -> D in { (`b`: B) -> (C) -> D in { (`c`: C) -> D in function(`a`, `b`, `c`) } } }
}
