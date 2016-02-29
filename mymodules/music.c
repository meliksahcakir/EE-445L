// music.c
// Runs on TM2C123
// Ty Winkler
// Feb 23, 2016

#include "music.h"
#include "notes.c"

int next_note = 1;

//First value is note frequency, second value is x where the note duration is 1/x
//
const unsigned short carolOfTheBells[500] = {   
  Bflat, 2,
	A, 1,
	B, 1,
	G, 2,
  Bflat, 2,
	A, 1,
	B, 1,
	G, 2,
  Bflat, 2,
	A, 1,
	B, 1,
	G, 2,
  Bflat, 2,
	A, 1,
	B, 1,
	G, 2,
  Bflat, 2,
	A, 1,
	B, 1,
	G, 2,
  Bflat, 2,
	A, 1,
	B, 1,
	G, 2,
  Bflat, 2,
	A, 1,
	B, 1,
	G, 2,
  Bflat, 2,
	A, 1,
	B, 1,
	G, 2,
	
	Bflat, 2,
	G, 2,//play with previous note
	A, 1,
	B, 1,
	G, 2,
	Bflat, 2,
	G, 2,//play with previous note
	A, 1,
	B, 1,
	G, 2,
	Bflat, 2,
	G, 2,//play with previous note
	A, 1,
	B, 1,
	G, 2,
	Bflat, 2,
	G, 2,//play with previous note
	A, 1,
	B, 1,
	G, 2,
	
	D, 2,
	Bflat, 2,//played with previous note
	C, 1,
	Eflat, 1,
	Bflat, 2,
	G, 2,//played with previous note
	D, 2,
	Bflat, 2,//played with previous note
	C, 1,
	Eflat, 1,
	Bflat, 2,
	G, 2,//played with previous note
	D, 2,
	Bflat, 2,//played with previous note
	C, 1,
	Eflat, 1,
	Bflat, 2,
	G, 2,//played with previous note
	D, 2,
	Bflat, 2,//played with previous note
	C, 1,
	Eflat, 1,
	Bflat, 2,
	G, 2,//played with previous note
	
	G,2,//Octave higher than normal G
	D, 2,
	Bflat, 2,
	G, 2,//played with previous 3 notes
	G, 1, 
	G, 1,//Played with previous note one octave higher
  G, 1,
	G, 1, //Played with previus note one octave higher
	F, 1, 
	F, 1, //Played with the previous note one octave higher
	E, 1, 
	E, 1, //Played with the preious note one octave higher
	
	D, 2,
	G, 6,
	Bflat, 6,
	D, 6,//one octave lower played with previous 3 notes
	D, 1, 
	D, 1, 
	C, 1,
	B, 1,
	
	C, 2,
	G, 6,
	E, 6,//played with previous 2 notes
	C, 1,
	C, 1,
	D, 1,
	C, 1,
	
	C, 2,
	G, 6,
	B, 6,//played with previous 2 notes
	
// 	//played once
// //Trebel cleff
// carolOfTheBells.music[0]=D;
// carolOfTheBells.music[0]=G;
// carolOfTheBells.music[0]=Bflat;//played for 3 counts with previous 3 notes
// carolOfTheBells.music[0]=D;//half note
// carolOfTheBells.music[0]=D;//half note
// carolOfTheBells.music[0]=C;//half note
// carolOfTheBells.music[0]=Bflat;//half note

// //played once
// //Trebel cleff
// carolOfTheBells.music[0]=C;
// carolOfTheBells.music[0]=G;
// carolOfTheBells.music[0]=E;//previous three notes played together, previous two played for 3 counts
// carolOfTheBells.music[0]=C;//half note
// carolOfTheBells.music[0]=C;//half note
// carolOfTheBells.music[0]=D;//half note
// carolOfTheBells.music[0]=C;//half note

// //played once
// //Trebel Cleff
// carolOfTheBells.music[0]=Bflat;
// carolOfTheBells.music[0]=G;
// carolOfTheBells.music[0]=D;//one octave lower played with previous 3 notes, previous 2 notes for 3 counts
// carolOfTheBells.music[0]=A;//half note
// carolOfTheBells.music[0]=Bflat;//half note
// carolOfTheBells.music[0]=G;
 };


