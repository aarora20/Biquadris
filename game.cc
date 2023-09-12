#include "game.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "block.h"
#include "cell.h"
#include "player.h"
#include "textobserver.h"

using namespace std;

int square(int number) { return number * number; }

vector<int> Game::isRowFull(Board* board, Player* player) {
  vector<int> fullRows;
  for (int row = 3; row < BLOCK_ROW_END; ++row) {
    bool full = true;
    string rowData = board->getRow(row);
    if (string::npos != rowData.find(".")) full = false;
    if (full) {
      fullRows.push_back(row);
      // cout << "Row " << row << " is full" << endl;
    }  // else
       // cout << "Row " << row << " is not full" << endl;
  }
  // cout << "Full rows: " << fullRows.size() << endl;
  return fullRows;
}

void Game::clearRow(Board* board, vector<int> rows) {
  for (std::vector<int>::iterator it = rows.begin(); it != rows.end(); ++it) {
    for (int col = 0; col < BLOCK_COLUMN_SIZE; ++col) {
      board->clearPos(col, *it);
    }
  }
}

void Game::calculateScore(Board* board, Player* player, int playerNum,
                          vector<int> rows) {
  unsigned long int length = rows.size();
  if (length > 0) {
    board->setTurnsSinceClear(0);
    notifyObservers();
    clearCurBlock(board, 0, 0);
    int level = player->getLevel();
    int score = player->getScore();
    score += square(length + level);
    for (std::vector<int>::iterator it = rows.begin(); it != rows.end(); ++it) {
      for (int col = 0; col < BLOCK_COLUMN_SIZE; ++col) {
        int remainingBlocks = board->getBoard()[*it][col]->getRemainingBlocks();
        // cout << "Remaining blocks before clear: " << remainingBlocks << endl;
        if (remainingBlocks == 1) {
          score += square(remainingBlocks + 1);
        }
        board->getBoard()[*it][col]->setRemainingBlocks(remainingBlocks - 1);
        // cout << "Remaining blocks before clear: " <<
        // board->getBoard()[*it][col]->getRemainingBlocks() << endl;
      }
      cout << "Player " << playerNum << " cleared row: " << *it << "!" << endl
           << endl;
      board->getBoard().erase(board->getBoard().begin() + *it);
      vector<shared_ptr<Cell>> newRow{
          vector<shared_ptr<Cell>>(BLOCK_COLUMN_SIZE)};
      auto blankCell = make_shared<Cell>(".", 0);
      for (int col = 0; col < 11; col++) {
        newRow[col] = blankCell;
      }
      board->getBoard().insert(board->getBoard().begin() + 3, newRow);
      player->setScore(score);
    }
    board->placeCurBlock();
    if (length > 1) {
      cout << playerNum << " triggered a special action!" << endl;
      cout << "Please enter your desired special action: ";
      string action;
      while (cin >> action) {
        Board* otherBoard;
        playerNum == 1 ? otherBoard = board2.get() : otherBoard = board1.get();
        if (action == "blind") {
          otherBoard->setBlind(true);
          break;
        } else if (action == "heavy") {
          otherBoard->setHeavy(true);
          break;
        } else if (action == "force") {
          string block;
          otherBoard->setForce(true);
          cout << "Choose the block you wish to force the other player to use"
               << endl;
          cin >> block;
          handleReplaceBlockCommand(block, otherBoard);
          break;
        } else
          cout << "Invalid Command, choose between blind, heavy or force"
               << endl;
      }
    }
    // cout << "Points obtained: " << score << endl;
  }
}

void handleInvalidCommands(string cmd) {
  if (cmd == "norandom" || cmd == "random") {
    string garbage;
    if (cmd == "norandom") cin >> garbage;
    cout << cmd << " not applicable for current level" << endl;
  }
}

int parsePrefix(string& cmd) {
  int commandCount = 1;
  string count = "";
  while (isdigit(cmd[0])) {
    count += cmd[0];
    cmd.erase(0, 1);
  }
  if (count != "") {
    commandCount = stoi(count);
  }
  return commandCount;
}

