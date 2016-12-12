func sayHello(personName: String) -> String {
    //personNameに"aiueoが代入される"
    let greeting = "Hello, " + personName + "!"
    //greetingにはHello, aiueo!が代入される
    return greeting
}

//sayHello関数を呼び出す
sayHello("aiueo")
