//
//  ViewController.swift
//  GrandCentralDispatch

import UIKit

enum ImageTypes: String{
    case downloadImage = "https://lh3.googleusercontent.com/BCoVLCGTcWErtKbD9Nx7vNKlQ0R3RDsBpOa8iA70mGW2XcC76jKS09pDX_Rad6rjyXQCxngEYi3Sy3uJgd99=s0#w=4713&h=3846"
    
}


class ViewController: UIViewController {
    
    //MARK: IBOutlets
    @IBOutlet weak var photoView: UIImageView!
    @IBOutlet weak var activityView: UIActivityIndicatorView!
    
    // Downloads large image on main thread, blocks UI
    @IBAction func synchronousDownload(sender: UIButton ) {
        
        photoView.image = nil
        
        activityView.startAnimating()
        
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 1), dispatch_get_main_queue()) { () -> Void in

            if let url = NSURL(string: ImageTypes.downloadImage.rawValue),
                let imgData = NSData(contentsOfURL: url),
                let image = UIImage(data: imgData){
                    
                    self.photoView.image = image
                    
                    self.activityView.stopAnimating()
            }
            
        }
        
        
    }
    
    // Creates a new queue, runs in the background, doesn't block UI
    @IBAction func simpleAsynchronousDownload(sender: UIButton) {
        
        photoView.image = nil
        
        activityView.startAnimating()
        
        let url = NSURL(string: ImageTypes.downloadImage.rawValue)
        
        //  create queue
        let downloadQueue = dispatch_queue_create("download", nil)
        
        // use dispatch_async
        dispatch_async(downloadQueue) { () -> Void in
            let imgData = NSData(contentsOfURL: url!)
            
            let image = UIImage(data: imgData!)
            
            // run code that updates UI on main thread
            dispatch_async(dispatch_get_main_queue(), { () -> Void in
                self.photoView.image = image
                
                self.activityView.stopAnimating()
            })
        }
        
    }
    
    // This code downloads the huge image in a global queue and uses a completion
    // closure.
    @IBAction func asynchronousDownload(sender: UIButton) {
        
        photoView.image = nil
        
        activityView.startAnimating()
        
        downloadImageMethod { (image) -> Void in
            self.photoView.image = image
            
            self.activityView.stopAnimating()
        }
    }
    
    // method downloads the image in background, runs closure (completion handler).
    // Process: once done downloading image, run completion handler
    func downloadImageMethod(completionHandler handler: (image: UIImage) -> Void){
        
        // use global queue
        dispatch_async(dispatch_get_global_queue(QOS_CLASS_USER_INITIATED, 0)) { () -> Void in
            
            if let url = NSURL(string: ImageTypes.downloadImage.rawValue),
                let imgData = NSData(contentsOfURL: url),
                let img = UIImage(data: imgData){
                    
                    // run completion block, ALWAYS in main queue
                    dispatch_async(dispatch_get_main_queue(), { () -> Void in
                        handler(image: img)
                        
                        
                })
            }
        }
    }
    
    // Change transparency of image (alpha value)
    @IBAction func setTransparencyOfImage(sender: UISlider) {
        
        photoView.alpha = CGFloat(sender.value)
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    
}
