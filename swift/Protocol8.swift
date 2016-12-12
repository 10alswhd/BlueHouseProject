//methodProtocolに適合した構造体
struct testStruct : methodProtocol {
    func testMethod1() {
        println("test")
    }
    
    func testMethod2(num:Int...)->Int {
        var sum = 0
        for n in num {
            sum += n
        }
        return sum
    }
    
    static func testTypeMethod() {
        println("test")
    }
}

//methodProtocolに適合したクラス
class testClass : methodProtocol {
    func testMethod1() {
        println("test")
    }
    
    func testMethod2(num:Int...)->Int {
        var sum = 0
        for n in num {
            sum += n
        }
        return sum
    }
    
    class func testTypeMethod() {
        println("test")
    }
}
