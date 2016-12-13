import UIKit
class ViewController: UIViewController {
    @IBOutlet weak var tappedLabel: UILabel!
    @IBOutlet weak var eggButton: UIButton!
    @IBAction func eggTapped(sender: AnyObject) {
        eggButton.tag += 1
        tappedLabel.text = "Tapped \(eggButton.tag) times"
        if eggButton.tag >= 15 {setImg("egg_hakk")}
        if eggButton.tag >= 30 {setImg("kylling")}
        if eggButton.tag >= 45 {setImg("kylling_splat")}
    }
    func setImg(name:String){
        eggButton.setBackgroundImage(UIImage(named: name), forState: .Normal)
    }
}
