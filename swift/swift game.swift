import Foundation

class Player {
    
    let colorkey = [ "joker": "j", "black": "bk", "blue": "b", "yellow": "y", "red": "r" ]
    var name = String()
    var rack = Array<Dictionary<String,Any>>()
    init(name: String, rack: Array<Dictionary<String,Any>>) {
        self.name = name
        self.rack = rack
    }
    
    func getRack() -> Array<Dictionary<String,Any>> {
        return rack
    }
    
    func displayRack() -> Array<Dictionary<String,Any>> {
        
        println("     ----- [Rack] -----")
        
        var option = 0
        for tile in rack {
            if (option % 4 == 0) {
                println()
            }
            print("\(option) - ")
            print("[")
            print(tile["number"] as Int)
            print(",")
            print(colorkey[tile["color"] as String] as String)
            print("]  ")
            option++
        }
        println()
        return rack
    }
    
    func input() -> String {
        var keyboard = NSFileHandle.fileHandleWithStandardInput()
        var inputData = keyboard.availableData
        return NSString(data: inputData, encoding: NSUTF8StringEncoding)
    }
    
}
 
class Sets {
    var sets = Array<Dictionary<String,Any>>()
 
    init(sets: Array<Dictionary<String,Any>>) {
        self.sets = sets
    }
    
    func sumOfTiles() -> Int {
        var total = 0
        for idx in 0..<sets.count {
            total += sets[idx]["number"] as Int
        }
        return total
    }
 
    func validateSetRun() -> Bool {
        if sets.count <= 2 {
            return false
        }
        
        var a_number = sets[0]["number"] as Int
        // var rev_a_number = sets[0]["number"] as Int
        var a_color = sets[0]["color"] as String
 
        for idx in 0..<sets.count {
            var current_number = sets[idx]["number"] as Int
            var current_color = sets[idx]["color"] as String
            if a_number != current_number && a_color != current_color && current_color != "joker" {
                return false
            }
            a_number++
        }
        return true
    }
 
    /*  This function validates set Groups by comparing the first
        element in a set to the others. Valid groups must contain 
        a minimum of 3 tiles. i.e. red(7), black(7), blue(7)
    */
    func validateSetGroup() -> Bool {
        var a_number = sets[0]["number"] as Int
        var a_color = sets[0]["color"] as String
        var colorCount = 0

        for set in sets {
            println(set)
        }
        
        if sets.count <= 2 {
            return false
        }
        
        
        for tile in sets {
            
            if a_number == 0 {
                continue
            }
            
            var x = tile["number"] as Int

            if (a_number != tile["number"] as Int) && (tile["number"] as Int != 0) {
                return false
            }
            
            if (a_color == tile["color"] as String) && (tile["color"] as String != "joker") {
                colorCount += 1
            }
            
            // Check how many times we see a_color in the list
            if colorCount > 1 {
                print("ColorCount: \(colorCount)")
                return false
            }
        }
        return true
    }
}
 
class Bukimur {
    
    let MAX_TILES = 104
    var players = 0
    var bag = Array<Dictionary<String,Any>>()
    var board = Array<Array<Dictionary<String,Any>>>()
 
    init(players: Int) {
        self.players = players
        //println("----- Initalizing game with \(players) players -----")
    }
 
    func dealTiles(n: Int) -> Array<Dictionary<String,Any>> {
        println("Dealing \(n) tiles to player...")
        var tiles = Array<Dictionary<String,Any>>()
        var sets = Array<Dictionary<String,Any>>()
        for i in 0...n-1 {
            tiles.append(bag[i])
            bag.removeAtIndex(i)
        }
        return tiles
    }
 
    func shuffle<T>(var list: Array<T>) -> Array<T> {
        for i in 0..<list.count {
            let j = Int(arc4random_uniform(UInt32(list.count - i))) + i
            list.insert(list.removeAtIndex(j), atIndex: i)
        }
        return list
    }
 
    func initalizeGame() -> Bool {
 
        let decks = [0,1]
        let colors = ["yellow", "black", "red", "blue"]
        let numbers = [1,2,3,4,5,6,7,8,9,10,11,12,13]

        for color in colors {
            for deck in decks {
                for num in numbers {
                    bag.append(["color": color, "deck": deck, "number": num])
                }
            }
        }
        
        // Add the jokers to the deck
        bag.append(["color": "joker", "deck": 0, "number": 0])
        bag.append(["color": "joker", "deck": 1, "number": 0])
 
        self.bag = self.shuffle(self.bag)

        return true
    }
}
 
var game = Bukimur(players: 4)

if game.initalizeGame() {
    
    var player = Player(name: "Bill", rack: game.dealTiles(14))
    var tiles = Array<Dictionary<String,Any>>()
    
    player.displayRack()
    // println(player.getRack())
    print("Enter a valid run > ")
    var inputData = player.input()
    // TODO: Need to add a check for 0 or . to exit application calls exit(-1)
    let tileNumber = 0
    while(true) { // Main input loop for game logic
        for tileNumber in inputData {
            let n = String(tileNumber).toInt()
            if !n {
                continue
            }
            tiles.append(player.rack[n!])
        }
        print("Validating set.....")
        
        if !Sets(sets: tiles).validateSetRun() || !Sets(sets: tiles).validateSetGroup() {
            println("Invalid run sorry!")
            exit(-1)
        }
        println("Valid Set run awesome!!!")
        exit(0)
    }
    
    // var playerSets = Sets(sets:[["color": "red", "deck": 0, "number": 4], ["color": "red", "deck": 0, "number": 5],["color": "joker", "deck": 0, "number": 0]])
    
}
