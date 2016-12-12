import JavaScriptCore

let println: @objc_block AnyObject! -> Void = { object in
    Swift.println(object)
}
