#include <iostream>
#include <vector>
using namespace std;

class Instrument {
public:
  virtual void makeSound() const = 0;
private:
};

class Brass : public Instrument {
public:
  Brass(unsigned mouthpiece_size) :  mouthpiece_size(mouthpiece_size) {}
  virtual ~Brass() = 0;
  virtual void makeSound() const;
private:
  const unsigned mouthpiece_size;
};

Brass::~Brass() {}

void Brass::makeSound() const {
  cout << "To make a sound... blow on a mouthpeice of size " << mouthpiece_size
       << endl;
}

class Trumpet : public Brass {
public:
  Trumpet(unsigned mouthpiece_size) : Brass(mouthpiece_size) {}
private:
};
  
class Trombone : public Brass {
public:
  Trombone(unsigned mouthpiece_size) : Brass(mouthpiece_size) {}
private:
};

class String : public Instrument {
public:
  String(unsigned pitch) : pitch(pitch) {}
  virtual ~String() = 0;
  virtual void makeSound() const;
private:
  const unsigned pitch;
};

String::~String() {}

void String::makeSound() const {
  cout << "To make a sound... bow a string with pitch " << pitch << endl;
}

class Violin : public String {
public:
  Violin(unsigned pitch) : String(pitch) {}
private:
};

class Cello : public String {
public:
  Cello (unsigned pitch) : String(pitch) {}
private:
};

class Percussion : public Instrument {
public:
  virtual void makeSound() const;
  virtual ~Percussion() = 0;
private:
};

Percussion::~Percussion() {}

void Percussion::makeSound() const {
  cout << "To make a sound... hit me!" << endl;
}

class Drum : public Percussion {
public:
private:
};

class Cymbal : public Percussion {
public:
private:
};

class Musician {
public:
  Musician() : instr(nullptr) {}

  void acceptInstr(Instrument* instPtr) { instr = instPtr; }

  Instrument* giveBackInstr() { 
    Instrument* result(instr); 
    instr = nullptr;
    return result;
  }

  void testPlay() const {
    if (instr) instr->makeSound(); 
    else cerr << "have no instr\n";
  }

private:
  Instrument* instr;
};

class MILL {
public:
  void receiveInstr(Instrument& instr) {
    instr.makeSound();
    for (size_t i = 0; i < inventory.size(); i++) {
      if (!inventory[i]) {
	inventory[i] = &instr;
	return;
      }
    }
    inventory.push_back(&instr);
  }

  Instrument* loanOut() {
    for (size_t i = 0; i < inventory.size(); i++) {
      if (inventory[i]) {
	Instrument* instr = inventory[i];
	inventory[i] = nullptr;
	return instr;
      }
    }
    return nullptr;
  }

  void dailyTestPlay() const {
    for (size_t i = 0; i < inventory.size(); i++) {
      if (inventory[i]) {
	inventory[i]->makeSound();
      }
    }
  }
private:
  vector<Instrument*> inventory;
};
  
// PART ONE
int main() {

    cout << "Define some instruments ------------------------------------\n";
    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12) ;
    Violin violin(567) ;
  
    // use the debugger to look at the mill
    cout << "Define the MILL --------------------------------------------\n";
    MILL mill;
  
    cout << "Put the instruments into the MILL --------------------------\n";
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);
  
    cout << "Daily test -------------------------------------------------\n";
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
  
    cout << "Define some Musicians---------------------------------------\n";
    Musician harpo;
    Musician groucho;
  	
    cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
    groucho.testPlay();	
    cout << endl;
    groucho.acceptInstr(mill.loanOut());
    cout << endl;
    groucho.testPlay();
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
  
    cout << endl << endl;
  
    groucho.testPlay();	
    cout << endl;
    mill.receiveInstr(*groucho.giveBackInstr());
    harpo.acceptInstr(mill.loanOut());
    groucho.acceptInstr(mill.loanOut());
    cout << endl;
    groucho.testPlay();
    cout << endl;
    harpo.testPlay();
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
  
    cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";
  
    // fifth
    mill.receiveInstr(*groucho.giveBackInstr());
    cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
    mill.receiveInstr(*harpo.giveBackInstr());

  
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
  
    cout << endl;
}
