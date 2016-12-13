import Foundation

class Singleton {
    
    class func sharedInstance() -> Singleton {
        
        struct Static {
            static var instance: Singleton? = nil
            static var onceToken: dispatch_once_t = 0
        }
        
        dispatch_once(&Static.onceToken) {
            Static.instance = self()
        }
        return Static.instance!
    }
    
    @required init() {
    }
}
