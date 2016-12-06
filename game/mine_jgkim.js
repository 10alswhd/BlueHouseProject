var test = 0;

// note : JS file 로드시 초기에 한번 호출 됩니다. 본인의 이름 혹은 닉네임 리턴 해주시면 됩니다.
var GetName = function () {
    return "jgkim";
}

var LOG = false;
function Log(params) {
  if (LOG) {
    Console.Info(params);
  }
}

// 정보
var globalInfo = {
  myNumber : 0,
  col : 0,
  row : 0
};

// const
var Dir = {
  UP : "0",
  RIGHT : "1",
  DOWN : "2",
  LEFT : "3"
}

var historyOfDirection = [];

// 수집한 마인 표기
var mazeGoldTaken = [];
function setGoldTaken(row, col) {
  mazeGoldTaken[globalInfo.row * row + col] = true;
}
function isGoldTaken(row, col) {
  return mazeGoldTaken[globalInfo.row * row + col] === true;
}

// note : myNumber : 내 번호 (0 ~ 3 값)
// note : totalPlayerCount : 플레이어 수
// note : col : Map 너비
// note : row : Map 높이
// note : 본 함수는 시작과 함께 1회만 호출 됩니다.
var Initialize = function (myNumber, totalPlayerCount, col, row) {
    Log(myNumber);
    Log(totalPlayerCount);
    Log(col);
    Log(row);

    globalInfo.myNumber = myNumber;
    globalInfo.col = col;
    globalInfo.row = row;
    //Log(globalInfo.myNumber);

    mazeGoldTaken = [];
}

function getRandomInt(min, max) {
  var random1 = Math.floor(Math.random() * (max - min)) + min;
  //Log("random : " + random1.toString());
  return random1;
  //return Math.floor(Math.random() * (max - min)) + min;
}

// note : 게임 중 내내 호출 될 function 입니다.
// note : playerPosition[playerNumber] 하시면 해당 플레이어의 위치값을 알 수 있습니다.
// note : playerPower[playerNumber] 하시면 해당 플레이어의 곡갱이+ 값을 알 수 있습니다.
// note : playerStun[playerNumber] 하시면 해당 플레이어의 남은 스턴 턴 수를 알 수 있습니다.
// note : mapBlocks는 전체 맵을 나타내는 선형 int array입니다. mapBlocks가 가질 수 있는 값은 아래와 같습니다.
// note : ITEM_9 : 곡갱이 아이템 LV1, 본인의 Power를 +3만큼 증가시킨다. (Power 1당 1턴에 돌 블럭을 1만큼 제거한다.)
// note : ITEM_8 : 곡갱이 아이템 LV1, 본인의 Power를 +2만큼 증가시킨다.
// note : ITEM_7 : 곡갱이 아이템 LV1, 본인의 Power를 +1만큼 증가시킨다.
// note : ITEM_6 : 시간 정지 아이템 LV3, 본인을 제외한 플레이어들을 많은 턴수만큼 행동 불능으로 만든다. sqrt(col^2 + row^2)
// note : ITEM_5 : 시간 정지 아이템 LV2, 본인을 제외한 플레이어들을 중간 턴수만큼 행동 불능으로 만든다. sqrt(col^2 + row^2) * (2/3)
// note : ITEM_4 : 시간 정지 아이템 LV1, 본인을 제외한 플레이어들을 적은 턴수만큼 행동 불능으로 만든다. sqrt(col^2 + row^2) * (1/3)
// note : ITEM_3 : 산사태 아이템 LV3, 본인을 제외한 플레이어들의 주변 5칸을 무작위 돌블럭으로 메운다.
// note : ITEM_2 : 산사태 아이템 LV2, 본인을 제외한 플레이어들의 주변 3칸을 무작위 돌블럭으로 메운다.
// note : ITEM_1 : 산사태 아이템 LV1, 본인을 제외한 플레이어들의 주변 2칸을 무작위 돌블럭으로 메운다.
// note : GEM_5 : 다이아몬드 블럭 - 5 point
// note : GEM_3 : 금 블럭 - 3 point
// note : GEM_2 : 은 블럭 - 2 point 
// note : GEM_1 : 동 블럭 - 1 point
// note : NONE : 아무것도 없는 블럭
// note : ROCK_1 : 내구도 1인 돌 블럭
// note : ROCK_2 : 내구도 2인 돌 블럭
// note : ROCK_3 : 내구도 3인 돌 블럭
// note : ROCK_4 : 내구도 4인 돌 블럭
// note : ROCK_5 : 내구도 5인 돌 블럭
// note : ROCK_6 : 내구도 6인 돌 블럭
var Process = function (playerPosition, playerPower, playerStun, mapBlocks) {
    // note : Breakpoint 잡고 실시간 디버깅이 가능하도록 환경을 제공 하고 싶었으나,
    //      JS Engin 디버깅 환경 설정이 좀 번거롭네요. 아래 코드로 Log/Mines.log 파일에 로그를 남길 수 있습니다.

    Log("*************************************");
    Log("Process");
    Log(playerPosition);
    Log(playerPower);
    Log(playerStun);
    //printMapBlock(mapBlocks);
	//Log(mapBlocks);
   // Log(mapBlocks[0]);
	//Log(mapBlocks[1]);
	//Log(mapBlocks[2]);
	//Log(mapBlocks[3]);

    return getDirection(playerPosition, playerPower, mapBlocks);
}
// note : 본인이 이동 하고 싶은 방향값을 반환 시켜 줍니다.
// note : 0 = 상, 1 = 우, 2 = 하, 3 = 좌
// note : 이동하려는 위치에 돌 블럭이 있을 경우, 본인이 가진 Power만큼 돌 블럭 가중치를 제거 합니다.
// note : Power가 3일때 6돌 블럭을 캘 경우, 6 - 3이 되어 3돌이 됩니다. 0값의 블럭으로만 이동이 가능 합니다.
// note : 맵의 가장자리로 이동 시, 제자리 걸음을 하게 되며 턴이 소모 됩니다.