string parseInput(string input) {
  const int COMMAND_COUNT = 19;
  vector<string> commands{
      "left",     "right",   "down",      "clockwise", "counterclockwise",
      "drop",     "levelup", "leveldown", "norandom",  "random",
      "sequence", "restart", "I",         "J",         "L",
      "O",        "S",       "T",         "Z"};
  string command = "";
  for (int i = 0; i < COMMAND_COUNT; ++i) {
    if (commands[i][0] == input[0] && commands[i][1] == input[1] &&
        commands[i].find(input) != std::string::npos) {
      command += commands[i];
      // cout << commands[i].find(input) << endl;
    }
  }
  // cout << "Command: " << command << endl;
  return command;
}

Game::Game(int seed, int startLevel, bool text, string file1, string file2)
    : seed{seed},
      startLevel{startLevel},
      text{text},
      restartCommandTriggered{false},
      file1{file1},
      file2{file2} {
  board1 = make_unique<Board>(startLevel, seed, file1);
  board2 = make_unique<Board>(startLevel, seed, file2);
  player1 = make_unique<Player>(startLevel, 0, board1.get());
  player2 = make_unique<Player>(startLevel, 0, board2.get());
}

Player* Game::getPlayer(int i) {
  return (i == 1) ? player1.get() : player2.get();
}

string Game::start() {
  auto textDisplay = make_unique<TextObserver>(this);
  board1->setNextBlock();  // Generates the initial next block and places it on
                           // the nextData vector
  clearNextBlock(
      board1.get());  // Removes the initial nextBlock from the nextData vector
  board1->setCurBlock();   // curBlock 'steals' the generated nextBlock and
                           // places it on the data vector
  board1->setNextBlock();  // Generates the new nextBlock and places it on the
                           // nextData vector

  board2
      ->setNextBlock();  // Same process as above executed for player 2's board
  clearNextBlock(board2.get());
  board2->setCurBlock();
  board2->setNextBlock();

  notifyObservers();      // Prints both boards
  return executeTurns();  // Begins executing turns
}

string Game::executeTurns() {
  while (true) {
    bool continueGame = player1Turn();
    if (!continueGame) return "finished";
    if (restartCommandTriggered) return "restart";
    continueGame = player2Turn();
    if (!continueGame) return "finished";
    if (restartCommandTriggered) return "restart";
  }
}

bool Game::player1Turn() {
  bool continueGame = executePlayerCommand(board1.get(), player1.get(), 1);
  if (!restartCommandTriggered && continueGame) notifyObservers();
  return continueGame;
}


bool Game::player2Turn() {
  bool continueGame = executePlayerCommand(board2.get(), player2.get(), 2);
  if (!restartCommandTriggered && continueGame) notifyObservers();
  return continueGame;
}

void Game::isHeavyDrop(Board* board) {
  int downCount = 0;
  if (board->getHeavy()) downCount++;
  if (board->getLevelInstance()->getHeavy()) downCount++;
  auto block = board->getCurBlock()->getBlockPosition();
  int xOffset = board->getCurBlock()->getXOffset();
  int yOffset = board->getCurBlock()->getYOffset();
  clearCurBlock(board, xOffset, yOffset);
  for (int i = 0; i < downCount; ++i) {
    //cout << "Shifting block down for the " << i+1 << "th(st) time." << endl;
    if (board->validMove("down")) board->getCurBlock()->down();
  }
  board->placeCurBlock();
}

