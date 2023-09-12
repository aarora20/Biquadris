#include <iostream>
#include <memory>
#include <string>

#include "board.h"
#include "game.h"
#include "player.h"
#include "textobserver.h"

using namespace std;

int main(int argc, char* argv[]) {
  int seed = 123;
  int level = 0;
  bool text = false;
  string script1 = "sequence1.txt";
  string script2 = "sequence2.txt";
  string arg;
  for (int i = 0; i < argc; i++) {
    arg = argv[i];
    if (arg == "-text")
      text = true;
    else if (arg == "-seed")
      seed = stoi(argv[i + 1]);
    else if (arg == "-scriptfile1")
      script1 = argv[i + 1];
    else if (arg == "-scriptfile2")
      script2 = argv[i + 1];
    else if (arg == "-startlevel")
      level = stoi(argv[i + 1]);
  }
  if (text)
    cout << "true";
  else
    cout << "false";
  cout << " " << seed << " "
       << " " << script1 << " " << script2 << " " << level << endl;
  string startEnd;
  do {
    auto game = std::make_unique<Game>(seed, level, text, script1, script2);
    startEnd = game->start();
  } while (startEnd == "restart");
  return 0;
}
