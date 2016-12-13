override func viewDidLoad() {
    ...
    self.highlightFirstLineInTextView(self.textView)
}

private func highlightFirstLineInTextView(textView: UITextView) {
    let textAsNSString = textView.text as NSString
    let lineBreakRange = textAsNSString.rangeOfString("\n")
    let newAttributedText = NSMutableAttributedString(attributedString: textView.attributedText)
    let boldRange: NSRange
    if lineBreakRange.location < textAsNSString.length {
        boldRange = NSRange(location: 0, length: lineBreakRange.location)
    } else {
        boldRange = NSRange(location: 0, length: textAsNSString.length)
    }
    
    newAttributedText.addAttribute(NSFontAttributeName, value: UIFont.preferredFontForTextStyle(UIFontTextStyleHeadline), range: boldRange)
    textView.attributedText = newAttributedText
}
