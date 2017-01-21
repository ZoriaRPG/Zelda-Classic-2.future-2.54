Understanding Arrays in ZScript
v0.4
Author: ZoriaRPG

Part I: Basic Usage

In the simplest context, arrays are a series of variables, stored in memory as one large variable table. 
Instead of each individual value occupying memory space, the entire aray (of any given size) uses
the same amount of space as one normal variable.

For example, here we have twelve variables that we would normally store as:
	
int x = 0;
int y = 1;
int z = 2;
int dir = 3;
bool flying = false;
bool swiming = false;
bool usingRing = true;
int screen = 30;
int dmap = 7;
float spaceFree = 10.30;
int hp = 64;
int keys = 8;

Each of these uses one 'slot' available to us, for a variable.
	
Instead of using twelve unique variables, we can condense this into one array. Because we have variables of
each of the three main datatypes (bool, int, float), and because of the way ZScript handles both variable types,
and typecasting, we can use one float array for all of them:

float Vars[12]={0,1,2,4,0,0,1,30,7,10.3000,64,8};

In this example, the first index (position Vars[0], holding a value of '0') would take the place of int x; above.
The second, taking the place of int y; is Vars[1], holding a value of '1'.
The third, taking the place of int z; is Vars[2], holding a value of '2'.
The fourth, taking the place of int dir; is Vars[3], holding a value of '4'.

The fifth, was originally a boolean, bool flying;. We have that in Vars[4], the fifth position, with a value of '0'.
Because you can typecase from float/int to boolean, ZC will interpret a '0' here as 'false', and any other value as 'true'.

The sixth, Vars[5], takes the place of bool swimming; Again, the value here is '0' (false).
The seventh, Vars[6], takes the place of usingRing. Here, we've initialised it with a value of '1' (true).

The eigHth, Vars[7] replaces int screen. We've initialised this with a value of '30'.
The ninth, Vars[8], replaces int dmap, and is initialised with a value of '7'.

For the tenth position, Vars[9], is replacing float freeSpace; and holds a value of '10.3000'.

In this case, we are genuinely using a float. Because ZC uses ints and floats interchangably, it is best to 
	use float arrays so that you may use all three datatypes in the same place.

The eleventh position, Vars[10], replaces int hp;, and is initialised with a value of '64'.
The twelvth, and final position, Vars[11], replaces int keys;, and holds a value of '8'.

Indices:

Positions in an array, are defined as 'indices' (singular: 'index'), a.k.a. 'elements' (singular: 'element'). 

In maths, an array, or set, is noted by representing a series of limnked values between two curled braces, but it
can often be more useful to imagine it as a table; in this case, of twelve SLOTS...

Vars[][][][][][][][][][][][]

The first position, is index '0', represented as Vars[0].

When we reference that, we target index 0, which is the first slot, indicated here with a star:

        Vars[*][][][][][][][][][][][]
        ...
            or in this SET , as '1' 
                vars[12]= { 1,0,0,0,0,0,0,0,0,0,0,0 };
                    ...
                        This is how you will *initialise arrays*, which we will soon explore, so keep it in mind.

The number between the braces is the index number, starting with '0': The last index of the array, is always 
its size *less one*, so in the case of Vars[], the last inddex (or element, or slot), is eleven, and we reference it as
Vars[11].

In visual terms, that would be this slot (marked with a star):
    When we reference that, we target index 0, which is the first slot, indicated here with a star:

        Vars[][][][][][][][][][][][*]
        ... again, in this SET, marked as '1'
                vars[12]= { 0,0,0,0,0,0,0,0,0,0,0,1 };
                
Always remember that array index mumbering BEGINS AT ZERO, and ends at 'ARRAY SIZE - 1'. 
    * This is critical in using the function, SizeOfArray(), and why we use <= when making loops based on the array size.
            
An array with 512 indices ( e.g. arr[512] ) will have indices arr[0] through arr[511].