var BOT_OBJECT = {
  curPos : 0,
  direction : 0, // 0 = 상, 1 = 우, 2 = 하, 3 = 좌
  found : false, // 뭔가 찾았니
  paths : [],  // 지나온 길 [상하좌우]
  prevPos : undefined
};

var mazeBots = []; // BOT_OBJECT type, row,col
var mazeBotPassed = []; // boolean type, row,col
var botsList = []; // bot 만들어진 순서대로 들어간 List
var goldPositionList = []; // 골드위치, 발견된 순서대로 들어간 list
var goldValueList = []; // goldPositionList 에서 발견한 골드의 값어치
var mazeFoundBots = [];    // 발견한 bot 객체의 레퍼런스, 봇은 이동중일수 있으니.
var mazeBlockAttackingBot = []; // 블록에 공격중인게 있다면, 넌 이미 늦은거야. 중복으로 블록 깨지 않게 하기 위해
var turnCountOnSimulator = 0;

function isMazeBotPassed(position) {
  return mazeBotPassed[position] !== undefined;
}

// goldValueList 으로 부터 최고의 인덱스를 찾음
// 여러개 찾았을때, 점수 많은 쪽으로 가기
function getBestGoldIndex(mapBlocks) {
  var index = 0;
  var min = 0;
  var shortPath = 0;
  var nPaths = 0;
  var bot = {};
  for (var i = 0; i < goldValueList.length; ++i) {

    // 매우 근접하다면. 1순위
    //bot = mazeFoundBots[goldPositionList[i]];
    //nPaths = bot.paths ? bot.paths.length : 10;
    //var PR_1_path = 1;
    //if (nPaths <= PR_1_path) {
    //  return i;
    //}

    // 금값이 높은 것에 우선순위
    if (goldValueList[i] < min) {
      index = i;
      min = goldValueList[i];
      bot = mazeFoundBots[goldPositionList[index]];
      shortPath = bot.paths ? bot.paths.length : 0;
    } else if (goldValueList[i] === min) {
      // 금 값 같으면, 거리 짧은 애를
      bot = mazeFoundBots[goldPositionList[index]];
      nPaths = bot.paths ? bot.paths.length : 0;
      if (nPaths < shortPath) {
        shortPath = nPaths;
        index = i;
      }
    }
  }
  Log("getBestGoldIndex : " + index + " , value : " + goldValueList[index]);
  return index;

}
function getDirection(playerPosition, playerPower, mapBlock) {
  var myPosition = playerPosition[globalInfo.myNumber];
  var myPower = playerPower[globalInfo.myNumber];

  Log("getDirection");

  // init simulate data
  mazeBots = [];
  mazeBotPassed = [];
  botsList = [];
  goldPositionList = []; // array
  goldValueList = []; // array
  mazeFoundBots = [];
  mazeBlockAttackingBot = [];
  turnCountOnSimulator = 0;
  //

  //Log("bots : " + botsList.toString());
  //Log("mazeBots : " + mazeBots[myPosition].toString());
  //Log(mazeBots[myPosition][Dir.UP].toString());
  //Log(mazeBots[myPosition][Dir.RIGHT].toString());
  //Log(mazeBots[myPosition][Dir.DOWN].toString());
  //Log(mazeBots[myPosition][Dir.LEFT].toString());
  //Log(myPosition.toString());
  //Log(mazeBotPassed.toString());
  //Log("----");

  //골드 방향으로 이동했으므로, 이미 처리한 목록에 추가, 불필요.(중복해서 먹을수 있는지 알았음)
  //if (isGem(myPosition, mapBlock)) {
  //  mazeGoldTaken[myPosition] = true;
  //}

  // 기존에 찾은 골드는 무시하게 함,  NONE 으로 처리
  //for (var i = 0; i <  mazeGoldTaken.length; ++i) {
  //  if (mazeGoldTaken[i] === true) {
  //    mapBlock[i] = 0;
  //  }
  //}

  //Log(mapBlock);


  // 현재 위치에서 사방으로 로봇 만들기 시도. 없다면 만들기
  makeBots(myPosition, undefined, false, false);
  //mazeBotPassed[myPosition] = true;
  //isFirst = false;

  // log
  Log(String("turns : " + turnCountOnSimulator));
  printMapBlock(mapBlock);
  printMazeBots();
  printMazeBotPassed();
  Log("botsList.length : " + String(botsList.length));

  // 시뮬레이션 : 로봇을 한 턴씩 이동시켜 뭐든 찾기
  turnCountOnSimulator++;
  var movingCount = runBots(myPower, mapBlock);;

  // log
  Log(String("turns : " + turnCountOnSimulator));
  printMapBlock(mapBlock);
  printMazeBots();
  printMazeBotPassed();
  Log("botsList.length : " + String(botsList.length));

  // 몇번 돌려본다
  //var maxTurn = 20;
  //while (maxTurn--) {
  //  turnCountOnSimulator++;
  //  movingCount = runBots(myPower, mapBlock);
  //}

  var minimumFound = 10;
  while (goldPositionList.length < minimumFound &&
    movingCount > 0)
  {
    turnCountOnSimulator++;
    movingCount = runBots(myPower, mapBlock);

    // log
    Log(String("turns : " + turnCountOnSimulator));
    printMapBlock(mapBlock);
    printMazeBots();
    printMazeBotPassed();
    Log("botsList.length : " + String(botsList.length));

    // 골드/아이템 하나라도 찾으면  봇 탐색 중지
    //if (goldPositionList.length > 0) {
    //  break;
    //}
  }

  //Log(String("turns(after) : " + turnCountOnSimulator));
  //printMazeBots();
  //printMazeBotPassed();
  //Log("botsList.length : " + String(botsList.length));


  var direction = 0;

  if (goldPositionList.length > 0) {
    // 점수 높은 bot 방향으로 가게
    printGoldPositionList(mapBlock);
    var bestIndex = getBestGoldIndex(mapBlock);
    Log("bestIndex : " + bestIndex);

    printBot(mazeFoundBots[goldPositionList[bestIndex]]);
    var foundBot = mazeFoundBots[goldPositionList[bestIndex]];

    //var parentArray = getPrevPosList(foundBot);

    var startPos = foundBot.paths[0];
    var nextPos = foundBot.paths.length > 1 ? foundBot.paths[1] : foundBot.curPos;
    var rowColStart = getRowCol(startPos);
    var rowColNext = getRowCol(nextPos);
    if (rowColStart.row === rowColNext.row) {
      if (rowColStart.col < rowColNext.col) {
        direction = 1; // right
      } else {
        direction = 3; // left
      }
    } else {
      if (rowColStart.row < rowColNext.row) {
        direction = 2; // down
      } else {
        direction = 0; // up
      }
    }
  } else {
    Log("****************");
    Log("****************");
    Log("****************");
    Log(" ERROR : gold not found ... ");
    Log("****************");
    Log("****************");
    Log("****************");
    direction = getRandomInt(0,4);
  }

  // 앞뒤/좌우 로 무한 반복하는 현상 임시해결
  // 몇번 반복했다면, 강제로 방향을 바꿈
  //*/
  if (historyOfDirection.length > 10) {
    if (myPosition === historyOfDirection[historyOfDirection.length - 2]
      && myPosition === historyOfDirection[historyOfDirection.length - 4]
      && myPosition === historyOfDirection[historyOfDirection.length - 6]
    ) {
      direction += getRandomInt(1,4); // 현재 가려고 했던 방향을 제외 한 나머지 랜덤
      direction %= 4;
    }
  }
  historyOfDirection.push(myPosition);
  //*/

  return direction;
}

