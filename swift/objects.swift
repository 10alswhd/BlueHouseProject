// Playground - noun: a place where people can play
import UIkit

class Vehicle {
    var color: String?
    var maxSpeed = 80
    
    // Designated(main)イニシャライザ
    init() {
        println("I've been created!")
    }
    
    // convenienceイニシャライザ
    convenience init(color: String) {
        // convenienceイニシャライザはmainイニシャライザを呼び出す必要がある
        self.init()
        self.color = color
        println("I was called with the convenience initializer")
    }
    
    deinit {
        println("I'm going away!")
    }
    
    func description() -> String {
        return "A \(self.color) vehicle"
    }
    
    func travel() {
        println("Travelling at \(self.maxSpeed) kph")
    }
}

var redCar = Vehicle()
redCar.color = "Red"
redCar.maxSpeed = 90

redCar.travel()
redCar.description()

// 継承
class Car: Vehicle {
    override func description() -> String {
        var description = super.description()
        return description + ", which is a car"
    }
}

var blueCar = Car(color: "blue")
blueCar.description()

var greenCar: Car?
greenCar = Car()
// オブジェクトのretain countが0になったらdeinitが呼ばれる
greenCar = nil

// computed properties
// ---------------------
class Rectangle {
    var width: Double = 0.0
    var height: Double = 0.0
    var area: Double {
        // computed getter
        get {
            return width * height
        }

        // computed setter
        set {
            // UIKitをimportして使う
            width = sqrt(newValue)
            height = sqrt(newValue)
        }
    }
}

var rect = Rectangle()
rect.width = 3.0
rect.height = 4.5
rect.area
rect.area = 9

rect.width
rect.height
