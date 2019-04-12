#include <iostream>
#include <vector>
using namespace std;

class Instrument {
public:
  virtual void makeSound() const = 0;
  virtual void play() const = 0;
private:
};

class Brass : public Instrument {
public:
  Brass(unsigned mouthpiece_size) :  mouthpiece_size(mouthpiece_size) {}
  virtual void makeSound() const;
private:
  const unsigned mouthpiece_size;
};

void Brass::makeSound() const {
  cout << "To make a sound... blow on a mouthpiece of size " << mouthpiece_size
       << endl;
}

class Trumpet : public Brass {
public:
  Trumpet(unsigned mouthpiece_size) : Brass(mouthpiece_size) {}
  virtual void play() const;
private:
};

void Trumpet::play() const { cout << "Toot"; }
  
class Trombone : public Brass {
public:
  Trombone(unsigned mouthpiece_size) : Brass(mouthpiece_size) {}
  virtual void play() const;
private:
};

void Trombone::play() const { cout << "Blat"; }

class String : public Instrument {
public:
  String(unsigned pitch) : pitch(pitch) {}
  virtual void makeSound() const;
private:
  const unsigned pitch;
};

void String::makeSound() const {
  cout << "To make a sound... bow a string with pitch " << pitch << endl;
}

class Violin : public String {
public:
  Violin(unsigned pitch) : String(pitch) {}
  virtual void play() const;
private:
};

void Violin::play() const { cout << "Screech"; }

class Cello : public String {
public:
  Cello (unsigned pitch) : String(pitch) {}
  virtual void play() const;
private:
};

void Cello::play() const { cout << "Squawk"; }

class Percussion : public Instrument {
public:
  virtual void makeSound() const;
private:
};

void Percussion::makeSound() const {
  cout << "To make a sound... hit me!" << endl;
}

class Drum : public Percussion {
public:
  virtual void play() const;
private:
};

void Drum::play() const { cout << "Boom"; }

class Cymbal : public Percussion {
public:
  virtual void play() const;
private:
};

void Cymbal::play() const { cout << "Crash"; }

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
  
  void play() const {
    if (instr) instr->play();
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

class Orch {
public:
  void addPlayer(Musician& player) {
    players.push_back(&player);
  }

  void play() {
    for (size_t i = 0; i < players.size(); i++) {
      players[i]->play();
    }
    cout << endl;
  }
private:
  vector<Musician*> players;
};
  
// PART TWO
int main() {
    // The initialization phase

    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12);
    Violin violin(567);

    MILL mill;
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);

    Musician bob;
    Musician sue;
    Musician mary;
    Musician ralph;
    Musician jody;
    Musician morgan;

    Orch orch;

    // THE SCENARIO

    //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);

    //The orchestra performs
    cout << "orch performs\n";
    orch.play();

    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);

    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());

    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);

    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());

    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);

    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Ralph joins the orchestra.
    orch.addPlayer(ralph);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();
	
    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());

    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Morgan joins the orchestra.
    orch.addPlayer(morgan);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

} // main

