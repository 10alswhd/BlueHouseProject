struct Vector {
  
    typealias Position = (x: Double, y: Double)          
        
    let start: Position         
    let end: Position          
        
    var length: Double {                 
        return sqrt(                         
            pow(end.x - start.x, 2) +                         
            pow(end.y - start.y, 2)                
        )          
    }

  }
