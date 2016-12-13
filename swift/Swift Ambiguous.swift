// Let's start with an example!
// We specify three anbiguous values a, b, c each which can be any integer [1,7]
let a = Ambiguous(1,2,3,4,5,6,7)
let b = Ambiguous(1,2,3,4,5,6,7)
let c = Ambiguous(1,2,3,4,5,6,7)

// We try to satisfy on a,b,c pythagorean's theorem, and we print the side lengths is some values a,b,c satisfy
if satisfy(a,b,c)({ (c.choice * c.choice == a.choice * a.choice + b.choice * b.choice) && (a.choice > b.choice)}) {
    println("We can have a triangle with sides lengths \(a.bound!), \(b.bound!), \(c.bound!).")
    // --> "We can have a triangle with sides lengths 4, 3, 5."
}

// It worked! Let's try another example:
let x = Ambiguous(1,2,3)
let y = Ambiguous(4,5,6)

// We print out every possible combination x,y such that the predicate is satisfied
while satisfy(x,y)({ x.choice * y.choice == 8 }) {
    println("\(x.bound!) * \(y.bound!) = 8") // --> "1 * 4 = 8"
}                                            //     "2 * 4 = 8"
                                             //     "3 * 4 = 8"
                                             //     "2 * 5 = 8"
                                             //     "1 * 6 = 8"
                                             //     "2 * 6 = 8"
                                             //     "3 * 6 = 8"
// Note that an ambiguous type need not be an Int---it can be any type!
// That's right, you could have an ambigous UIView that is initiated to contain all visible views
// And then you could use satisfy to check if any view overlap
let myViews = self.view.subviews
let a = Ambiguous(myViews)
let b = Ambiguous(myViews)

if satisfy(a,b)({ CGRectIntersects(a.frame,b.frame) }) {
    let intersecting = (a.bound!, b.bound!)
    // Do something interesting :P
}

// Pretty cool, eh?
// Note that the Ambigous variables that we are satisfying don't even have to be the same type!
// Now let's see how this works.
func satisfy(variables: AmbiguousType...) -> (() -> Bool) -> Bool {
    
    return { test in
        
        for variable in variables[1..<variables.endIndex] {
            variable.prepare()
        }
        
        while nextCombination(variables, 0) {
            if test() {
                for variable in variables { variable.bind() }
                return true
            }
        }
        for variable in variables { variable.unbind() }
        return false
    }
}

class Ambiguous<T> : AmbiguousType, Printable {
    
    let possibilities: [T]
    
    private var boundValue: T?
    var bound: T? {
        get {
            return boundValue
        }
    }
    
    var choice: T!
    
    private var generator: IndexingGenerator<Array<T>>!
    
    internal func choose() -> Bool {
        if let next = generator.next() {
            choice = next
            return false
        }
        else {
            resetGenerator()
            choose()
            return true
        }
    }
    
    internal func resetGenerator() {
        generator = possibilities.generate()
    }
    
    internal func prepare() {
        if choice == nil { choose() }
    }
    
    convenience init(_ possibilities: T...){
        self.init(possibilities)
    }
    
    init(_ possibilities: [T]){
        self.possibilities = possibilities
        resetGenerator()
    }
    
    internal func bind() {
        boundValue = choice
    }
    
    internal func unbind() {
        boundValue = nil
    }
    
    func clear() {
        resetGenerator()
        choice = nil
        unbind()
    }
    
    var description: String {
        get {
            return "Abiguous \(possibilities)"
        }
    }
}

// Return value indicates whether there are still results
func nextCombination(variables: [AmbiguousType], index: Int) -> Bool {
    
    if index >= variables.endIndex { return false }
    let exhausted = variables[index].choose()
    return exhausted ? nextCombination(variables, index + 1) : true
}

func clear(variables: AmbiguousType...){
    for variable in variables {
        variable.clear()
    }
}
