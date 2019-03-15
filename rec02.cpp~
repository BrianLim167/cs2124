/*
Brian Lim
rec01.cpp
simulates Conway's Game of life
*/

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdlib.h>
using namespace std;

void init_game_board(vector<string>& game_board, const char* filename) {

  ifstream lifestream(filename);
  if (!lifestream) {
    cerr << "failed to open " << filename;
    exit(1);
  }

  string line;
  while (lifestream >> line) {
    game_board.push_back(line);
  }
  lifestream.close();

}

void update_change_state_board(vector< vector<bool> >& change_state_board,
  const vector<string>& game_board) {

    int rows = game_board.size();
    int cols = game_board[0].size();

    for (int r=0 ; r < rows ; r++) {
      for (int c=0 ; c < cols ; c++) {

        int count = 0;
        for (int dx=-1 ; dx <= 1 ; dx++) {
          for (int dy=-1 ; dy <= 1; dy++) {
            if ( (dx != 0 || dy != 0) &&
            (0 <= r+dx && r+dx < rows && 0 <= c+dy && c+dy < cols) &&
            (game_board[r+dx][c+dy] == '*')) {
              count++;
            }
          }
        }

        if ( game_board[r][c] == '-' ) {
          change_state_board[r][c] = (count == 3);
        } else {
          change_state_board[r][c] = (count < 2 || count > 3);
        }

      }
    }

  }

void update_game_board(vector<string>& game_board,
  const vector< vector<bool> >& change_state_board) {

    int rows = game_board.size();
    int cols = game_board[0].size();

    for (int r=0 ; r < rows ; r++) {
      for (int c=0 ; c < cols ; c++) {
        if (change_state_board[r][c]) {
          if (game_board[r][c] == '-') {
            game_board[r][c] = '*';
          } else {
            game_board[r][c] = '-';
          }
        }
      }
    }

  }

void output_game_board(ofstream& out, const vector<string>& game_board){

  int rows = game_board.size();

  for (int r=0 ; r < rows ; r++) {
    out << game_board[r] << endl;
  }

}

int main() {
  int NUM_GENERATIONS = 10;

  ofstream out("output.txt");
  if (!out) {
    cerr << "failed to open output.txt";
    exit(1);
  }

  vector<string> game_board;
  init_game_board(game_board, "life.txt");

  int rows = game_board.size();
  int cols = game_board[0].size();

  vector< vector<bool> > change_state_board(rows, vector<bool>(cols, false));

  out << "Initial world" << endl;
  output_game_board(out, game_board);
  out << "===========================" << endl;

  for (int gen=0 ; gen < NUM_GENERATIONS ; gen++) {
    update_change_state_board(change_state_board, game_board);
    update_game_board(game_board, change_state_board);
    out << "Generation: " << gen+1 << endl;
    output_game_board(out, game_board);
    out << "====================" << endl;
  }

  out.close();

}
