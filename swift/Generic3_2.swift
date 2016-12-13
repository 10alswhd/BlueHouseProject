class SampleGenerics<T> {
    func returnNum(n1:T)->T{
        return n1
    }
}

let sampleGenerics = SampleGenerics<Int>()
println(sampleGenerics.returnNum(10))