bool Game::executePlayerCommand(Board* board, Player* player, int playerNum) {
  bool continueGame = true;
  bool turnOver = false;  // Boolean to determine if the player's turn has ended
  cout << "Player " << playerNum << "'s turn" << endl;
  while (!turnOver && continueGame) {  // Loops as long as turnOver is false
    // If a sequence of commands was passed, and we are at the end of that
    // sequence set sequencePassed to false so we no longer take input from that
    // sequence.
    if (sequencePassed && it == sequence.end()) {
      sequencePassed = false;
    }  // NEED TO CLEAR SEQUENCE
    // Take input from sequence file
    else if (sequencePassed) {
      cmd = *it;
      ++it;
    }
    if (!sequencePassed) {  // Take input from cin
      cout << "Please enter your command: ";
      cin >> cmd;
      if (cin.eof()) continueGame = false;
      cout << endl;
    }

    // Determine if an integer prefix X was supplied in a command.
    int commandCount = parsePrefix(cmd);
    // Determine the command passed.
    cmd = parseInput(cmd);

    // Execute commands as followed
    if (cmd == "restart") {
      restartCommandTriggered = true;
      break;
    } else if (cmd == "levelup" || cmd == "leveldown") {
      for (int i = 0; i < commandCount; ++i) {
        handleLevelCommand(cmd, board, player);
      }
    } else if (cmd == "drop") {
      for (int i = 0; i < commandCount; ++i) {
        handleDropCommand(board);
        // Clears the nextBlock from the nextData vector
        clearNextBlock(board);
        // Steals the nextBlock and places on the data
        bool valid = board->setCurBlock();
        if (!valid) {
          cout << "Player " << playerNum << " has lost" << endl;
          continueGame = false;
        }
        // vector
        board->setNextBlock();  // Generates the new nextBlock and places on the
                                // nextData vector
        if (i != commandCount - 1) {
          // We do not print the board after the last drop command because the
          // end of this turn will print the board itself.
          notifyObservers();
        }
        vector<int> rows = isRowFull(board, player);
        calculateScore(board, player, playerNum, rows);
        int turnsSinceClear = board->getTurnsSinceClear();
        cout << "Turns since clear: " << turnsSinceClear << endl;
        board->setTurnsSinceClear(turnsSinceClear+1);
        if ((turnsSinceClear + 1) % 5 == 0 && player->getLevel() == 4) {
          auto cell = make_shared<Cell>("*", 4);
          int row = 3;
          while (row < 18) {
            if (board->getBoard()[row][5]->getType() != ".") break;
            ++row;
          }
          board->getBoard()[row-1][5] = cell;
        } 
      }
      // Since we have performed the last drop command, the player's turn is
      // over.
      board->setBlind(false);
      turnOver = true;
    } else if (cmd == "clockwise" || cmd == "counterclockwise") {
      for (int i = 0; i < commandCount; ++i) {
        handleRotateCommand(cmd, board);
      }
    } else if (cmd == "left" || cmd == "right" || cmd == "down") {
      for (int i = 0; i < commandCount; ++i) {
        handleMoveCommand(cmd, board);
      }
    } else if (cmd == "I" || cmd == "J" || cmd == "L" || cmd == "O" ||
               cmd == "S" || cmd == "T" || cmd == "Z") {
      handleReplaceBlockCommand(cmd, board);
    } else if (cmd == "norandom" && player->getLevel() > 2) {
      cin >> noRandomFile;
      if (player->getLevel() > 2) {
        // sets the noRandomFile param so that level will now generate
        // blocks from the file provided instead of random generation.
        player->getBoard()->getLevelInstance()->setNoRandomFile(noRandomFile);
        notifyObservers();
      }
    } else if (cmd == "random" && player->getLevel() > 2) {
      // sets the noRandomFile param to an empty string so that level
      // will now generate blocks randomly again.
      player->getBoard()->getLevelInstance()->setNoRandomFile("");
      notifyObservers();
    } else if (cmd == "sequence") {
      handleSequenceCommand();
    } else {
      handleInvalidCommands(cmd);
    }
  }
  return continueGame;
}

void Game::handleLevelCommand(const string& cmd, Board* board, Player* player) {
  int currentLevel = player->getLevel();
  if (cmd == "levelup" && currentLevel < MAX_LEVEL) {
    ++currentLevel;
    board->changeLevel(
        currentLevel);  // Changes the instance of level used to generate blocks
    player->updateLevel(currentLevel);  // Changes the integer value of level
                                        // used to print level
    notifyObservers();
  } else if (cmd == "leveldown" && currentLevel > MIN_LEVEL) {
    --currentLevel;
    board->changeLevel(
        currentLevel);  // Changes the instance of level used to generate blocks
    player->updateLevel(currentLevel);  // Changes the integer value of level
                                        // used to print level
    notifyObservers();
  } else {
    cout << "Unable to " << cmd << " past " << currentLevel << endl;
  }
}

