class Person {
    var name = ""
    var age = 0
    
    //イニシャライザ
    init(){
        self.name = "unknown"
        self.age = 20
    }
    
    //パラメータ付きイニシャライザ
    init(name:String,age:Int){
        self.name = name
        self.age = age
    }
}
