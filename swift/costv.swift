func touchVisualizerWindowShouldAlwaysShowFingertip(window: COSTouchVisualizerWindow!) -> Bool {
    // Return YES to make the fingertip always display even if there's no any mirrored screen.
    // Return NO or don't implement this method if you want to keep the fingertip display only when
    // the device is connected to a mirrored screen.
    return true
}

func touchVisualizerWindowShouldShowFingertip(window: COSTouchVisualizerWindow!) -> Bool {
    // Return YES or don't implement this method to make this window show fingertip when necessary.
    // Return NO to make this window not to show fingertip.
    return true
}
