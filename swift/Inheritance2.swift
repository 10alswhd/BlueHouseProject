class Student : Person{
    var no = 0
    
    func printNo(){
        println("出席番号は\(self.no)です。")
    }
    
}

var student = Student(name: "test", age: 10)
student.printSelfIntroduction()
student.printNo()

//結果
//私の名前はtestです。年齢は10歳です。
//出席番号は0です。
