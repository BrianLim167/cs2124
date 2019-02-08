/*
Brian Lim
hw01.cpp
Caeser cypher decrypter
*/

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdlib.h>
using namespace std;

//get the encoding shift amount
int get_alpha_shift(const char* filename) {

  ifstream ifs(filename);
  if (!ifs) {
    cerr << "failed to open " << filename << endl;
    exit(1);
  }

  //find the shift from the first line
  int shift;
  ifs >> shift;
  ifs.close();
  return shift;

}

//get encrypted text as a vector of strings
void get_encrypted(vector<string>& buf, const char* filename) {

  ifstream ifs(filename);
  if (!ifs) {
    cerr << "failed to open " << filename << endl;
    exit(1);
  }

  //store each line after the first
  string line;
  ifs >> line; //push out the first line
  while (getline(ifs, line)) {
    buf.push_back(line);
  }
  ifs.close();

}

//decodes an encrypted character
char decrypt_char(char encrypted, int shift) {

  shift = shift % 26

  if (encrypted < 'a' || encrypted > 'z') {
    return encrypted; //leave non-lowercase characters
  }
  if (encrypted - shift >= 'a' && encrypted - shift <= 'z') {
    return encrypted - shift;
  }
  return encrypted - shift + 26; //wrap-around if needed

}

//decodes an encrypted string
string decrypt_string(string encrypted, int shift) {

  string ans = encrypted;
  for (int i = 0 ; i < ans.length() ; i++) {
    ans[i] = decrypt_char(ans[i], shift);
  }
  return ans;

}

int main() {

  const char* ENCRYPTED_FILE = "encrypted.txt";

  int alpha_shift = get_alpha_shift(ENCRYPTED_FILE);
  vector<string> encrypted_text;
  get_encrypted(encrypted_text, ENCRYPTED_FILE);


  for (int i = encrypted_text.size() - 1 ; i >= 0 ; i--){
    cout << decrypt_string(encrypted_text[i], alpha_shift) << endl;
  }

}
