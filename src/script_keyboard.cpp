#include "zc_sys.h"

bool ReadKey(int k);

//For ZASM

bool KeyPresses[55];

void SetZASMKeypresses(){
	for ( int q = 0; q < MAX_KEYS; q++ ) {
		KeyPresses[q] = ReadKey(q);
	}
}

bool PressedKey(int key){ return Keypresses[key]; }	
bool readkeyboard; //Read the keyboard and ignore other input to buttons;


case ZKEY:
{
	int key = ri->d[0];
			

