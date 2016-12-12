import UIKit

enum StoryboardType: String {
    case None = ""
    case Main = "Main"
    func storyboard() -> UIStoryboard {
        let storyboard = UIStoryboard(name: self.rawValue, bundle:nil)
        return storyboard
    }
}

protocol StoryboardCoordinator {
    class func storyboardType() -> StoryboardType
}

class BaseViewController: UIViewController {
    class func storyboardType() -> StoryboardType {
        return .None
    }
    
    class func instantiateFromStoryboard() -> Self {
        return self.instantiateFromType()
    }
    
    private class func instantiateFromType<T: UIViewController>() -> T {
        let storyboard = self.storyboardType().storyboard()
        return storyboard.instantiateViewControllerWithIdentifier(self.classNameInAppModule()) as T
    }
}