//
function getRowCol(pos) {
  return {
    row: parseInt(pos / globalInfo.col),
    col: pos % globalInfo.col
  };
}
function getPositionFromRowCol(rowCol) {
  return parseInt(rowCol.row * globalInfo.col + rowCol.col);
}

function isItem(pos, mapBlock) {
  if (mapBlock[pos] >= -1009
    && mapBlock[pos] <= -1001) {
    return true;
  }
  return false;
}
function isGem(pos, mapBlock) {
  if (mapBlock[pos] >= -5
    && mapBlock[pos] <= -1) {
    return true;
  }
  return false;
}
function isBlock(pos, mapBlock) {
  if (mapBlock[pos] > 0
    && mapBlock[pos] <= 6) {
    return true;
  }
  return false;
}

//
function moveBot(bot, newPos) {
  var curPos = bot.curPos;
  bot.paths.push(curPos);
  if (!mazeBots[newPos]) {
    mazeBots[newPos] = [];
  }
  mazeBots[newPos][bot.direction] = bot;
  bot.curPos = newPos;
}

/**
 * botsList 에서 모든 bot 들을 실행시킴
 * @param myPower
 * @param mapBlock
 * @returns {number}
 *      - 1 : 어딘가로 이동을 했다면,
 *      - 0 : 가려고 하는 곳이 막혔거나 이미 다른 bot이 지나간 길이어서 못 갔다면
 */
