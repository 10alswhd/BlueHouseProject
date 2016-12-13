// Playground - noun: a place where people can play
import UIKit

func hello() {
    println("Hello World !!")
}

hello()

func getMessage() -> String {
    return "Hello World !!"
}

getMessage()

func twice(num:Int) -> Int {
    return 2 * num
}

println(twice(15))

func add(a:Double, b:Double) -> Double {
    return a + b
}

println(add(5.0, 6.5))

func sum(numbers:Double...) -> Double {
    var total:Double = 0.0

    for number in numbers {
        total += number
    }

    return total
}

println(sum(4.0, 3.0, 5.0, 2.0, 8.0, 6.0))

func printMessage(message:String = "Hello World !!") {
    println(message)
}

printMessage()
printMessage(message: "Hello Japan !!")

func add(a:Int, b:Int = 1, c:Int = 2) -> Int {
    return a + b + c
}

println(add(1))
println(add(1, b:3))
println(add(1, b:3, c:4))

func getPrice(var price:Int) -> Int {
    let tax = 1.08
    price = Int(floor(Double(price) * tax))
    return price
}

println(getPrice(100))

func computeBMI(weight kg:Double, height cm:Double) -> Double {
    if (cm == 0) {
        return -1
    }

    let bmi = round((kg / pow(cm * 0.02, 2)) * 10) / 10.0

    return bmi
}

println(computeBMI(weight: 56.5, height: 170))

func getTotalPrice(#unit:UInt, #number:UInt) -> UInt {
    return unit * number
}

println(getTotalPrice(unit: 500, number: 15))

func arrayByInt(#array:Array<Int>, #num:Int) -> Array<Int> {
    var results = [Int]()

    for value in array {
        results.append(value * num)
    }

    return results
}

println(arrayByInt(array: [1, 2, 3], num: 3))

func getTestResult(#math:UInt, #english:UInt, #science:UInt) -> (total:UInt, average:Double) {
    let total   = math + english + science
    let average = round((Double(total) / 3.0) * 10) / 10.0

    return (total, average)
}

let testResult = getTestResult(math: 92, english: 72, science: 62)
println("total => \(testResult.total), average => \(testResult.average)")

func calc(#a:Int, #b:Int) -> Int {
    return a + b
}

func calc(#c:Int, #d:Int) -> Int {
    return c * d
}

func calc(#a:Int, #b:Int, #c:Int) -> Int {
    return (a + b) * c
}

println(calc(a: 4, b: 8))
println(calc(c: 2, d: 7))
println(calc(a: 5, b: 9, c: 3))

func computeAverage(#array:Array<Double>) -> Double {
    var total = 0.0

    for value in array {
        total += value
    }

    let average = total / Double(array.count);

    return average
}

func computeAverage(#numbers:Double...) -> Double {
    return computeAverage(array: numbers)
}

println(computeAverage(array: [5, 6, 7.5]))
println(computeAverage(numbers: 5, 6, 7.5))

func makeArray<T>(#items:T...) -> Array<T> {
    var array = [T]()

    for item in items {
        array.append(item)
    }

    return array
}

println(makeArray(items: 3, 5, 7, 2, 8))
println(makeArray(items: "red", "green", "blue"))

let computeTotalPrice = getTotalPrice

println(computeTotalPrice(unit: 1500, number: 19))

func printHello(user:String)  {
    println("Hello \(user)")
}

func printBye(user:String) {
    println("Bye \(user)")
}

func command(#printer:String -> (), #user:String) {
    printer(user)
}

command(printer: printHello, user: "Korilakkuma")

func getPriceFunction(#age:Int) -> (Int) -> Int {
    func getLowPrice(number:Int) -> Int {
        return 400 * number
    }

    func getHighPrice(number:Int) -> Int {
        return 600 * number
    }

    if age < 12 {
        return getLowPrice
    } else {
        return getHighPrice
    }
}

let getLowPrice  = getPriceFunction(age: 10)
let getHighPrice = getPriceFunction(age: 24)

println(getLowPrice(3))
println(getHighPrice(3))

let add:(Int, Int) -> Int = {(a:Int, b:Int) -> Int in
    return a + b
}

println(add(5, 8))

let numbers = [4, 7, 2, 9]

let array1 = map(numbers, {(let v:Int) -> Int in
    return v * 2
});

println(array1)

let array2 = map(numbers){(let v:Int) -> Int in
    return v * 2
}

println(array2)

let array3 = map(numbers){v in v * 2}

println(array3)

let array4 = map(numbers){$0 * 2}

println(array4)

let colors = ["red", "green", "blue"]

let array5 = map(colors){$0.uppercaseString}

println(array5)

func dictionaryMap(var dic:Dictionary<String, Int>, closure:(String, Int) -> (String, Int)) -> Dictionary<String, Int> {
    for (key, value) in dic {
        let (k, v) = closure(key, value)
        dic[k] = v
    }

    return dic
}

let abc = ["a":3, "b":4, "c":9]
let dic = dictionaryMap(abc){(key:String, value:Int) -> (String, Int) in
    return (key, 2 * value)
}

println(dic)

func battery(capacity:Int) -> (Int) -> Int {
    var stock = capacity

    func use(volume:Int) -> Int {
        if (stock > volume) {
            stock -= volume
        } else {
            stock = 0
        }

        return stock
    }

    return use
}

let battery100 = battery(100)

var stock:Int

stock = battery100(60)

println(stock)

stock = battery100(30)

println(stock)

stock = battery100(20)

println(stock)
