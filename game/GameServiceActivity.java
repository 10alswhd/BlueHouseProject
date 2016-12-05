package com.ozateck.oyadius4;

import android.app.Activity;
import android.os.Bundle;
import android.content.Intent;
import android.util.Log;
import android.widget.Toast;

import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.games.Games;

import com.ozateck.gameservice.*;

public class GameServiceActivity extends ShimejiActivity
				implements GameHelper.GameHelperListener{
	
	private final static String TAG = "GameServiceActivity";

	private static GameHelper mHelper;

	public static final int CLIENT_GAMES = GameHelper.CLIENT_GAMES;
	public static final int CLIENT_APPSTATE = GameHelper.CLIENT_APPSTATE;
	public static final int CLIENT_PLUS = GameHelper.CLIENT_PLUS;
	public static final int CLIENT_ALL = GameHelper.CLIENT_ALL;

	protected static final boolean DEBUG_LOG = false;
	protected static final int REQUEST_CODE = 7777;

	// Singleton model
	public static GameHelper getGameHelper(Activity activity){
		if (mHelper == null){
			mHelper = new GameHelper(activity, GameHelper.CLIENT_GAMES);
			mHelper.enableDebugLog(DEBUG_LOG);
			return mHelper;
		}
		return mHelper;
	}

	@Override
	protected void onCreate(Bundle icicle){
		super.onCreate(icicle);
		
		getGameHelper(this);
		mHelper.setup(this);
	}
	
	@Override
	protected void onStart(){
		super.onStart();
		
		// Cocos2dx
		// AppDelegate::applicationDidFinishLaunchingから呼び出す事
		//onStartGameService();
	}
	
	@Override
	protected void onStop(){
		super.onStop();
		
		onStopGameService();
	}

	@Override
	protected void onDestroy(){
		super.onDestroy();
		
		mHelper = null;
	}

	@Override
	protected void onActivityResult(int request, int response, Intent data) {
		super.onActivityResult(request, response, data);
		
		mHelper.onActivityResult(request, response, data);
	}
	
	protected GoogleApiClient getApiClient(){
		return mHelper.getApiClient();
	}

	protected boolean isSignedIn(){
		return mHelper.isSignedIn();
	}

	protected void beginUserInitiatedSignIn(){
		mHelper.beginUserInitiatedSignIn();
	}

	protected void signOut() {
		mHelper.signOut();
	}

	@Override
	public void onSignInSucceeded(){
		
		Log.d(TAG, "onSignInSucceeded");
		//Toast.makeText(this, "onSignInSucceeded", Toast.LENGTH_LONG).show();
	}

	@Override
	public void onSignInFailed(){
		
		Log.w(TAG, "onSignInFailed");
		//Toast.makeText(this, "onSignInFailed", Toast.LENGTH_LONG).show();
	}
	
	//==========
	// JNI
	//==========

	// Cocos2dx(Log in)
	// AppDelegate::applicationDidEnterForgroundから呼び出す事
	public static void onStartGameService(){
		if(mActivity.isOnline() == false) return;
		mHelper.onStart(mActivity);
	}

	// Cocos2dx(Log out)
	public static void onStopGameService(){
		if(mActivity.isOnline() == false) return;
		mHelper.onStop();
	}
	
	public static void sendRankingScore(int score){
		Log.d(TAG, "sendRankingScore:" + score);
		if(mHelper.isSignedIn()){
			Games.Leaderboards.submitScore(mHelper.getApiClient(),
					mActivity.getString(R.string.main_ranking), score);
		}else{
			Log.w(TAG, "You have to login.");
		}
	}
	
	public static void showRanking(){
		Log.d(TAG, "showRanking");
		if(mHelper.isSignedIn()){
			mActivity.startActivityForResult(
					Games.Leaderboards.getAllLeaderboardsIntent(mHelper.getApiClient()),
					REQUEST_CODE);
		}else{
			Log.w(TAG, "You have to login.");
			mHelper.onStart(mActivity);
		}
	}
}