Unfortunately, we do not want to remember all of this using raw numerals to represent the array indices, on a regular basis.
Instead, we want to asign some constants to these INDEX values:

//Constant		Index
const int POS_X 	= 0;
const int POS_Y 	= 1;
const int POS_Z 	= 2;
const int DIR 		= 3;
const int FLYING 	= 4;
const int SWIMMING 	= 5;
const int USINGRING 	= 6;
const int SCREEN 	= 7;
const int DMAP 		= 8;
const int FREESPACE	= 9;
const int HP		= 10;
const int KEYS		= 11;

In so doig, we can reference an array index using language, instead of numbers...

The constant (on the left), matches the index number, on the right.
Thus, Vars[DIR] is Vars[3], and Vars[KEYS] is the same as Vars[11].

This is far more convienent, in that it makes your code easier to read (and comprehend), and that it makes it brutally easy
to change the purpose of an index. 

Say for example, that you make a lot of code that uses Vars[DMAP], and you decide that you (for whatever reason) wish to change
the array index holding the value of vars[DMAP] from vars[8] to Vars[6]. If you did that, with *hardcoded values*, you would
need to search through all of your code for every instance of Vars[8] (you are bound to miss some instances), and change
every single one to read as Vars[6].

With the values assigned as constants, and by always referencing them in your code using those constants 
(i.e. always referencing this index as Vars[DMAP], and NEVER as vars[8]. all you need do is change the conatant:
const int DMAP = 8
...to
cont int DMAP = 6.

THen, every instance in your code that calls that index will be automatically updated when you compile.

Using *well-named* constants will also healp you immensely when debugging your code, as it's easy to become lost in a sea of 
numbers in braces.

//! Initialising Arrays with SETS

//A set is represented hen declaring an array, as a series of numbers, separated by commas, beteen a paid of curly braces:
{    }





////////////!!! FINISH SECTION

Im the following example, the number between the braces [ x ] is the index, whereas the corresponding value
between the curly braces, is the value OF that index, so:

float Vars[12]={0,1,2,5,0,0,1,30,7,10.3000,64,8};

Vars[DIR] is INDEX 3, which is the FOURTH position here, holding a value of '5'.

The value of INDEX 9 (Vars[9]), is the tenth position here, and is '10.3000'.


Assigning constants allows us to access information in the array, using that constant, to represent the index 
number, so that we never again need to remember it.

Thus, Vars[KEYS] is the same as Vars[11].

Thus, we can wasily make a call using the information int he array, as we would a normal variable:

if ( Vars[SWIMMING] ) 
	
would be used, instead of if ( swimming )

...

Of course, sometimes the name of an array can be long, and we don;t always want to type all of that out in detail,
so we instead, use a special function, designed to read into the array, as a shortcut:

float Is(int pos){
	return Vars[pos];
}

This function returns the value of Vars[ pos ]. It accepts one argument ('pos') and passes that argument to the return 
instruction, so that we may call:

if ( Is(SWIMMING) )

This is identical to calling ( if Vars[SWIMMING] ) because we are passing the constant 'SWIMMING' to the 
function as an argument, and it is using that constant when returning the value held in that array index.

Now, that usage is as a boolean, but we can also do:
	
if ( Is(DMAP) > 20 ) 
	
That is a fully valid expression, and because Vars[DMAP] will return a value of '30', the expression is evaluated 
as 'true'. 

We can also invert this, with a not ( ! , bang ) :

if ( !Is(DMAP) > 20 )
	
The value held in Vars[DMAP] is still 30, so this would evaluate as 'false'.

Those are some basic models, for using arrays. 
	
Likewise, we can also create a function to store, or change a value in an array:

void UpdateSwimming(float set){
	Vars[SWIMMING] = set;
}

Using this:

UpdateSwimming(1);

This changes the value of Vars[SWIMMING] from '0' to '1'.

void AddKey(){
	Vars[KEYS]++;
}

//Adds +1 to Vars[KEYS].


//////////////////////////
/// Part II: For Loops ///
/////////////////////////////////////////////////////////
/// The 'for loop' is one of the most powerful tools at your disposal, particularly when dealing with arrays.
/// In conrast to a while loop, that runs while a condition is evaluated as true, or false, a FOR LOOP runs
/// **for** a specific duration, expressed as follows:

for ( int i = 0; i < min; i++ )

/// In this example, we create a for loop, starting at 0. It runs, increasing the value of 'i' each cycle
/// until i == min.


A for loop, has three components. The base declaration (int i = 0 above), followed by a separator ';'.
Then, the operating limit, declared as i < min above, where min is an external variable, followed by the separator ';'.
Finally, an operational factor (increment, or decrmement; stated above as i++, which increases the value of 'i'
each pass. Thus, the loop will run through every index of the array, allowing you to perform batch operations.

/// Note: If you have an external variable that you wish to use as the main variable in a for loop, you can do this:
int i = 10;
for (; i < 0; i--)

/// The already-declared value of 'i' (10) us used here. Instead of declaring it in the for loop, you may just add a leading separator ';'
/// and the rest of the instructions follow.

/// This is useful when you are running multiple loops that operate on one main variable; but this is a rare occurence.

// ! Iteration 

Here is a practise routine, to learn, and practise making arrays for use
with iterative for loops:

First, a reminder: Many of the internal ZScript variables, are arrays. 
In this example, we will make use of Link->Counter[], which is an array
with a size of [32]. 

Here is a list of the indices used by Game->Counter[32]:

Game->Counter[32]=
        {   CR_LIFE,        CR_RUPEES,      CR_BOMBS,       CR_ARROWS,      
            CR_MAGIC,       CR_KEYS,        CR_SBOMBS,      CR_SCRIPT1,     
            CR_SCRIPT2,     CR_SCRIPT3,     CR_SCRIPT4,     CR_SCRIPT5,  
            CR_SCRIPT6,     CR_SCRIPT7,     CR_SCRIPT8,     CR_SCRIPT9, 
            CR_SCRIPT10,    CR_SCRIPT11,    CR_SCRIPT12,    CR_SCRIPT13,
            CR_SCRIPT14,    CR_SCRIPT15,    CR_SCRIPT16,    CR_SCRIPT17,    
            CR_SCRIPT18,    CR_SCRIPT19,    CR_SCRIPT20,    CR_SCRIPT21,    
            CR_SCRIPT22,    CR_SCRIPT23,    CR_SCRIPT24,    CR_SCRIPT25     };
            
Knowing that each player uses 32 indices to hold their stats, we will set a constant for that, so that we may call it in our loops.
This is extremely prudent, as if we expand the size of any given set, we can simply update the value of this one consstant.
rather than updating any instance sof a hardcoded value for it.

const int PLAYER_STATS_INDICES_PER_CHAR = 32;

For this example, let us presume that we will be making a quet with three player characters: Link, Marty, and Jennifer.

in  doing, we have a function that sets the present character:
    void SetPlayerChar(int character_id); //Sets the present (selected character) to character_id.
...
and a function to read the present player character:
    int getPlayerChar(); //Returns the ID of the present (selected character)
    
    
//Constant for the backup set of values 


We know that we use 32 values to store the counters for Link, and as we will be needing a backup set for each character, 
we'll be using a routine to store, and read the backup values. The number of these will be the same as the number of main
values, so in addition to the 32 counter values, we'll need another 32 to hold backups.

Therefore, we make a constant with the offset (the first index that wills tore a backup value). In this case, the offset is 
'32', as we use indices 0 through 31 for the first set of values, and indices 32 through 63 for the backups. 

In this way, we can make a function that calls : index+PLAYER_STATS_BAK 

//Sets the backup value of a single stat in the array t a specified value.
void SetStatBackup(int stat, int val){
    PlayerStats[stat+PLAYER_STATS_BAK] = val;
}


In sl doig, we can easily modify the values stored in this subset of the main array, by using this OFFSET as an adjustment.

const int PLAYER_STATS_BAK = 32; //32 attribs duplicated, = +32

//! Constants for the characters
const int CHARACTER_LINK = 0; //32 indices for stats, plus 32 backups = indices 0- through 63.
const int CHARACTER_MARTY = 64; //Link's indices end at 63, so the next index becomes the FIRAT INDEX of the next character.
                                //...thus, index 64 is the '0' index for character 2. THis means that we can reference in in for loops
                                //without needing to make special adjustments tot he loop. The loop remains the same size, and calls
                                //using the Marty's constant, so instead of starting at zero, the loop starts at 64.
                                //Marty uses indices 64 through 127.
const int CHARACTER_JENNIFER = 128; //Likeise, the next player starts at index 128. THe size used by any one of the characters is 64 indices.
                                    //Therefore, our required array size is 64* ( number of characters ) 
                                    //In this example, we have three characters, so the array size is 64 * 3, or 192.
                                    
float PlayerStats[192];



//! Making an interation function using this array, and comstants.

Now, let's use a for loop to make a function t store the present values of each counter, into the backup slots in the array.

void BackupPlayerStats(int char_id){
    for ( int q = 0; q <= PLAYER_STATS_INDICES_PER_CHAR; q++ ){
        PlayerStats[char_id+q+PLAYER_STATS_BAK] = Game->Counter[q];
    }
}

In this example, we use our offsets, tp copy the entire set of counters from Game->Counter[q] to the backup set
for any character. 

Let's break that down:

The function uses char_id as an input to define what character to use, so let's consider that we're using marty.

We assigned Marty an offset of 64, in the constant CHARACTER_MARTY, so we'll call the function as follows:

BackupPlayerStats(CHARACTER_MARTY);

As an instruction, this would become:

for ( int q = 0; q <= PLAYER_STATS_INDICES_PER_CHAR; q++ ){
        PlayerStats[CHARACTER_MARTY+q+PLAYER_STATS_BAK] = Game->Counter[q];
}

Let's further break this down,a nd see how these constants are doing our work for us:

PLAYER_STATS_INDICES_PER_CHAR = 32
CHARACTER_MARTY = 64
PLAYER_STATS_BAK = 32

Thus, our for loop would look like this, with hardcoded values:
for ( int q = 0; q <= 32; q++ ){
        PlayerStats[64+q+32] = Game->Counter[q];
}

Therefore, if we assume that q = 0l as it would on the first pass, the value of Game->Counter[CR_LIFE] will be copied into
PlayerStats[64+0+32]
...or
PlayerStats[96]

That's precisely where we want it, and the function will copy the values of ALL 32 COUNTERS  T THEIR RESPECTIVE POSITIONS
in the array, in one stroke.

Nnote however, hw useful our constants have become...

If we need to change the number of total indixes, or the offsets, for anything, all it takes is adjusting one constant, rather
than chasing down hardcoded values.

Note also how the use of a constant for the character offset allows us to use the same function to back up the stata for any
of our three chARACTERS, BY CALLING that function and using the named constant for the desired character as its argument:

BackupPlayerStats(CHARACTER_LINK);

That would do precisely the same backup, again, in one command, reading every counter, and backing the up, but for the Link character.
No additional function is needed, all action is swift, and it is stored int he same array as Marty's information, in its own 
block of indices.

See how the maths change. using the Link constant... For Marty, the information was stored in indices 96 through 127, but
for Lin, with a character ID offset of zero:

for ( int q = 0; q <= PLAYER_STATS_INDICES_PER_CHAR; q++ ){
        PlayerStats[CHARACTER_LINK+q+PLAYER_STATS_BAK] = Game->Counter[q];
}

PLAYER_STATS_INDICES_PER_CHAR = 32
CHARACTER_LINK = 0
PLAYER_STATS_BAK = 32

Thus, our for loop would look like this, with hardcoded values:
for ( int q = 0; q <= 32; q++ ){
        PlayerStats[0+q+32] = Game->Counter[q];
}

This stores his datum in indices 32 through 63. 

Thus, the table looks like this:

Game->Counter[32]
[][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][] 
-----> Copied into:

//Playertats[192]                                                //Values                   ( Indices )
[][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][] //Link Main Stats          ( 0 to 31 )
[][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][] //Link Backup Stats        ( 32 to 63 )
[][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][] //MARTY's Main Stats       ( 64 to 95 ) 
[][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][] //MARTY's BACKUP Stats     ( 96 to 127 ) 
[][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][] //Jennifer's Main Stats    ( 128 to 159 )
[][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][] //jennifer's Backup Stats  ( 160 to 191 )


//! WhaT IF WE WANT TO ADD ANOTHER CHARACTER
//Add another conatnt for it

//! Why to make arrays larger than needed.


///////////////////////////////
//// SizeOfArray() Function ///
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Another critical component when using for loops, with arrays, is the function SizeOfArray(int array).
To use this, you specify the aray ny name as the argument for SizeOfArray(). Thus, if you are checking
against the aray Vars[12], you instruct as follows:

for ( int q = 0; q <= SizeOfArray(Vars); q++)

/// SizeOfArray() always uses one argument, the identifier name of the array, as declared. You enter this as the name only
/// without braces. Thus, SizeOfArray(Vars) is correct, **not** SizeOfArray(Vars[]).

/// You need to ensure that you use <= or >= here, so that the last, or first index position is read.
/// ***An alternative to this, a custom function in RPG.zh, Array(int arr) simplifies this, by automatically adding +1 to the array size.
/// If you use my custom Array(int arr) function, you can use < or > as normal.

/// With an array, you want to run loops like this:

for ( int q = 0; q <= SizeOfArray(arrName); q++ )

/// This will run a loop, starting at index '0', until the loop reaches the last index of the array.

/// You may also decrement the loop, as follows:

for ( q = SizeOfArray(arrName); q >= 0; q-- );

/// Normally, you want an increment type (var++) return; as this reads indices starting at '0' and is useful
/// in performing Trace() functions, based on the pass. 
/// However, should you want to run special decremented versions, for a particular application, you may do this.

/// You may also specify a specific starting index, and a specific decrment.
/// Thus, if you have:

int Table[100]; and you want to read each TENTH position, you would do:
for ( int q = 0; q <= SizeOfArray(Table); q+10 )
 ...which will return index 0, 10, 20, 30, 40, 50, 60, 70, 80, and 90.

/// You may also begin reading at a specific index:
for ( q = 10; q <= SizeOfArray)Table); q+10 )
...which will return values of index 10, 20, 30, 40, 50, 60, 70, 80, and 90.

