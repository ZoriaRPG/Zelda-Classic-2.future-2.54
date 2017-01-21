Use Arrays Instead of Global vars to Avoid Save File Problems
Tags: scripting, arrays, save file, global, variables, strings, cheat limitations. 

[u][b]How to Use Arrays, Instead of Global Vars [/b][/u]
[i]....to Avoid Needing New Save Files When Updating a Quest[/i]
 
As some of you may know, if you add a global variable to a quest, when modifying your scripts, it will necessitate a new save slot for your quest. Failing to use a new (fresh) save slot, will almost assuredly mean that whatever you added, won;t work.
 
Coupled with this, is the nasty problem of a limit of 255 global variables--in practical terms, because of how the ZASM registers work, half of that, for around 128 (!) at most.
 
In this tutorial, I'm not only going to teach you how to use arrays and constants to avoid both of these pitfalls, but also a few other tips, and tricks for using 'global strings' without eating up global registers, and how to use constants, coupled with a few handy functions, to make it all work as if it were simple, ordinary variables--at least as much as possible.

The most crucial point to understand, is that when you declare an array, ZQuest reats it as a single global variable, no-matter what index size you assign to it. In addition, arrays are dynamically read, and written, so you won;t need to worry about a large array slowing ZC down to a crawl. It's no slower than any other variable usage, in general, or in practise. 

THus, the first step, is to consider how many global variables you will ever need, and then multiply that, by a factor of no less than ten. Trust me, plan ahead and you won;t have regrets about not doing it, later. 

For this purpose, I tend to declare this sort of array with a size of NO LESS than 8192. 

'8,192!?', you ask, 'I will never need that many variables!'. Probably not, but why not play it safe, and assume that you may, hmm?

So, let's go ahead and make that array. For the purose of this article, we'll call it GameVariables:

[code]
float GameVariables[8192];
[/code]

Before we get into this too deeply, let's examine how ZC pre-allocates space for your global variables, and arrays...

//! Explaining Arrays and variables for Dummies
Often, newcomers, and veterans alike may have trouble comprehending how variables (including arrays) are stored. I'll try to 
simplify this with a metaphoric explanation...

Imagine that ZC has 255 'postboxes'. Each one can hold a value, and they are numbered from 1 to 255. 

Each time you declare a global variable, or a global array, it is assigned a 'postbox'. That 'postbox' is then stored in the
quest save, both as being used, and as having an address number.

Thus, let's say you declare this:

int myvar;
int myvar2;
int myvar3;

Each of these three declarations is given its own postbox. They are assigned an address NUMBER IN THE ORDER IN WHICH YOU DECLARE THEM, 
so myvar is postbox 1, myvar2, is postbox 2, and myvar3 is postbox 3. 

When you are done, and load this quest, ZC will read these, and PERMANANTLY allocate a postbox to them, in the SAVE FILE. 

The rest of the available 252 postboxes are set to store TEMPORARY values, like sorting bins. They can;t be used to hold
any permanant value. 

Therefore, if we start the game, boxes 1, 2, and 3, are locked to the address (pointer IDs) of the declared variables.

If you later go in and add int myvar4, recompile, and save the quest file, the quest file ITSELF will have an address for 
postbox 4, but because it did not exist when you saved the game, ZC won;t know how to deliver post to it!

Next, we must consider how an array (of any type) is stored. 

Let's say that you declare MyArray[256]; That is, an array with 256 indices, numbered from 0 to 255. 
Each of those indices is like its own little postbox, but RATHER THAN using one of the main postboxes for each index, 
ZScript stores ALL of the indices in one of its postboxes. So, picture it like a big postbox, with many small compartments inside, each directed to a flat (apartment) number. 
The array itself is in the address '4', but the indices are in 4-0, 4-1, 4-2, 4-3, and so forth, through 4-255. 

This means that we can safely tuck 256 variables into one postbox. 

