class SampleGenerics<T> {
    func returnNum(n1:T)->T{
        return n1
    }
    
    //コンパイルエラー
    func addNum(n1:T,n2:T)->T{
        return n1 + n2
    }
}
