let nTaple = (1, -1)
switch nTaple {
case let (x, y) where x == y:
    print("xとyが等しい")
case let (x, y) where x == -y:
    print("xと-yが等しい")
case let (x, y):
    print("上記以外")
}
//結果
//xと-yが等しい