function runBots(myPower, mapBlock) {

  var movedCount = 0;

  //var BOT_SAMPLE = {
  //  curPos : 0,
  //  direction : 0, // 0 = 상, 1 = 우, 2 = 하, 3 = 좌
  //  found : false, // 뭔가 찾았니
  //  paths : [],  // 지나온 길 [상하좌우]
  //  prevPos : undefined
  //};

  // mazeBots 안의 모든 bot 들을 하나씩 이동시킴
  Log("runBots -------");

  for (var i in botsList) {
    var bot = botsList[i];

    if (bot.dead === true) {
      continue;
    }

    var curPos = bot.curPos;
    var rowCol = getRowCol(curPos);

    switch (bot.direction) {
      case Dir.UP:
        rowCol.row--;
        break;
      case Dir.RIGHT:
        rowCol.col++;
        break;
      case Dir.DOWN:
        rowCol.row++;
        break;
      case Dir.LEFT:
        rowCol.col--;
    }

    // if outOfMaze(newPos)
    if (rowCol.row < 0 || rowCol.row >= globalInfo.row
      || rowCol.col < 0 || rowCol.col >= globalInfo.col) {
      bot.dead = true;
      continue;
    }

    bot.turnsCount++;

    var foundGoldOrItem = false;

    var newPos = getPositionFromRowCol(rowCol);

    // 1. 블록이면 카운트 낮춤
    // 2. 골드이면 goldtaken 하고, passed marking 하고 found = true,
    // 3. 아이템이면 found = true
    // 4. 빈공간(NONE) 이면, passed marking 새로운 위치에 makeBots 수행
    if (isBlock(newPos, mapBlock)) {

      // 다른 봇이 이미 공격중이면,
      if (mazeBlockAttackingBot[newPos]
        && mazeBlockAttackingBot[newPos].curPos !== bot.curPos) {
        bot.dead = true; // bot 사망한것으로
        continue;
      }
      mazeBlockAttackingBot[newPos] = bot; // 이 봇이 공격중이닷~

      mapBlock[newPos] -= myPower;
      if (mapBlock[newPos] <= 0) {
        mapBlock[newPos] = 0;
        //mazeBlockAttackingBot[newPos] = undefined; // 누가 어택완료 하자마자 딴놈이 들어올수 있으므로, 계속 어택 중인걸로 놔둠
      }
      //Log("block found " + newPos + " = " + mapBlock[newPos]);
      movedCount++; // 뭔가를 했는지 체크용
    } else if (isGem(newPos, mapBlock)) {
      goldValueList.push(mapBlock[newPos]);
      mapBlock[newPos] = 0;

      foundGoldOrItem = true;

      bot.found = true;
      // 이동
      moveBot(bot, newPos);

      makeBots(newPos, bot, true, false);
      movedCount++;
    } else if (isItem(newPos, mapBlock)) {

      // 파워 아이템이라면, 내가 6이하일때만 가지러 가게 함
      if (mapBlock[newPos] <= -1007
        //&& myPower >= 6
       ) {
        // 파워아이템은 그냥 무시...
        mapBlock[newPos] = 0;
      } else
      {
        goldValueList.push(mapBlock[newPos]);
        mapBlock[newPos] = 0;

        foundGoldOrItem = true;

        bot.found = true;
      }

      moveBot(bot, newPos);

      makeBots(newPos, bot, false, true);
      movedCount++;
    } else {
      // 다른 봇이 공격해 놓은걸, 니가 깬개 아니면 그냥 통과하면 안되지.
      if (mazeBlockAttackingBot[newPos]
        && mazeBlockAttackingBot[newPos].curPos !== bot.curPos) {
        bot.dead = true; // bot 사망한것으로
        continue;
      }

      //printBot(bot);
      moveBot(bot, newPos);
      //mapBlock[newPos] = 0;
      makeBots(newPos, bot, false, false);
      movedCount++;
    }

    if (foundGoldOrItem) {
      goldPositionList.push(newPos);
      mazeFoundBots[newPos] = bot;
    }
  }

  return movedCount;
}

