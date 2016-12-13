struct Square{
    var width=0
    var height=0
    
    func area()->Int{
        return width*height
    }
    
    func printArea(){        
        print("area \(area())")
    }
}
