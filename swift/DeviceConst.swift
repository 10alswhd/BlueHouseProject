//
//  AppConst.swift
//  AdBlockSample
//
//  Created by bright on 2016/11/26.
//  Copyright © 2016年 bright. All rights reserved.
//
import Foundation
import UIKit

final class DeviceConst {
    let osName          = "iOS"
    // NOTE: コストの高い変数(定数)は、lazy をつけてクラスの初期化コストを抑えた方が良さそう(遅延評価)
    // 但し、このは場合は大した処理でもないのでほとんど変わらないと思いますが。。。
    lazy var osVersion  = UIDevice.current.systemVersion
    lazy var appVersion = Bundle.main.infoDictionary?["CFBundleShortVersionString"] as? String ?? ""
    lazy var appName    = Bundle.main.infoDictionary?["CFBundleName"] as? String ?? ""
    lazy var appId      = Bundle.main.infoDictionary?["CFBundleIdentifier"] as? String ?? ""
    // 定数といいつつvarじゃないかとツッコまれそうですが、lazy let は書けないので苦し紛れに。。。
    
    // NOTE: クラスインスタンスの作成を避けたい場合
    static let hoge = "bar"
    
    // NOTE: どう書くかは好みだと思いますが、一行で書きづらいものや、
    // 自身の定数を組み合わせて返却するものとかは、計算型プロパティとか使うと良いんじゃないかなと個人的に思う。
    var spec: String {
        return self.osName + self.osVersion + self.appVersion
    }
    
}