///
function makeBots(curPosition, botFrom, foundGold, foundItem) {
  if (isMazeBotPassed(curPosition))
    return;

  if (mazeBots[curPosition] === undefined) {
    mazeBots[curPosition] = [];
  }

  Log("makeBots");
  var rowCol = getRowCol(curPosition);
  Log(String('[' + rowCol.row + '][' + rowCol.col + ']'));

  makeUpBot(curPosition, botFrom);
  makeRightBot(curPosition, botFrom);
  makeDownBot(curPosition, botFrom);
  makeLeftBot(curPosition, botFrom);

  Log(mazeBots[curPosition][Dir.UP] && mazeBots[curPosition][Dir.UP].direction);
  Log(mazeBots[curPosition][Dir.RIGHT] && mazeBots[curPosition][Dir.RIGHT].direction);
  Log(mazeBots[curPosition][Dir.DOWN] && mazeBots[curPosition][Dir.DOWN].direction);
  Log(mazeBots[curPosition][Dir.LEFT] && mazeBots[curPosition][Dir.LEFT].direction);

  // passed 체크 위치 중요.
  mazeBotPassed[curPosition] = botFrom ? botFrom.direction : 'x';
}


function makeUpBot(curPosition, botFrom) {
  var pos = getRowCol(curPosition);
  var newPos = {
    row: pos.row - 1,
    col: pos.col
  };

  if (newPos.row < 0) {
    return;
  }
  // 위로 지나간 애가 없어야..
  if (isMazeBotPassed(getPositionFromRowCol(newPos))) {
    return;
  }

  if (mazeBots[curPosition][Dir.UP] === undefined) {
    var newBot = {
      curPos : curPosition,
      direction : Dir.UP, // 0 = 상, 1 = 우, 2 = 하, 3 = 좌
      found : false, // 뭔가 찾았니
      paths : botFrom ? botFrom.paths.slice(0) : [],  // 지나온 길 [상하좌우]
      prevPos : botFrom ? botFrom.curPos : undefined,
      turnsCount : turnCountOnSimulator //
    };
    mazeBots[curPosition][Dir.UP] = newBot;
    botsList.push(newBot);
  }
}

