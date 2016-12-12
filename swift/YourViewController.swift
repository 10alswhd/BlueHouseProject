/*
// Subclass UIViewController
*/
class YourViewController: UIViewController {
    
    // Add constant with UICollectionViewCell identifier
    private let reuseIdentifier = "YourCell"

    //Xcode-generated code here
}

/*
// Implement UICollectionViewDataSource protocol via Swift extension
*/
extension YourViewController : UICollectionViewDataSource {
    // Optional
    func numberOfSectionsInCollectionView(collectionView: UICollectionView) -> Int {
        return 0
    }
    
    // Required
    func collectionView(collectionView: UICollectionView, numberOfItemsInSection section: Int) -> Int {
        return 0
    }
    
    // Required
    func collectionView(collectionView: UICollectionView, cellForItemAtIndexPath indexPath: NSIndexPath) -> UICollectionViewCell {
        
        let cell = collectionView.dequeueReusableCellWithReuseIdentifier(reuseIdentifier, forIndexPath: indexPath) as! UICollectionViewCell
        
        return cell
    }
}

/*
// Implement UICollectionViewDelegateFlowLayout protocol via Swift extension
*/
extension YourViewController : UICollectionViewDelegateFlowLayout {
    
    // Optional
    func collectionView(collectionView: UICollectionView, layout collectionViewLayout: UICollectionViewLayout, sizeForItemAtIndexPath indexPath: NSIndexPath) -> CGSize {
        
        let sideSize = collectionView.frame.size.width / 5 - 10;
        return CGSize(width: sideSize, height: sideSize);
    }
    
}
