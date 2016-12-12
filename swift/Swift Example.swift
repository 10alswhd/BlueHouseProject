func invisibleButtonTapped(sender: UIButton!)
{
    var playerIsPlaying:Bool = self.avPlayer.rate > 0
    if (playerIsPlaying) {
        self.avPlayer.pause();
    } else {
        self.avPlayer.play();
    }
}