void Game::handleDropCommand(Board* board) {
  // Clears the previous placement of the block
  auto block = board->getCurBlock()->getBlockPosition();
  int xOffset = board->getCurBlock()->getXOffset();
  int yOffset = board->getCurBlock()->getYOffset();
  clearCurBlock(board, xOffset, yOffset);

  while (board->validMove("down")) {
    board->getCurBlock()->down();  // Edits the position of the block
  }
  board
      ->placeCurBlock();  // Places the final position of the block on the board
  // Does not print board since the end of the current player's turn will
  // print the board.
}

void Game::handleRotateCommand(const string& cmd, Board* board) {
  // Clears the previous placement of the block
  auto block = board->getCurBlock()->getBlockPosition();
  int xOffset = board->getCurBlock()->getXOffset();
  int yOffset = board->getCurBlock()->getYOffset();
  clearCurBlock(board, xOffset, yOffset);

  if (cmd == "clockwise" && board->validMove("clockwise")) {
    board->getCurBlock()->rotateCw();
  } else if (cmd == "counterclockwise" &&
             board->validMove("counterclockwise")) {
    board->getCurBlock()->rotateCcw();
  }
  // Places the final position of the block on the board
  board->placeCurBlock();  
  isHeavyDrop(board);
  notifyObservers();    // Prints board
}

void Game::handleMoveCommand(const string& cmd, Board* board) {
  // Clears the previous placement of the block
  auto block = board->getCurBlock()->getBlockPosition();
  int xOffset = board->getCurBlock()->getXOffset();
  int yOffset = board->getCurBlock()->getYOffset();
  clearCurBlock(board, xOffset, yOffset);

  if (cmd == "left" && board->validMove("left")) {
    board->getCurBlock()->left();
  } else if (cmd == "right" && board->validMove("right")) {
    board->getCurBlock()->right();
  } else if (cmd == "down" && board->validMove("down")) {
    board->getCurBlock()->down();
  }
  board->placeCurBlock();
  // Places the final position of the block on the board
  isHeavyDrop(board);
  notifyObservers();  // Prints board
}

void Game::handleReplaceBlockCommand(const string& cmd, Board* board) {
  // Clears the previous placement of the block
  auto block = board->getCurBlock()->getBlockPosition();
  int xOffset = board->getCurBlock()->getXOffset();
  int yOffset = board->getCurBlock()->getYOffset();
  clearCurBlock(board, xOffset, yOffset);
  if (cmd == "I" || cmd == "J" || cmd == "L" || cmd == "O" || cmd == "S" ||
      cmd == "T" || cmd == "Z") {
    board->updateCurBlock(cmd);  // Changes the curBlock
  }
  board->placeCurBlock();  // Places the new curBlock on the board
  notifyObservers();       // Prints board
}

void Game::handleSequenceCommand() {
  string filename;
  cin >> filename;        // Obtains sequence filename
  sequencePassed = true;  // Sets sequencePassed to true
  ifstream file(filename);
  string command;
  while (file >> command) {
    // Adds commands in the sequence file to our sequence
    sequence.push_back(command);
  }
  // Sets the sequence to start at beginning
  it = sequence.begin();
}

void Game::clearCurBlock(Board* board, int xOffset, int yOffset) {
  auto block = board->getCurBlock()->getBlockPosition();
  for (const auto& pos : block) {
    board->clearPos(pos[0] + xOffset, pos[1] + yOffset);
  }
}

void Game::clearNextBlock(Board* board) {
  int yOffset = -2;
  auto block = board->getNextBlock()->getBlockPosition();
  for (const auto& pos : block) {
    board->clearNextPos(pos[0], pos[1] + yOffset);
  }
}

Game::~Game() = default;
