/*
Scenario
This task will be a little more free-form than the previous ones.

We want you to design and write a game!

First, think of the type of game you want to design:

maybe a classic pen-and-paper game like Battleships or Tic-tac-toe;
or maybe a word game like Hangman;
or some simple board game like Ludo;
or even a card game like Blackjack
The game does not need to be fancy, but think of the following things when you work:

how can you present the game in a user-friendly way?
which elements of the game can be modelled using classes and objects?
do you see any space for common interfaces that can be shared by more than one class?
That's it. Go on, have fun!
*/

// Choose game: Hangman
#include <iostream>
#include <sstream>

using namespace std;

class StickFigure {
public:
  StickFigure() {}
  ~StickFigure() {}
  void draw_o_bracket();
  void draw_c_bracket();
  void draw_f_slash();
  void draw_b_slash();
  void draw_v_line();
  void draw_hangline();
};

void StickFigure::draw_o_bracket() {
  cout << '(';
}

void StickFigure::draw_c_bracket() {
  cout << " )";
}

void StickFigure::draw_f_slash() {
  cout << '/';
}

void StickFigure::draw_b_slash() {
  cout << " \\";
}

void StickFigure::draw_v_line() {
  cout << '|';
}

void StickFigure::draw_hangline() {
  cout << "------------------------------\n";
  cout << "|/                            |\n";
}

class Player {
private:
  string name;
  
public:
  Player(string n) : name(n) {}
  ~Player() {}
  string getName() { return name; }
};

class Hangman {
private:
  string secret_word;
  StickFigure stickman;
  Player player1;
  Player player2;
  int allowed_guesses;
  int player2_guesses;
  char *guess_word;
public:
  Hangman(string s, string player1, string player2): player1(player1), player2(player2), secret_word(s), allowed_guesses(8), player2_guesses(0) {
    guess_word = new char[secret_word.length()];
  }
  ~Hangman() {}
  Player getPlayer(int i) {
    return i == 1 ? player1 : player2;
  }
  void draw();
  string processPlayerAction(string action, string s);
  void processGuess(string s, int j);
  string getSecretWord() { return secret_word; }
  void getGuessWord() {
    for (int i = 0; i < secret_word.length(); i++) {
      if (guess_word[i] == '\0') cout << '_'; 
      else cout << guess_word[i];
    }
    cout << endl;
  }
};

void Hangman::draw() {
  stickman.draw_hangline();
  for (int i = 0; i < player2_guesses && player2_guesses != allowed_guesses; i++) {
    if (i == 0) {
      cout << "|                            ";
      stickman.draw_o_bracket();
    } else if (i == 1) {
      stickman.draw_c_bracket();
      cout << '\n';
    } else if (i == 2 || i == 6) {
      cout << "|                            ";
      stickman.draw_f_slash();
    } else if (i == 3 || i == 7) {
      stickman.draw_b_slash();
      cout << '\n';
    } else if (i == 4 || i == 5) {
      cout << "|                             ";
      stickman.draw_v_line();
      cout << '\n';
    }
  }
    for (int i = 0; i < 12 - player2_guesses; i++) {
    cout << "|\n";
  }
}

string Hangman::processPlayerAction(string action, string s = "") {
  if (action == "guess") {
    if (s.length() <= this->secret_word.length()) {
      if (secret_word.compare(s) == 0) {
        return "endgame";
      } else {
        if (secret_word.find(s) != string::npos) {
          int j = secret_word.find(s);
          processGuess(s, j);
          getGuessWord();
          if (secret_word.compare(guess_word) == 0) {
            return "endgame";
          }
          if (player2_guesses > 0) --player2_guesses;
          draw();
          return "correct";
        } else
          return "incorrect";
      }
    }
  }
  ++player2_guesses;
  draw();
  if (player2_guesses == allowed_guesses) {
    return "endgame2";
  }
  return "drew";
}

void Hangman::processGuess(string s, int j) {
  if (s.length() == 1) {
    char c = s[0];
    for (int i = j; i < this->secret_word.length(); i++) {
      if (c == secret_word[i]) {
        this->guess_word[i] = c;
      }
    }
  } else if (s.length() > 1) {
    for (int i = 0; i < s.length(); i++) {
      this->guess_word[j+i] = secret_word[j+i];
    }
  }
}

class Interactive {
private:
  Hangman hangman;
public:
  Interactive(string s, string player1, string player2) : hangman(s, player1, player2) {
  }
  ~Interactive() {}
  static void introduceRules();
  void awaitInstruction(string action, string s);
  void showP1Menu();
  void showP2Menu();
};


