extension Optional {
    func reduce<U>(initial: U, combine: (U, T) -> U) -> U {
        if let me = self {
            return combine(initial, me)
        } else {
            return initial
        }
    }
    
    func each(f: T -> Void) {
        reduce(()) { f($1) }
    }
    
    func fmap<U>(transform: T -> U?) -> U? {
        return map(transform).reduce(nil) { $1 }
    }
    
    func filter(includeElement: T -> Bool) -> T? {
        return fmap { includeElement($0) ? $0 : nil }
    }
}

// each
if true {
    let a: Int? = 2
    let b: Int? = nil
    
    a.each { println($0) } // 2
    b.each { println($0) } // nil
}

// reduce
if true {
    let name1: String? = "world"
    let name2: String? = nil
    
    let r1: String = name1.reduce("Hello") { $0 + ", " + $1} // Hello, world
    let r2: String = name2.reduce("Hello") { $0 + ", " + $1} // Hello
}

// flatMap(fmap)
if true {
    let a: Int? = 2
    let b: Int? = 3
    
    let r = a.fmap { a0 in
        b.map { b0 in
            a0 + b0
        }
    }
}
