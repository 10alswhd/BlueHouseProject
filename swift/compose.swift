import UIKit

func comp<A, B, C>(f: (A -> B), g: (B -> C)) -> (A -> C) {
    return { x in g(f(x)) }
}