/// For the interim, you need only worry about incremental arrays, starting at 0,a nd reading the entire array.

//////////////////////////
/// Why this is useful...
/// Practical Applications
///
/// Let's say that you have an array, acting as a table of enemies possible on a screen.
/// ...and you want to check is a given screen enemy is from that table:

int EnemyTable[10]={3,16,17,18,24,27,40,45,60,131};
	for ( int q = 1; q <= Screen->LoadNPCs(); q++ ) { //Reads all enemies on the screen.
	npc enem = Game->LoadNPC(q); ///Uses the present value of 'q' (the pass number), to identify a specific NPC.
	for ( int w = 0; w <= SizeOfArray(EnemyTable); w++ ){
		int listenem = EnemyTable[w]; //Assigns the value held in the index of EnemyTable, at the current pass to a variable.
		if ( enem->ID == listEnem ) { //If the present pass reading screen enemies, matches a value in the array holding enemy numbers...
			enem->HP = 100; //Changes that enemy's HP to 100.
		}
	}
}

/// This is an example of a NESTED FOR LOOP. The main loop (operating on variable q) is running, and in each
/// pass of that for loop, a SECOND for loop checks the array EnemyTable, operating on the value 'w'.
/// If the value of EnemyTable[w] matches the value of LoadNPC[q], it gives it 100 HP.

