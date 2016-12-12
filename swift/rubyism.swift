extension Int
{
    func times(f :(Int) -> ())
    {
        for i in 0..<self
        {
            f(i)
        }
    }
}

extension Array
{
    func each(f :(T) -> ())
    {
        for item in self
        {
            f(item)
        }
    }
}

extension Range
{
    func each(f :(T) -> ())
    {
        for item in self
        {
            f(item)
        }
    }
}

// Repeat N times
5.times { println("Called \($0+1) times") }

// Simple each-do cycle
["Dog", "Cat", "Parrot"].each { println($0) }

// Each-do for Range<T>
// (Unfortunately, it needs the parenthesis, otherwise the compiler complaints)
(0..<4).each { println("\($0)") }
