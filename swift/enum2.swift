// Playground - noun: a place where people can play
import UIKit

enum MensSize {
    case S
    case M
    case L
    case XL
}

var size = MensSize.M

println(size)

size = .XL

println(size)

func packing(size:MensSize) -> String {
    var stuff:String

    switch size {
        case .XL, .L :
            stuff = "Large"
        case .M :
            stuff = "Medium"
        case .S :
            stuff = "Small"
    }

    return stuff
}

println(packing(size))

enum Direction:Int {
    case forward  = 1
    case backward = 2
    case left     = 3
    case right    = 4
}

println(Direction.forward)
println(Direction.forward.rawValue)
println(Direction(rawValue: 3))
