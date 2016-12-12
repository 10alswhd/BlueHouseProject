class Person{
    ...
    
    //インターネットからのデータ取得は時間がかかるため、lazyキーワードを追加。これにより、netDataプロパティが実際に利用されるまで値の取得をしない
    lazy var netData = NetData(address:"http://xxxx")
}

class NetData{
    init(address:String){
        //インターネットから指定されたユーザーのデータを取得する処理
    }
}

//personクラスのインスタンスを生成。この時点ではnetDataプロパティの値は未確定。
var person = Person(firstName: "Hanako", lastName: "Sakura")

//何か処理する
...

//利用するタイミングでデータが取得される
println(person.netData)
