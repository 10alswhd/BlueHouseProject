// ------- Delegate Pattern / Protocols ------------

protocol BadGuyProtocol{

    var life: Int { get set } //computed property
    func takeDamage(damage: Int)
}

protocol PowerOfActionProtocol {
    
    func attack(target: BadGuyProtocol)
}

// +++++++++++++++++++++++++++++++++++++++++


//implement the protocol method PowerOfActionProtocol which has a method attack(atTarget)
class Punch: PowerOfActionProtocol {
    
    func attack(target: BadGuyProtocol) { // when using Punch, target will lose 1
        target.takeDamage(1)
    }
}

class DropKick: PowerOfActionProtocol {
    
    func attack(target: BadGuyProtocol) {  // when using DropKick, target will lose 5
        target.takeDamage(5)
    }
}

// +++++++++++++++++++++++++++++++++++++++++

// BadGuy Class must implement protocol
class BadGuy: BadGuyProtocol{
    
    var life: Int = 10
    
    func takeDamage(damage: Int) {
        life -= damage
                print("thief lost \(damage) life points")
        
        if life <= 0 {
                print("thief is sleeping now")
        }
    }
}

// GoodGuy Class doesnt implement any protocols
class GoodGuy {

    var action: PowerOfActionProtocol! // property action
    init(action: PowerOfActionProtocol) {  // constructor to set action to object.
        self.action = action
    }
    // GoodGuy class delegates the shot behavior/logic to the action of choice
    // the action of choice class will determine what happens. 
    func attackTowards(target: BadGuyProtocol) {
        // chooses either Punch or DropKick class method
        action.attack(target)
    }
}

// created a new GoodGuy w/ action
var owner = GoodGuy(action: Punch())
var thief = BadGuy()

owner.attackTowards(thief) //action: Punch
owner.attackTowards(thief) //> thief lost 1 hit points
owner.attackTowards(thief) //> thief lost 1 hit points
owner.attackTowards(thief) //> thief lost 1 hit points
thief.life // 6
owner.attackTowards(thief) //> thief lost 1 hit points
owner.action = DropKick() // changing action because the Punch is inefficient
owner.attackTowards(thief) //> thief lost 5 hit points
//> thief is sleeping now
