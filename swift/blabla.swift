import Foundation

class ServerRequest: NSObject
{
    private var request: NSURLRequest!
    typealias completionType = (NSData?, NSError?, ServerRequest) -> ()
    private var completion: completionType!
    private var receivedData: NSMutableData?
    private var connection: NSURLConnection?
    
    var unauthorizedErrorHandler: ((statusCode: Int) -> ())?
    
    init(request: NSURLRequest, completion: (NSData?, NSError?, ServerRequest) -> ())
    {
        super.init()
        
        self.request = request
        self.completion = completion
        self.connection = NSURLConnection(request: self.request, delegate: self, startImmediately:false)
        //this line will help connection is fired even while tere are touch events
        self.connection?.scheduleInRunLoop(NSRunLoop.currentRunLoop(), forMode: NSRunLoopCommonModes)
    }
    
    func send()
    {
        receivedData = NSMutableData()
        
        self.connection?.start()
    }
    
    func abort()
    {
        self.connection?.cancel()
        
        self.completion(nil, NSError(domain: "\(self.dynamicType)", code: 1001, userInfo: nil), self)
        unauthorizedErrorHandler?(statusCode: 1001)
    }
}

extension ServerRequest: NSURLConnectionDataDelegate, NSURLConnectionDelegate
{
    func connection(connection: NSURLConnection, didReceiveResponse response: NSURLResponse)
    {
        self.receivedData?.length = 0
    }
    
    func connection(connection: NSURLConnection, didReceiveData data: NSData)
    {
        self.receivedData?.appendData(data)
    }

    func connection(connection: NSURLConnection, didFailWithError error: NSError)
    {
        unauthorizedErrorHandler?(statusCode: error.code)
        
        self.completion(nil, error, self)
    }

    func connectionDidFinishLoading(connection: NSURLConnection)
    {
        unauthorizedErrorHandler?(statusCode: -1)
        
        self.completion(receivedData, nil, self)
    }
    
    //MARK: https specific(canAuthenticateAgainstProtectionSpace is depraceted first in iOS 8)
    func connection(connection: NSURLConnection, canAuthenticateAgainstProtectionSpace protectionSpace: NSURLProtectionSpace) -> Bool
    {
        return protectionSpace.authenticationMethod == NSURLAuthenticationMethodServerTrust
    }
    
    func connection(connection: NSURLConnection, willSendRequestForAuthenticationChallenge challenge: NSURLAuthenticationChallenge)
    {
        if let sender = challenge.sender
        {
            if let trust = challenge.protectionSpace.serverTrust
            {
                sender.useCredential(NSURLCredential(forTrust: trust), forAuthenticationChallenge: challenge)
            }
            sender.continueWithoutCredentialForAuthenticationChallenge(challenge)
        }
    }

}