Where this matters, is that you can declare a very large array--one with far more space than you believe that you need. I usually make these a size of 4096, which looks like this
when declaring it:

float ArrayName[4096];

That is 4096 compartments, in one postbox. Each of the indices 'compartments' is given its own address too, when created, so, if you want to make it BIGGER by adding compartments (indices) later, you can;t.
This is why we want to start big: Far bigger than we need, as the indices that you do not use, don;t actually take up any extra space. 

Now, you will probably not need that many--although very complicated scripts certainly MAY--but the nice thing is that while ZScript cannot add more postboxes or compartmwnts
later, BECAUSE the compartments are already there, just not in use, it can assign them to new 'tenants' that need to occupy their space.

Thus, if you later need to add variables, you can do so, SAFELY, without needing a new save file, as the compartments to store
whatever you want to store in then, have already been allocated. They're just waiting to be occupied. Thus, by making the array OVERSIZED< we ensure that we have room for FUTURE EXPANSION. 


Wait a moment, you may be thinking. Why did you make that a float, and what do I do when i need booleans? The answer to both of these questions, is that you never* need to declare a boolean array. I learnt that lesson the hard way, and I'm saving you time, right here and now. ZC treats floats, when returning values, juis as it woud for both ints, and bools. The ZC typecasting will treat any 0-value as 'dfalse', and any non-zero value as 'true', so that takes care of your booleans. As for ints, you can always store an int, in a float type variable, or array in ZScript. The reverse however, is NOT true. If you make the array an int type, then you will not be able to store the decimal portion of floating point vakues in it. Thus, by starting with a float declaration, we can safely use all three types at our leisure. 

Use of Constants

One of the common complaintd with array usage, is that it's harder to remember what something like MyVars[1240] is, or does. That is absolutely true, and in fact, it's highly advisable not to HARDCOSE numeric values when calling these indices to read them.

Instead, we make it easy, by declaring constants, with a name that helps us esaily identify what the index holds.

let's say for example, that an array index, maybe 1260, holds the ID of the last item Link used. Wehat we do here, is declare a constant with a USEFUL NAME
such as:

const int LINK_LAST_A_ITEM = 1260;

Now, instead of calling MyVars[1260] we can instead, call MyVars[LINK_LAST_A_ITEM]

This has multiple :

it makes code easier to read. Instead of a garbled mess of numbers, we now explicitely state what the value is that we want to read, or modify
when we call it.

It makes it easier to change things. if you want to add a variable, but you want it in index 1260, say
const int LINKS_PANTS = 1260;

...you can MOVE the references in ALL of your scripts to MyVars[LAST_A_ITEM_USED] simply by changing the value assigned TO THE CONSTANT. Thus, is we now want 
LINK_LAST_A_Item to use Array index 3011, we change:

const int LAST_A_ITEM_USED = 1260;
to 
const int LAST_A_ITEM_USED = 3011;

When we recompile, every reference in all of your scripts to MyVars[LAST_A_ITEM_USED] is AUTOMATICALLY updated to use index 3011 instead of 1260.
This ensures that we don;t need to go through thousands of lines of code to find, and change a pile of hardcoded values, as we would if we instead called MyVars[126];

All you need do, is change ONE VALUE, and you are DONE.

It makes code easier for other people to comprehend, by using natural language.