function makeRightBot(curPosition, botFrom) {
  var pos = getRowCol(curPosition);
  var newPos = {
    row: pos.row,
    col: pos.col + 1
  };

  if (newPos.col >= globalInfo.col) {
    return;
  }
  // 위로 가는 애가 없어야..
  if (isMazeBotPassed(getPositionFromRowCol(newPos))) {
    return;
  }

  if (mazeBots[curPosition][Dir.RIGHT] === undefined) {
    var newBot = {
      curPos : curPosition,
      direction : Dir.RIGHT, // 0 = 상, 1 = 우, 2 = 하, 3 = 좌
      found : false, // 뭔가 찾았니
      paths : botFrom ? botFrom.paths.slice(0) : [],  // 지나온 길 [상하좌우]
      prevPos : botFrom ? botFrom.curPos : undefined,
      turnsCount : turnCountOnSimulator //
    }
    mazeBots[curPosition][Dir.RIGHT] = newBot;
    botsList.push(newBot);
  }
}

function makeDownBot(curPosition, botFrom) {
  var pos = getRowCol(curPosition);
  var newPos = {
    row: pos.row + 1,
    col: pos.col
  };

  if (newPos.row >= globalInfo.row) {
    return;
  }
  // 위로 가는 애가 없어야..
  if (isMazeBotPassed(getPositionFromRowCol(newPos))) {
    return;
  }

  if (mazeBots[curPosition][Dir.DOWN] === undefined) {
    var newBot = {
      curPos : curPosition,
      direction : Dir.DOWN, // 0 = 상, 1 = 우, 2 = 하, 3 = 좌
      found : false, // 뭔가 찾았니
      paths : botFrom ? botFrom.paths.slice(0) : [],  // 지나온 길 [상하좌우]
      prevPos : botFrom ? botFrom.curPos : undefined,
      turnsCount : turnCountOnSimulator //
    };
    mazeBots[curPosition][Dir.DOWN] = newBot;
    botsList.push(newBot);
  }
}

function makeLeftBot(curPosition, botFrom) {
  var pos = getRowCol(curPosition);
  var newPos = {
    row: pos.row,
    col: pos.col - 1
  };

  if (newPos.col < 0) {
    return;
  }
  // 위로 가는 애가 없어야..
  if (isMazeBotPassed(getPositionFromRowCol(newPos))) {
    return;
  }

  if (mazeBots[curPosition][Dir.LEFT] === undefined) {
    var newBot = {
      curPos : curPosition,
      direction : Dir.LEFT, // 0 = 상, 1 = 우, 2 = 하, 3 = 좌
      found : false, // 뭔가 찾았니
      paths : botFrom ? botFrom.paths.slice(0) : [],  // 지나온 길 [상하좌우]
      prevPos : botFrom ? botFrom.curPos : undefined,
      turnsCount : turnCountOnSimulator //
    };
    mazeBots[curPosition][Dir.LEFT] = newBot;
    botsList.push(newBot);
  }
}

// util
function printMazeBots() {
  var i = 0,
    j = 0,
    pos = 0;

  var output = []; // string array

  for (i = 0; i < globalInfo.row; ++i) {
    for (j = 0; j < globalInfo.col; ++j) {
      pos = i * globalInfo.col + j;
      if (j == 0) {
        output[i] = String(i % 10) + "||";
      }
      if (mazeBots[pos] === undefined) {
        output[i] = output[i] + "  |";
      } else {
        var maskUpDown = ' ',
          maskLeftRight = ' ';

        if (mazeBots[pos][Dir.UP] && mazeBots[pos][Dir.DOWN]) {
          maskUpDown = '!';
        } else if (mazeBots[pos][Dir.UP]) {
          maskUpDown = '^';
        } else if (mazeBots[pos][Dir.DOWN]) {
          maskUpDown = 'v';
        }

        if (mazeBots[pos][Dir.RIGHT] && mazeBots[pos][Dir.LEFT]) {
          maskLeftRight = '-';
        } else if (mazeBots[pos][Dir.RIGHT]) {
          maskLeftRight = '>';
        } else if (mazeBots[pos][Dir.LEFT]) {
          maskLeftRight = '<';
        }

        output[i] = output[i] + maskUpDown + maskLeftRight + "|";
      }
    }
  }

  Log("mazeBots ");
  Log("    0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 ")
  Log("---------------------------------------------------------------------");
  for (i = 0; i < output.length; ++i) {
    Log(output[i]);
  }
  Log("---------------------------------------------------------------------");
}

