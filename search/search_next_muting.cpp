byte TEA5767N::searchNextMuting() {
  byte bandLimitReached;
	
  mute();
  bandLimitReached = searchNext();
  turnTheSoundBackOn();
	
  return bandLimitReached;
}
