func getFullName(firstName:String, lastName:String)->String{
    return firstName + lastName
}
//getFullNameの戻り値がfullNameに代入される
let fullName = getFullName("Taro","Yamada")

println(fullName)