It is much easier for someone reading your script, to look at MyVars[LAST_A_ITEM_USED} than MyVars[1260[. The former explicitely tells them
what that value is for, while the latter requires them to spend unholy smounts of time, FIGURING IT OUT. 

It allows us to get the data of an array index, with a function, very easily. Consider that you want to make a function that RETURNS the value of an array index. 

With this method, we can make a function like this:

int Value(int index){
	return MyVars[index];
}

Now, when we want to know the vaslue of MyVars[LAST_A_ITEM_USED] , we AGAIN use the constant, but this time, when we CALL
that function:

Val(LAST_A_ITEM_USED);

That gives us a lot of fluidity in how we read values, set values, and change values. Again, it also makes our code
much easier to read, and it saves us from hardcoding NAMED functions such as:

LastAItemUsed(){
	return MyVars[3011];
}

In fact, this is so powerful, that it gives us incredibly useful shortcuts. Instead of doing:

if ( MyVars[LAST_A_ITEM_USED] != 0 ) 
	we can do
if ( Val(LAST_A_ITEM_USED) != 0 )
	
That may not seem signifigant, but if the array has a long name, such as EnemyCollisionRoutineValues[], we don;t want to type that over an over.

Likewise, we can use multiple shortcut names for these functions, and give them purpose by name. I personally prefer using Is(int index) to get a value, as
	this reads as either an integer, or boolean type return very easily. To do this, we OVERLOAD the function as follows:
		
int Is(int index){
	return MyVars[index];
}

int Is(int index, int value){
	return MyVars[index] == value;
}

Now we can call:

Is(SWIMMING) to find out if Link is swimming (by storing a value other than 0 when he is in this index, and 0 if he is not...
or
Is(LAST_A_ITEM_USED,I_MAGIC_THING);

Which will return true if the last item used (as stored in our array) is that item. 
	
It's also useful to have a set of functions to modify the values:

//Sets an array value to a specific number.
void Set(int index, int value){
	MyVars[index] = value;
}

//Increases the value of an index by +1
void Inc(int index){
	MyVars[index]++;
}

//Reduces the value of an index by -1
void Dec(int index){
	MyVars[index]--;
}

//Increases the value of an index by 'amount'
void Inc(int index, int amount){
	MyVars[index] += amount;
}

//Reduces the value of an index by 'amount'
void Dec(int index, int amount){
	MyVars[index]-= amount;
}

We call them simply:

Instead of calling 
MyVars[LINK_IS_SPINNING] = 1;

we call 
Set(LINK_IS_SPINNING,1);

or instead of 

Using constants for Array Pointers
	
//! No you can't, pudding brain. ZScript doesn;t support assigning anything to a constant other than a raw numeric literal!
	
All arrays have a pointer, assigned as a unique integer ID when declared. This is very useful, as if we have a long array
	name that we need to use often, we can make a constant s a short name, like this:

const int LINKSTATS = LinkStatsAndvariables;

The pointer for LinkStatsAndVariables, whatever it may be, is assigned to the constant, and all future calls for that constant
	will automatically point to that array.

Example:

//Returns the value of 'index' in the array with pointer 'arr'
int Val(int arr, int index){
	return arr[index];
}

//Increases the value of index 'index' of array 'arr' by +1
void Inc(int arr, int index){
	arr[index]++;
}

if we want to know the value of LINK_LAST_X in the array LinkStatsAndvariables[], we call this as:
	
Val(LINKSTATS,LAST_LINK_X);

In use, :
if ( Val(LINKSTATS,LAST_LINK_X) > 20 ) 
	

COmpare the length of that in characters to:
if ( LinkStatsAndVars[LAST_LINK_X] > 20 )
	

or Inc(LINKSTATS,LAST_LINK_X);


You'll see that we save a few characters, so you may do this with arrays tha have long names, for which you wish to add an abbreviation to call in your statements, or instructions. 

In addition, it means that when we are writing out instructions, we will only need to use parens, not braces '[ ]'
in our instructions. This has the benefit of not needing an additional character, so that there is a smaller chance of error. It's also faster, as in a statement, 
we usually have fingers hovering over left and right parens, not (square) braces, so every time you need to call something, you save a second, or two. Those truly do add up fast.

Each Index, One Constant

Returning Values With Functions

Creating Functions for this Application

Reading our Values

Setting Values

Value Increments (use of '++' and '--')

const int LESS = -214747.9999;
const int PLUS = 214747.9999; 


----------------------------------------
Part II: Initialising Values as Non-Zero
----------------------------------------
		Ensuring that these arrays can be read in a modified script set.
		Initialising as an arbitrary value to know if an array index has been set.  
		
One thing that it is prudent to do, if you want to be able to easily call boolean checks against indices in arrays that
	you make for this purpose, is to set all of their indices to an arbitrary value that you are unlikely to ever have in a game.
		
	For example: -20967.3812
	It's very unlikely that this EXACT value will ever be used. 
	Thus, if you declare the array, and set all of its indices to this value as part of your standard format, you can then
		declare a constant:
	const float NOT_INIT = -20967.3812;
	
	Than, in your scripts, if you need to check if an array value was never used, where it could be '0' either way, you can
		check against this value first:
	if ( MyArray[INDEX] == NOT_INIT ) 
		If it matches that value, it was never used, and you can set it to '0' to establish it as an initial false return, or any other vakue that
	you desire, which will return true. 
	
	You can easily initialise these values in a global ~init script with one for loop:
		
	for ( int q = 0; q < SizeOfArray(MyVars); q++ ) MyVars[q] = NOT_INIT;
	
	THis will set all the indices to the desired values when the game loads.
	
	This becomes very important when you have general checks that return if an index is 0/false. 
		
	For example, if you make an entry for : ... //! [[ADD EXPLANATION AND EXAMPLE ]]
	
	Then, in a global active script, you can check if a value that you added by adding a constant was never initialised, 
		and if so, set it to whatever value you want it to be as a starting value, or otherwise work with it. 
			
		This becomes important 
		

/* 
----------------------------------------------------------
Part III : Abusing Screen->D In The Stead of Global Arrays
----------------------------------------------------------
*/

But what if you are modifying a project, where you would need a global array, but you didnlt originally have one? Clearly, 
	you can;t just add one in, and expect it to work, as it would require a global register to be reserved in the save file, 
and as that won;t be reserved, the array will never have a valid pointer in operation.

If we are already locked into a project, that did not have a vast global array, adding one is effectively the same as adding a global variable.
People with saved games, can;t use the update, without starting over. Thus, if you failed to plan ahead for this contingency, there is a somewhat cheap way around it.

How do we do this, if we CANNOT use global arrays?!
	
The way to handle this is easy, or well, at least, simple.... What is that, you ask?

Why, Screen->D of course.

Every screen on every DMap of a game, has its own array, and these are both accessibly globally, and are *retained through saved games* (unlike local arrays, and most other screen properties).

If we need to store some new values, and don;t wish to invalidate save files, we can abuse these to meet that need.

Simply find some screens on any DMap that have free Screen->D[registers], and use those. This works in muc the same way as using a global array, except that it's more logical to make functions specifically to return values from them.

Let's say that we need to store a variable for a script that makes Link jump, on a timer. 

ordinarily, we could use int JumpTimer; or an array index in a global array to store this, but as we don;t have that luxury, a ZScript function--SetDMapScreenD(), and its counterpart GetDMapScreenD() will help us store, and retrieve that information.

Using the above example, we make some constants:

const int JUMP_TIMER_REG_DMAP = 0; //DMap 0 
const int JUMP_TIMER_REG_SCREEN = 79; //Screen 79 of DMap 0
const int JUMP_TIMER_REG = 3; //Screen->D[3] on Screen 79 of DMap 0

Now, to set this value, or read it, we make a function set:

void SetLinkJumpTImer(int value){
	Game->SetDMapScreenD(JUMP_TIMER_REG_DMAP,JUMP_TIMER_REG_SCREEN,JUMP_TIMER_REG,value);
}

int GetLinkJumpTimer(){
	return Game->GetDMapScreenD((JUMP_TIMER_REG_DMAP,JUMP_TIMER_REG_SCREEN,JUMP_TIMER_REG);
}

int GetLinkJumpTimer(int value){
	return Game->GetDMapScreenD((JUMP_TIMER_REG_DMAP,JUMP_TIMER_REG_SCREEN,JUMP_TIMER_REG) == value;
}

int IncLinkJumpTimer(){
	int val = Game->GetDMapScreenD((JUMP_TIMER_REG_DMAP,JUMP_TIMER_REG_SCREEN,JUMP_TIMER_REG) += 1;
	Game->SetDMapScreenD(JUMP_TIMER_REG_DMAP,JUMP_TIMER_REG_SCREEN,JUMP_TIMER_REG,val);
}

int IncLinkJumpTimer(int amount){
	int val = Game->GetDMapScreenD((JUMP_TIMER_REG_DMAP,JUMP_TIMER_REG_SCREEN,JUMP_TIMER_REG) += amount;
	Game->SetDMapScreenD(JUMP_TIMER_REG_DMAP,JUMP_TIMER_REG_SCREEN,JUMP_TIMER_REG,val);
}

int DecLinkJumpTimer(){
	int val = Game->GetDMapScreenD((JUMP_TIMER_REG_DMAP,JUMP_TIMER_REG_SCREEN,JUMP_TIMER_REG) -= 1;
	Game->SetDMapScreenD(JUMP_TIMER_REG_DMAP,JUMP_TIMER_REG_SCREEN,JUMP_TIMER_REG,val);
}

int DecLinkJumpTimer(int amount){
	int val = Game->GetDMapScreenD((JUMP_TIMER_REG_DMAP,JUMP_TIMER_REG_SCREEN,JUMP_TIMER_REG) -= amount;
	Game->SetDMapScreenD(JUMP_TIMER_REG_DMAP,JUMP_TIMER_REG_SCREEN,JUMP_TIMER_REG,val);
}

Now, in any script that we have, in which we need to manipulate this data, we can quick;y call it:

if ( GetLinkJumpTimer(16) ) 
	that would return true if our faux globsal variable is exactly 16
		
if ( GetLinkJumpTimer() > 16 ) 
	this would evaluate true if it is 16 or more.
		
Example in use:
	
	const int JUMP_TIME = 
if ( GetLinkJumpTimer() > 1  ) {
	if ( Link->Jump > 0 ) Link->Jump = 0;
	//prevent Link from Jumping again until the cooldown timer expires. 
	DecLinkJumpTimer();
	//If the timer has a value over 0, decreases the timr by '1' every frame. 
if ( GetLinkJumpTimer <= 0 && Link->Jump > 0 ) SetLinkJumpTimer(JUMP_TIME);
	//If Link is jumping and the timer is 0, allow the jump, and set the timer to '100'.


To ensure the highest level of compatibility, we occasionally want to insure that registers do not old values of exactly 0. This allows us to know, each time that we load the game
	if the register was previously used. To do this, we set its value inside the run function of the global active script, to -1.
		Then, if it is -1, we know it was never initialised. 
			
		

/*		
---
		Part IV :
		What We Can Always Add
		*/
		
		Another important thing to remember, is that you can always add instructions to any script, including *local variables, or arrays of any type*
		without invalidating a svae file. You may add anything inside the run() function in any script, and not need to worry about it.
		Furthermore, you may add new functions--including global functions, and constants, without invalidating a quest save file.
		
		Functions are store in the .qst file and accessed directly, while constants are converted to their numeric literal, during compilation. 
			
		This may, or may not be true of headers, as headers may create their own global variables, and arrays. 
		
		For headers, see Chapter V.
		
		
	/*
		Chapter V: Modifying Headers
	*/
		
		If you decide to add a header to a quest, you may encounter the same problem as adding a global variable,
		except it is multipled many times, based on the number off vars that the header uses, and the complexity of the header.
		
		In this case, the only solutution is to modify the header, pointing it to global arrays, or Screen->D. 
			
		If it uses arrays, or vars that do not need to be global, you can also declare arrays inside the run function in your global active script, and make
			data handling functions to push values into those.