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
    
    //インスタンスメソッド
    func printSelfIntroduction(){
        println("私の名前は\(self.name)です。年齢は\(self.age)歳です。")
    }
    
    //デイニシャライザ
    deinit {
        println("deinit call")
    }
    
    //タイプメソッド
    class func printPersonInfo() {
        println("Personクラスは人の情報を定義したクラスです")
    }
}
