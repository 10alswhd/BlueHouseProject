//
//  SwiftHttp.swift
//
//  Created by Lihnux on 7/2/15.
//
import Foundation


class SwitfHttp: NSObject, NSURLSessionDelegate, NSURLSessionTaskDelegate {
    
    typealias HttpCallback = (result: NSData?, error: String?) -> ()
    
    //var httpCallback: HttpCallback? = nil
    
    func httpGet(url: NSURL!, callback: HttpCallback?) {
        
        var configuration = NSURLSessionConfiguration.defaultSessionConfiguration()
        var session = NSURLSession(configuration: configuration, delegate: self, delegateQueue:NSOperationQueue())
        
        var task = session.dataTaskWithURL(url, completionHandler: { (data, response, error) -> Void in
            
            if callback != nil {
                if error != nil {
                    callback!(result: nil, error: error.localizedDescription)
                }
                else {
                    callback!(result: data, error: nil)
                }
            }
            
        })
        
        task.resume()
    }
    
    func URLSession(session: NSURLSession, didReceiveChallenge challenge: NSURLAuthenticationChallenge, completionHandler: (NSURLSessionAuthChallengeDisposition, NSURLCredential!) -> Void) {
        
        println("\(challenge.protectionSpace.authenticationMethod)")
        
        if challenge.protectionSpace.authenticationMethod == NSURLAuthenticationMethodServerTrust {
            
            var certificateCount = SecTrustGetCertificateCount(challenge.protectionSpace.serverTrust)
            
            var result: SecTrustResultType = 0
            SecTrustEvaluate(challenge.protectionSpace.serverTrust, &result)
            
            /*
            @From https://developer.apple.com/library/prerelease/ios//documentation/Security/Reference/certifkeytrustservices/index.html#//apple_ref/c/tdef/SecTrustResultType
            kSecTrustResultUnspecified
                Evaluation successfully reached an (implicitly trusted) anchor certificate without any evaluation failures, but never encountered any explicitly stated user-trust preference. This is the most common return value.
                Most apps should, by default, trust the chain. If you ask the user what to do, in OS X, you should use the SFCertificateTrustPanel class in the Security Interface Framework Reference.
            
            kSecTrustResultProceed
                The user explicitly chose to trust a certificate in the chain (usually by clicking a button in a certificate trust panel).
                Your app should trust the chain.
            
            kSecTrustResultDeny
                The user explicitly chose to not trust a certificate in the chain (usually by clicking the appropriate button in a certificate trust panel).
                Your app should not trust the chain.
            
            kSecTrustResultConfirm
                The user previously chose to always ask for permission before accepting one of the certificates in the chain. This return value is no longer used, but may occur in older versions of OS X.
                Either ask the user what to do or reject the certificate. If you ask the user what to do, in OS X, you should use the SFCertificateTrustPanel class in the Security Interface Framework Reference.
            
            kSecTrustResultRecoverableTrustFailure
                This means that you should not trust the chain as-is, but that the chain could be trusted with some minor change to the evaluation context, such as ignoring expired certificates or adding an additional anchor to the set of trusted anchors.
                The way you handle this depends on the OS.
            
            kSecTrustResultFatalTrustFailure
                Evaluation failed because a certificate in the chain is defective. This usually represents a fundamental defect in the certificate data, such as an invalid encoding for a critical subjectAltName extension, an unsupported critical extension, or some other critical portion of the certificate that could not be successfully interpreted. Changing parameter values and calling SecTrustEvaluate again is unlikely to result in a successful reevaluation unless you provide different certificates.
            
            kSecTrustResultOtherError
                Evaluation failed for some other reason. This can be caused by either a revoked certificate or by OS-level errors that are unrelated to the certificates themselves.
            */
            
            switch Int(result) {
            case kSecTrustResultDeny, kSecTrustResultRecoverableTrustFailure, kSecTrustResultFatalTrustFailure, kSecTrustResultOtherError:
                println("Server Cerificate Issue: \(result)")
                
                println("Server Certificate List Count \(certificateCount)")
                
                for i in 0 ..< certificateCount {
                    
                    let certificate = SecTrustGetCertificateAtIndex(challenge.protectionSpace.serverTrust!, i).takeUnretainedValue()
                    let serverCertData = SecCertificateCopyData(certificate).takeRetainedValue()
                    var commonName = UnsafeMutablePointer<Unmanaged<CFString>?>.alloc(1)
                    SecCertificateCopyCommonName(certificate, commonName)
                    println("\(commonName.memory?.takeUnretainedValue())")
                    commonName.memory?.release()
                    commonName.dealloc(1)
                }
            default:
                println("Server Cerificate OK")
                var credential = NSURLCredential(forTrust: challenge.protectionSpace.serverTrust!)
                completionHandler(NSURLSessionAuthChallengeDisposition.UseCredential, credential);
            }
        }
    }
    
    func URLSession(session: NSURLSession, task: NSURLSessionTask, willPerformHTTPRedirection response: NSHTTPURLResponse, newRequest request: NSURLRequest, completionHandler: (NSURLRequest!) -> Void) {
            var newRequest : NSURLRequest? = request
            println(newRequest?.description);
            completionHandler(newRequest)
    }
}
