import UIKit
import PlaygroundSupport
var vc = UIViewController()
if let v = vc.view {
    var 🤔 = UILabel(frame: CGRect(x: 0, y: 0, width: 128, height: 128))
    🤔.center = CGPoint(x: v.frame.width / 2 - 40, y: 120)
    🤔.font = UIFont.systemFont(ofSize: 64)
    🤔.text = "🤔"
    🤔.textAlignment = NSTextAlignment.center
    v.addSubview(🤔)
}
PlaygroundPage.current.liveView = vc
