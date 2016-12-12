 /*! accepts event names and prints out time interval (seconds) since last event given  */
    struct Benchmarker {
        
        struct Event {
            let time: NSDate
            let name: String
        }
        
        static var events = [Event]()
        static let prefix = "--------\n--------\n--------\nBENCHMARK\n--------\n--------\n--------\n"
        
        static func benchmark(eventName: String) {
            let event = Event(time: NSDate(), name: eventName)
            
            if let last = events.last {
                debugPrint("\(prefix)\(event.name)! \(event.time.timeIntervalSinceDate(last.time)) seconds since \(last.name)")
            } else {
                debugPrint("\(prefix)\(event.name)!")
            }
            
            events.append(event)
        }
        
        static func clear() {
            events = [Event]()
        }
        
        static func complete(eventName: String) {
            benchmark(eventName)
            clear()
        }
    }
