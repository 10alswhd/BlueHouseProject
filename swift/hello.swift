class MyClass {
    // Instance variables
    var myStr: String
    
    // Constructor
    init() {
        myStr = "Hello "
    }
    
    // Method
    func myFunc(value:String) -> String {
        var myClosure: (String) -> (String) = {
            [unowned self] (value: String) -> (String) in

            let retStr = self.myStr + value
            return retStr
        }
        
        return myClosure(value)
    }

    func myMethod(value:String) -> String {
        let retStr = self.myStr + value
        return retStr
    }
}

let myInstance = MyClass()
myInstance.myFunc("World")
myInstance.myMethod("World")
