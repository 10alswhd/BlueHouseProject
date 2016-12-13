class MyManager  {
    private static let sharedInstance = MyManager()
    class var sharedManager : MyManager {
        return sharedInstance
    }
}
