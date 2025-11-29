# Wordle Game in C
A terminal-based implementation of the popular word game Wordle, written in C.

Overview:

This project implements the classic Wordle game where players attempt to guess 
a hidden 5-letter word within 6 attempts. After each guess, the game provides 
color-coded feedback to help players deduce the correct word.

Features:

 - 🎯 Random word selection from a curated dictionary

 - 🎨 Color-coded feedback using ANSI escape codes

 - 📚 Word validation against a comprehensive dictionary

 - 💾 File-based word storage for persistence

 - 🏆 Win/loss tracking with result display

 - 🔄 Multiple game sessions with different target words

 - 🛡️ Memory-safe with proper allocation and cleanup

Requirements:

 - GCC compiler

 - Linux/Unix terminal (for ANSI color support)

 - C standard library

Installation:

 - git clone <repository-url>
   cd wordle
 
 - Ensure the word dictionary files are present:

    allWords.txt - Complete dictionary for validation

    solutionWords.txt - Target words for the game
    
 - Ensure that hashmap.c, hashmap.h, wordle-play.c and Makefile are present 

 - Type 'make' in terminal
   Type './wordle' after that  
  
Game Rules:

   You have 6 attempts to guess the 5-letter word

   After each guess, you'll receive color-coded feedback:

   Green: Letter is correct and in the right position

   Yellow: Letter is in the word but in the wrong position

   Gray: Letter is not in the word at all

   All guesses must be valid 5-letter English words

   The game ends when you either:

   Guess the word correctly (win)

   Use all 6 attempts without success (loss)

   Enjoy :)

Author:

 - Yerzhan Abeyev
 - Computer Science Student
 - Columbia University
