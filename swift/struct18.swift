struct Student{
    static var count = 0
    var name=""
    
    init(name:String){
        self.name = name
        Student.count++
    }
    
    static func getCount()->Int{
        return Student.count
    }
}
