//  Created by Joseph Neuman
import Foundation

func getBool(object:AnyObject?) -> Bool? {
  return object as AnyObject? as? Bool
}

func getDate(object:AnyObject?) -> NSDate? {
  if let tempObject = object as AnyObject? as? String {
    return  getDateFormatter().dateFromString(tempObject)
  } else {
    return nil
  }
}

func getDictionary(object:AnyObject?) -> Dictionary<String, AnyObject>? {
  return object as AnyObject? as? Dictionary<String, AnyObject>
}

func getString(object:AnyObject?) -> String? {
  if let temp: AnyObject = object as AnyObject? {
    if let temp2 = temp as? String {
      return temp2
    } else if let temp2 = temp as? Int {
      return String(temp2)
    } else {
      return nil
    }
  } else {
    return nil
  }
}
