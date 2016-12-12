public struct Connection {
    public var request: HttpRequest
    public var response: HttpResponseProtocol
    
    public var urlParams: [(String, String)] = []
    
    public init(request: HttpRequest) {
        self.request = request
        self.response = HttpResponse()
    }
    
    // func halt() -> sends response
}
