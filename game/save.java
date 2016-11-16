public void save(SharedPreferences.Editor map) {
		
		if (map == null) {			
			return;
		}
		
		map.putInt("game_saved", 1);

		map.putInt("game_highScore", highScore);		
		
		// save game vars
		if (lastPothole == null) {
			map.putInt("game_lastPotHole_id", -1);
		}
		else {
			map.putInt("game_lastPotHole_id", lastPothole.id);
		}
		
		map.putLong("game_spawnPotholeTicks", spawnPotholeTime);
		map.putBoolean("game_playerTap", playerTap);
		map.putInt("game_gameState", gameState);
		map.putLong("game_tapToStartTime", tapToStartTime);
		map.putBoolean("game_showTapToStart", showTapToStart);
		map.putLong("game_getReadyGoTime", getReadyGoTime);
		map.putInt("game_getReadyGoState", getReadyGoState);
		map.putLong("game_gameOverTime", gameOverTime);

		map.putInt("game_lastGameState", lastGameState);
		map.putLong("game_pauseStartTime", pauseStartTime);
		
		map.putLong("game_spawnPastryTime", spawnPastryTime);
		
		map.putLong("game_scoreTime", scoreTime);
		map.putInt("game_curScore", curScore);
		
		// save game entities
		
		droid.save(map);
		
		for (Pothole p : potholes) {
			p.save(map);
		}
		
		pastry.save(map);
		
		road.save(map);
		
		//
		// store saved variables
		//
		map.commit();
	}