// 어느 방향에서 온 bot 이 통과했는지
function printMazeBotPassed() {
  var i = 0,
    j = 0,
    pos = 0;

  var output = []; // string array

  for (i = 0; i < globalInfo.row; ++i) {
    for (j = 0; j < globalInfo.col; ++j) {
      pos = i * globalInfo.col + j;
      if (j == 0) {
        output[i] = String(i % 10) + "||";
      }
      if (!isMazeBotPassed(pos)) {
        output[i] = output[i] + "  |";
      } else {
        var maskBotFrom = ' ';

        if (mazeBotPassed[pos] === Dir.UP) {
          maskBotFrom = '^';
        } else if (mazeBotPassed[pos] === Dir.DOWN) {
          maskBotFrom = 'v';
        }

        if (mazeBotPassed[pos] === Dir.RIGHT) {
          maskBotFrom = '>';
        }
        else if (mazeBotPassed[pos] === Dir.LEFT) {
          maskBotFrom = '<';
        }

        if (mazeBotPassed[pos] === 'x') {
          maskBotFrom = 'x';
        }

        output[i] = output[i] + maskBotFrom + " |";
      }
    }
  }

  Log("printMazeBotPassed ");
  Log("    0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 ")
  Log("---------------------------------------------------------------------");
  for (i = 0; i < output.length; ++i) {
    Log(output[i]);
  }
  Log("---------------------------------------------------------------------");

}

function printMapBlock(mapBlocks) {
  var i = 0,
    j = 0,
    pos = 0;

  var output = []; // string array

  for (i = 0; i < globalInfo.row; ++i) {
    for (j = 0; j < globalInfo.col; ++j) {
      pos = i * globalInfo.col + j;
      if (j == 0) {
        output[i] = String(i % 10) + "||";
      }
      if (mapBlocks[pos] === 0) {
        output[i] = output[i] + "  |";
      } else {
        if (isBlock(pos, mapBlocks)) {
          output[i] = output[i] + "B" + String(mapBlocks[pos]) + "|";
        } else if (isGem(pos, mapBlocks)) {
          output[i] = output[i] + "G" + String(Math.abs(mapBlocks[pos])) + "|";
        } else if (isItem(pos, mapBlocks)) {
          var type = mapBlocks[pos];
          if (type <= -1001 && type >= -1003) {
            output[i] = output[i] + "M |"; // 산사태
          } else if (type <= -1004 && type >= -1006) {
            output[i] = output[i] + "T |"; // 시간정지
          } else {
            output[i] = output[i] + "P |"; // 파워
          }
        }
      }
    }
  }

  Log("printMapBlock ");
  //----0--1--2--3--4--5--6--7--8--9-10-11-12-13-14-15-16-17-18-19--
  //0||  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
  //1||  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |

  Log("    0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 ")
  Log("---------------------------------------------------------------------");
  for (i = 0; i < output.length; ++i) {
    Log(output[i]);
  }
  Log("---------------------------------------------------------------------");
}

function printBot(bot) {
  Log(String("bot.curPos : " + bot.curPos));
  var rowCol = getRowCol(bot.curPos);
  Log(String("    [" + rowCol.row + "][" + rowCol.col + "]"));
  Log(String(" dir : " + bot.direction));
  if (bot.paths) {
    var p = " paths : ";

    var posToRowColString = function (pos) {
      var rowCol = getRowCol(pos);
      return "[" + rowCol.row + "][" + rowCol.col + "]";
    }
    for (var i = 0; i < bot.paths.length; ++i) {
      p += String(bot.paths[i] + '(' + posToRowColString(bot.paths[i]) + ') > ');
    }
    Log(p);
  }
}

function printGoldPositionList(mapBlock) {
  Log("goldPositionList.length : " + goldPositionList.length);
  var pos = 0;
  for (var i = 0; i < goldPositionList.length; ++i) {
    pos = goldPositionList[i];
    var rowCol = getRowCol(pos);
    Log("[" + i + "] : [" + rowCol.row + "][" + rowCol.col + "]  pos:" + pos
      + " ,Gold " + goldValueList[i]);
  }
}

function getPrevPosList(bot, list) {
//  if (bot) {
//    list.push(bot.prevPos);
//    getPrevPosList()
//  }
}
