func sumOf(numbers: Int...) -> Int {
    var sum = 0
    for number in numbers {
        sum += number
    }
    return sum
}
sumOf()
sumOf(42, 597, 12)

func averageOf(numbers: Int...) -> Int {
    var sum = sumOf(numbers)

    return sum / numbers.count
}

averageOf(1, 2, 3)
