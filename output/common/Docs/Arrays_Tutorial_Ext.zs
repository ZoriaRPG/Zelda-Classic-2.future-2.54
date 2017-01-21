//We make two arrays, for Relatives, and Relations

int Relatives[10];
int Relations[10];

//We map constants for Relatives, with the first index used as temp memory.
const int MEMORY = 0;
const int MUM = 1;
const int DAD = 2;
const int GRAN = 3;
const int GRAMPS = 4;
const int SIS = 5;

//..and repeat bfor Relations. MEMORY is pre-defined as Index[0] and will remain valid for both arrays. 
const int HARRY = 0;
const int LIZ = 1;
const int TOM = 3;

//..and set some states. 
const int ALIVE = 1;
const int DEAD = 0;

void ( CheckLivingStatus(){ //We can accept inputs here, which we can type as English text, too...see below.
	if ( Relatives[MUM] == ALIVE ) Relatives[MEMORY] = MUM;
	if (Relations[HARRY] == ALIVE 0 ) Relations[MEMORY] = HARRY;
}

void ( CheckLivingStatus(int relative, int relation){ //We can accept inputs here, which we can type as English text, too...see below.
	if ( Relatives[relative] == ALIVE ) Relatives[MEMORY] = relative;
	if ( Relations[relation] == ALIVE ) Relations[MEMORY] = relation;
}

//Now we combine them

int Relatives[20];

const int MEMORY = 0; //We ret5ain the MEMORY index, as a catch-all, then...
const int MEMORY_RELATIVES = 1; //Add a specific one for relatives, and...
const int MEMORY_RELATIONS = 2; //...a specific one for relations, so that we can segregate them, as we did above. 

//We adjust the index constants as needed\, merging them.
const int MUM = 2; 
const int DAD = 4;
const int GRAN = 4;
const int GRAMPS = 6;
const int SIS = 7;
const int HARRY = 8;
const int LIZ = 9;
const int TOM = 10;

//Status remains unchanged.
const int ALIVE = 1;
const int DEAD = 0;

//Then we do Search and Replace, as follows:
// Find Relatives[MEMORY]
//...replace with Relatives[MEMORY_RELATIVE]

// Find Relations[MEMORY]
//...replace with Relatives[MEMORY_RELATION]

// Find Relations[
//...replace with Relatives[

//! Changed Code! If this was thousands of lines, that made calls to these arrays,
//it would take hours, or days to change it if we used fixed values, but we can do it
//mere *seconds* this way.

void ( CheckLivingStatus(){ //We can accept inputs here, which we can type as English text, too...see below.
	if ( Relatives[MUM] == ALIVE ) Relatives[MEMORY_RELATIVE] = MUM;
	if (Relations[HARRY] == ALIVE ) Relatives[MEMORY_RELATION] = HARRY;
}

void ( CheckLivingStatus(int relative, int relation){ //We can accept inputs here, which we can type as English text, too...see below.
	if ( Relatives[relative] == ALIVE ) Relatives[MEMORY_RELATIVE] = relative;
	if ( Relatives[relation] == ALIVE ) Relatives[MEMORY_RELATION] = relation;
}


//You'll see here, that both are absolutely identical in operation, but we use
//one fewer gd register, by merging the arrays.

//Because we have the variables assigned to constants, we can do code changes more freely,
//and we can assign the constants to appropriate array indices on-the-fly, before compilation. 