void Interactive::awaitInstruction(string action, string s = "") {
  while (action.length() > 0) {
    if (action == "quit") {
      if (s == "1") cout << hangman.getPlayer(2).getName() << " won!" << endl;
      else if (s == "2") cout << hangman.getPlayer(1).getName() << " won!" << endl;
      break;
    }

    if (action == "guess") {
      if (s.length() < 1 || s.length() > hangman.getSecretWord().length()) {
        cout << hangman.getPlayer(2).getName() << ", the length of your guess is too long. Punishment incoming...: " << s << "\n";
        action = "draw";
      } else cout << hangman.getPlayer(2).getName() << " guessed: " << s << "\n";
    } else if (action == "draw") {
      cout << hangman.getPlayer(1).getName() << "..." << "\n";
    } else if (action == "skip") {
      cout << hangman.getPlayer(1).getName() << " decided to spare you..." << "\n\n";
      cout << "Your turn: " << hangman.getPlayer(2).getName() << endl;
      showP2Menu();
      return;
    }

    string response = hangman.processPlayerAction(action, s);

    if (response == "endgame") {
      cout << hangman.getPlayer(2).getName() << " won! Congratulations!!!" << endl;
      break;
    } 
    
    else if (response == "endgame2") {
      cout << hangman.getPlayer(2).getName() << ", you've been hanged! Game over!!!" << endl;
      break;
    } else if (response == "correct") {
      cout << hangman.getPlayer(2).getName() << " guessed correctly" << endl << endl;
      cout << "Continue playing, " << hangman.getPlayer(2).getName() << endl;
      showP2Menu();
      break;
    } else if (response == "incorrect") {
      cout << hangman.getPlayer(2).getName() << " guessed incorrectly" << endl << endl;
      cout << "Your turn: " << hangman.getPlayer(1).getName() << endl;
      showP1Menu();
      break;
    } else if (response == "drew") {
      cout << hangman.getPlayer(1).getName() << " is hanging you" << endl << endl;
      cout << "Your turn: " << hangman.getPlayer(2).getName() << endl;
      showP2Menu();
      break;
    }
  }
}

void Interactive::introduceRules() {
  cout << "-------Welcome to my local Hangman-------\n";
  cout << "This game will have two players: Player 1 and Player 2.\n"\
      << "Each player will enter their name and player 1 will enter a secret word.\n\n";
  cout << "There are a few rules of engagement.\n";
  cout << "1. The secret word must be of the English alphabet, meaning only nouns, verbs or adjectives are accepted.\n"\
      << "Alphanumeric strings, numbers, punctuations and special characters are not accepted.\n\n";
  cout << "2. Player 2 must enter either a single character or a word.\n"\
      << "\ti. If a single character is entered and it matches with any of the characters in the word supplied by player 1,\n"\
      << "\t\tthe character is placed in all the places where there is a match inside the player 2's word container.\n\n"\
      << "\tii. If a word is entered and it matches with either the entire secret word, or a section of the secret word,\n"\
      << "\t\tthat section is entered into the guess word. In either case, the guess word now matches the secret word, player 2 wins.\n\n\n";

  cout << "3. If not, player 1 may draw one element of the stickman figure.\n" \
      << "If player 1 completes the diagram before the player 2 guesses correctly, \n"\
      << "then player one has won. Else player 2 has won. \n";
}

void Interactive::showP1Menu() {
  restart:
  cout << hangman.getPlayer(1).getName() << ", make your move\n";
  cout << "1. Draw\t2. Skip\t3. Read rules\t4. Quit\n";

  int choice;

  cin >> choice;

  string guess;
  if (choice == 1) {
    awaitInstruction("draw");
  } else if (choice == 2) {
    awaitInstruction("skip");
  }else if (choice == 3) {
    introduceRules();
    goto restart;
  } else if (choice == 4) {
    awaitInstruction("quit", "1");
  } else goto restart;
}

void Interactive::showP2Menu() {
  restart:
  cout << hangman.getPlayer(2).getName() << ", make your move\n";
  cout << "1. Guess\t2. Read rules\t3. Quit\n";

  int choice;

  cin >> choice;

  string guess;
  if (choice == 1) {
    cout << "Make a guess: ";
    cin >> guess;
    awaitInstruction("guess", guess);
  } else if (choice == 2) {
    introduceRules();
    goto restart;
  }
   else if (choice == 3) {
    awaitInstruction("quit", "2");
  } else goto restart;
}



int main(void) {
  string player_1_input, secret_word, player_1, player_2;

  cout << "\n\nPlayer 1: Enter your name and secret word in the format: <name> <secret word>\n";
  getline(cin, player_1_input);

  stringstream ss(player_1_input);

  ss >> player_1 >> secret_word;

  bool isAlpha = std::all_of(secret_word.begin(), secret_word.end(), [](unsigned char c) {
    return std::isalpha(c);
  });

  if (!isAlpha) {
    cout << "Secret word must contain only alphabets" << endl;
    return 0;
  }

  cout << "Player 2: Enter your name in the format: <name>\n";
  getline(cin, player_2);
  
  Interactive *hangmanGame = new Interactive(secret_word, player_1, player_2);
  hangmanGame->showP2Menu();

  return 0;
}