/// This is a prime example of how to use for loops with arrays, to accomplish a goal.
/// You can next as many for loops as you want. 
/// Without a Waitframe() instruction in a for loop, all of its passes occur in ONE FRAME. You want this
/// for these types of operations; but not for DRAWING commands (to be explained in 'How To: Draw Commands').
///
///


/////////////////////////////////////////////////////
/// Part III: Building and Using Table Structures ///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

We have covered using arrays to do basic checks, but what if you want to check a host of things, by making a 
	table, such as matching XP to a given enemy by ID, and assigning drops?

To do this, we need to make the array a 'virtual structure'.
	When doing this, imaging making a table in a spreadsheet:

int EnemTable[100] = { 	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
			
Here, we essentially have a structure/table, with ten rows. Each row has ten elements, for a total of 100 indices.
In this case, we will start with that each property is for the first row (indices 0 to 9):

Index 0: Enemy ID
Index 1: Enemy HP
Index 2: Enemy Tile
Index 3: Enemy CSet
Index 4: Enemy X
Index 5: Enemy Y
Index 6: Enemy Direction
Index 7: Enemy touch damage.
Index 8: Enemy Weapon
Index 9: Enemy Weapon Damage

Now, each of the nine following rows, will maintain the same information for an additional enemy. 
	Thus, we can store all ten of these details, for ten enemies, in one structure. 
		
Next, we need to assign constants:
	
const int ENEMYROW = 10; //This is used in combination with PASS, in calculating table position.

//Table Columns: Each of these corresponds to a virtual 'column' in our structure. 	
const int ENEMY_ID = 0;
const int ENEMY_HP = 1;
const int ENEMY_TILE = 2;
const int ENEMY_CSET = 3;
const int ENEMY_X = 4;
const int ENEMY_Y = 5;
const int ENEMY_DIR = 6;
const int ENEMY_TOUCH = 7;
const int ENEMY_WEAP = 8;
const int ENEMY_WDAMAGE = 9;
	
Let us assume that we want to read something from this array. 

	
int pass = 0;
for (; pass <= SizeOfArray(EnemTable); pass++){
	npc enem = Game->LoadNPC(q); ///Uses the present value of 'q' (the pass number), to identify a specific NPC.
	enem->HP = EnemTable[pass*ENEMYROW + ENEMY_HP];
}

//This uses the variable pass, as a basis. For the first ten screen enemies, we change the HP of those enemies to 
//the value of EnemTable[ENEMY_HP] for each row (0 to 9).

We use basic math, for the main calculations in specifying the array index in the for loop:
	pass (starting with 0, ending at 9) is the base value, multiplied by ENEMROW (a value of 10).
Thus, on the first pass, the first value in the calculation [EnemTable pass*ENEMROW] is 0, the next pass, '10'
and so forth.

The second part of the calculation, is '+ENEM_HP'. This moves the pointer, from index 0 on the first pass, 
to index 1 on the first pass (the enemy HP for the first row).

On the next pass, the value of the variable 'pass' becomes '1'. 

Thus, we calculate: EnemTable[pass*10 + ENEM_HP]
as
EnemTable[1*10 + ENEM_HP]
...or...
EnemTable[10 + ENEM_HP]
...or...
EnemTable[11].

..thus assigning the value held in EnemTable[11], HP for the second row, to that enemy.
	
Using rows, and columns as constants, we can perform calculations with our for loops, and assign the needed 
datum en masse. 

	///////////FINISH THIS SECTION

Now, we set up a for loop, that
	
for ( int pass = 0; pass

         ////////////////////////////

//////////////////////////////////////
///            Part IV             ///
///  COLUMS, and ROWS = STRUCTURES ///
//////////////////////////////////////

Traditional programming languages allow the user to make *structures*, which you can think of, as arrays built 
out of arrays. These fall into a few categories, including the 2D array, and 3D array. I shall explain both of 
those presently, but it is important to note that NEITHER are POSSIBLE with ZC.

A 2D array is built like this:

int Table[5]={ int characters[20], int powers[50], int spells[100], int items[256], int statistics[9] };

A 3D array might look like this:


int Table[5]={ int characters[20], int powers[50], int spells[100], int items[256], int statistics[3]={ int Mental[2], int Physical[2], int Spiritual[3] } };

My goodness, that looks complicated; hmm?

Well, the way it works, is that each of those, has arrays, inside arrays, allowing someone to cross-index 
elements easily.

In ZC, we can;t build structures, but we can develop TABLES that work in a way that is useful, to bind together 
related bits of information.

Let us say that you want to make a structure, that has 20 characters.
Each character, can have 50 powers, 100 spells, 256 items, and nine total statistics. 

Instead of storing all of these in many small arrays, we can out them ALL into ONE array.

Then you ask, 'How will we ever find anything? Won;t it be too confusing?'

The short answer, is 'No, not confusing to use', but it does require some set-up.

The first thing that we do, is to determine the total number of variables PER CHARACTER:

We may need 

Add up the total nunber of additional fields that we will need. In this case:
powers : 50
spells : 100
items: 256
stats : 9

-------------
415


THus, we need 415 index positions, PER CHARACTER< to store everything.

Now, we need to put up some constants, as identifiers for where each set of values starts:
	
const int POWERS = 0; //This starts at arr[1], and ends at arr[50]
const int SPELLS = 50; //This starts at arr[51] and ends at arr[151]
const int ITEMS = 150; //This starts at arr[151] and ends at arr[406]
const int STATS = 405; //This starts at arr[406] and ends at arr[415]

These form our MAIN IDENTIFIER constants!

Now, let us look at our array:

CharStats[415];

CharStats, now holds enough information, to store the datum for one character. 
	We shall call this ONE ROW of datum. 

The next step, is to start giving useful constants to the indivisual elements. 

***We DO NOT want to do this by their exact array index position!***
	
Instead, we want to give them more logical values, AS IF they were in THEIR OWN arrays.

Thus, 
/// Powers
const int FLIGHT = 0;
const int HEATVISION = 1;
const int SUPERSTRENGTH = 2;
const int SUPERSPEED = 3;
const int XRAYVISION = 4;
const int PHASING = 30;
///etc

/// Spells

const int FIREBALL = 0;
const int RAYOFFROST = 1;
const int DEATHBOLT = 2;
const int DOOMFINGER = 3;
const int RECOVERY = 4;
const int DRAGONSLAVE = 80;
const int NIGHTFALL = 91;
///etc

/// Items
const int IT_SWORD = 0;
const int IT_LASERGUN = 1;
const int IT_POTLAUNCHER = 2;
const int IT_BATARANG = 3;
const int IT_CRIBBAGEDECK = 4;
const int IT_LUCKYCOIN = 50;
const int IT_ATOMICBOMB = 201;
//etc

/// Stats
const int MUSCLE = 0;
const int STAMINA = 1;
const int AGILITY = 2;
const int BALANCE = 3;
const int SPEED = 4;
const int INTELLECT = 5;
const int SOUL = 6;
const int PERCEPTION = 7;
const int INFLUENCE = 8;

//!* These form our GROUP IDENTIFIER constants.

Now, we can COMBINE these constants, in each groupm with one of the MAIN IDENTIFIER constants like this:

POWERS+DEATHBOLT

Thus, ( POWERS = 0 ) + ( SUPERSPEED = 3 ) = 3. Index position 3 is the spell, the Super Speed Power.

SPELLS+DRAGONSLAVE

Thus, ( SPELLS = 50 ) + ( DRAGONSLAVE = 80 ) = 130. index position 130, is the spell, Dragonslave.

ITEMS+CRIBBAGEDECK 

Thus, ( ITEMS = 150 ) + ( CRIBBAGEDECK = 4 ) = 154. Index position 154 is the Cribbage Deck item.

STATS+SOUL

Thus, ( STATS = 405 ) + ( SOUL = 6 ) = 411. Index position 411, is the value of the Soul stat.


To access this, for our character, we would do:
	CharStats[ITEMS+CRIBBAGEDECK] = x;

This would set the value of the cribbage deck item, to X.

In an statement: if ( CharStats[POWERS+BEATHBOLT] ) {
			//Do something
	This would evaluate if index 155 has a value of 0, or a non-zero value. 

Thus, not only have we set up COLUMNS for the individual items, spells, and powers, but we have set up a 
	structure so that we can access them as GROUPS.

Yet, we have twenty characters. Does this mean that we need twenty arrays with all this information in each?

Thankfully, no. There is a safe, easy, and simple way to handle all twenty of our marching men.

Multiply the index size of the array, by 20:
Each row is for a single character, so we make 20 (virtual) ROWS.
	
Thus, we change: CharStats[416];
to
CharStats[8320];

(Note: You cannot declare an array using a formula, or a constant. the number between the braces [ ] needs to be
a numeral in ZC. Thus, CharStats[8320]; is valid, but CharStats[416*20]; is not valid. You **can do this**
when *USING* an array, but **not** when *declaring* it)

Now that we have CharStats[8320]; we may proceed, to assign constants to our characters:

const int CHAR_MURRAY = 0;
const int CHAR_LARRY = 1;
const int CHAR_CURLEY = 2;
const int CHAR_MOE = 3;
const int CHAR_SHEMP = 4;
const int CHAR_CLARK = 5;
const int CHAR_ANNA = 6;
const int CHAR_LEXI = 7;
const int CHAR_SAM = 8;
const int CHAR_LUCY = 9;
///etc

Now, at last, we have COLUMS (GROUPS, and SUBGROUPS), and ROWS.

To find something in this table, for a *SPECIFIC CHARACTER*, we need one more, CHARACTER_ID, and we do this:

Thus, we declare a constant:

constant int CHARACTER_ID = 416;

That is fair enough. We can read into an array, using CHARACTER_ID, and always return the value of arr[416].

'Wait', you ask.., 'how does that help us?'

This little gen of an identifier, allows us to use multiplication inside the index fields, when we want to *USE*
the array.


Note, that this is not the character NAME, it';s a token that we're goint to use to index all twenty ROWS:
( CHARACTER_ID * CHAR_MURRAY ) == ( 416 * 0 ) 
This puts our magic pointer, at index 0, which is where all the things associated with Character Murray, 
begin (at row '0'). 

( CHARACTER_ID * CHAR_MURRAY ) + SPELLS + FIREBALL 
This puts us at the index of the fireball spell, for Murray.

( CHARACTER_ID * CHAR_MOE ) == ( 416 * 3 ) 
This puts us at the start of the attributes for Moe. Thus, pointing us to row 3 (the fourth row, as we count 
	from zero).
( CHARACTER_ID * CHAR_MOE ) + ITEMS + IT_LUCKYCOIN 
This points to the index of the lucky coin item *FOR* Moe. 

Let us see that in math:

 CHARACTER_ID * CHARACTER_MOE = 1248
ITEMS + IT_LUCKYCOIN = 200

Therefore, we're using these token words, to point to index 1448. We don't need to remember that value, ever, 
ever. 
We only need to remember our special CONSTANTS, and use them wisely. 

if ( CharStats[ ( CHARACTER_ID * CHARACTER_LUCY ) + ITEMS + ATOMICBOMB ] && CharStats[ ( CHARACTER_ID * CHARACTER_SHEMP ) + POWERS + SUPERSPEED ] ) {
	//The world is over. 
	
void SetCharItems(int character){	
	int pass = 0;
	for ( int q = ( (CHARACTER_ID*character) + ITEMS); q < (q + 255); q++ ) {
		if ( CharStats[q] && !Link->Item[pass] ) {
			Link->Item[pass] = true;
		}
		if ( !CharStats[q] && Link->Item[pass] ) {
			Link->Item[pass] = false;
		}
		pass++;
	}
}