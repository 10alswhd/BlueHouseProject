func application(application: UIApplication, didFinishLaunchingWithOptions launchOptions: [NSObject: AnyObject]?) -> Bool {

Parse.setApplicationId("AppId",
  clientKey: "ClientId")
Parse.enableLocalDatastore()

return true
}
