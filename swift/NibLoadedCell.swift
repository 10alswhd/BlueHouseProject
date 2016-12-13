//
//  NibLoadedCell.swift
//
//  Created by Marcel Dierkes on 08.11.15.
//  Copyright © 2015 Marcel Dierkes. All rights reserved.
//
import UIKit

/// This protocol simplified UITableViewCell/UICollectionViewCell registering and 
/// dequeueing for cells loaded from custom nib files.
public protocol NibLoadedCell: class {
    static var cellIdentifier: String { get }
    static var nibName: String  { get }
}

public extension NibLoadedCell {
    
    /// A default implementation for cellIdentifier consisting of the implementer's class name.
    public static var cellIdentifier: String {
        return NSStringFromClass(self) + "Identifier"
    }

    /// A default implementation for nibName where the nib file is named after the implementer's class name.
    public static var nibName: String {
        let components = NSStringFromClass(self).characters.split() { $0 == "." }.map(String.init)
        if let className = components.last {
            return className
        } else {
            return NSStringFromClass(self)
        }
    }
}

// MARK: - UITableView
public extension NibLoadedCell where Self: UITableViewCell {
    
    /**
     Register a nib-loaded table view cell for a table view.
     
     - parameter tableView: A UITableView that will be used to dequeue the registered cell.
    */
    public static func registerInTableView(tableView: UITableView) {
        tableView.registerNib(UINib(nibName: self.nibName, bundle: NSBundle(forClass: self)), forCellReuseIdentifier: self.cellIdentifier)
    }
}

public extension UITableView {
    
    /**
     Dequeue a previously registered nib-loaded table view cell for a specific indexPath.
     
     Make sure to specify the table view cell type around this method, e.g.:
     
         let cell = tableView.dequeueNibLoadedTableViewCellForIndexPath(indexPath) as CustomCell
     
     - parameter indexPath: A valid NSIndexPath
     
     - returns: A dequeued cell
    */
    public func dequeueNibLoadedCellForIndexPath<CellType: NibLoadedCell>(indexPath: NSIndexPath) -> CellType {
        guard let cell = self.dequeueReusableCellWithIdentifier(CellType.cellIdentifier, forIndexPath: indexPath) as? CellType else {
            fatalError("The requested cell type was not registered for this table view.")
        }
        return cell
    }
}

// MARK: - UITableView Header Footer Views
public extension NibLoadedCell where Self: UITableViewHeaderFooterView {
    
    /**
     Register a nib-loaded table view header footer view for a table view.
     
     - parameter tableView: A UITableView that will be used to dequeue the registered view.
     */
    public static func registerInTableView(tableView: UITableView) {
        tableView.registerNib(UINib(nibName: self.nibName, bundle: NSBundle(forClass: self)), forHeaderFooterViewReuseIdentifier: self.cellIdentifier)
    }
}

public extension UITableView {
    
    /**
     Dequeue a previously registered nib-loaded header footer view for a specific indexPath.
     
     Make sure to specify the table view cell type around this method, e.g.:
     
         let cell = tableView.dequeueNibLoadedHeaderFooterView() as CustomHeaderFooterView
     
     - returns: A dequeued header footer view
    */
    public func dequeueNibLoadedHeaderFooterView<CellType: NibLoadedCell>() -> CellType {
        guard let cell = self.dequeueReusableHeaderFooterViewWithIdentifier(CellType.cellIdentifier) as? CellType else {
            fatalError("The requested header footer view type was not registered for this table view.")
        }
        return cell
    }
}

// MARK: - UICollectionView
public extension NibLoadedCell where Self: UICollectionViewCell {
    
    /**
     Register a nib-loaded collection view cell for a collection view.
     
     - parameter collectionView: A UICollectionView that will be used to dequeue the registered cell.
    */
    public static func registerInCollectionView(collectionView: UICollectionView) {
        collectionView.registerNib(UINib(nibName: self.nibName, bundle: NSBundle(forClass: self)), forCellWithReuseIdentifier: self.cellIdentifier)
    }
}

public extension UICollectionView {
    
    /**
     Dequeue a previously registered nib-loaded collection view cell.
     
     Make sure to specify the collection view cell type around this method, e.g.:
     
         let cell = collectionView.dequeueNibLoadedCollectionViewCellForIndexPath(indexPath) as CustomCell
     
     - parameter indexPath: A valid NSIndexPath
     
     - returns: A dequeued cell
    */
    public func dequeueNibLoadedCellForIndexPath<CellType: NibLoadedCell>(indexPath: NSIndexPath) -> CellType {
        guard let cell = self.dequeueReusableCellWithReuseIdentifier(CellType.cellIdentifier, forIndexPath: indexPath) as? CellType else {
            fatalError("The requested cell type was not registered for this collection view.")
        }
        return cell
    }
}

// MARK: - UICollectionReusableView Reusable View
public extension NibLoadedCell where Self: UICollectionReusableView {
    
    /**
     Register a nib-loaded reusable view for a collection view.
     
     - parameter collectionView: A UICollectionView that will be used to dequeue the registered cell.
     - parameter kind:           The kind of supplementary view to create.
     */
    public static func registerInCollectionView(collectionView: UICollectionView, kind: String) {
        collectionView.registerNib(UINib(nibName: self.nibName, bundle: NSBundle(forClass: self)), forSupplementaryViewOfKind: kind, withReuseIdentifier: self.cellIdentifier)
    }
}

public extension UICollectionView {
    
    /**
     Dequeue a previously registered nib-loaded reusable view for a specific indexPath.
     
     - parameter kind: The kind of supplementary view to create.
     
     - returns: A dequeued reusable view
     */
    public func dequeueNibLoadedReusableViewForIndexPath<CellType: NibLoadedCell>(indexPath: NSIndexPath, kind: String) -> CellType {
        guard let cell = self.dequeueReusableSupplementaryViewOfKind(kind, withReuseIdentifier: CellType.cellIdentifier, forIndexPath: indexPath) as? CellType else {
            fatalError("The requested reusable view type was not registered for this collection view.")
        }
        return cell
    }
}
