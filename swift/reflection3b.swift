extension Vector: CustomReflectable {          

    func customMirror() -> Mirror {                 
        return Mirror(self, children: [                         
            "start": "\(start.x) × \(start.y)",                         
            "end": "\(end.x) × \(end.y)",                         
            "length": length                 
        ])         
    }
 
 }
