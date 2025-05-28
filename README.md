# scrabble-word-finder
This project is a terminal-based Scrabble word generator that helps players find all valid words they can form using their current letter tiles and a given board letter (either at the start or end of the word).

It implements:

-  Recursive backtracking to explore all permutations of available letters

-  Binary search to efficiently validate generated words against a wordlist

-  Scrabble-style scoring, including the 50-point bonus for using all letters in hand

-  User interaction via console to input hand letters, the board letter, and its position

-  Repeated rounds of gameplay based on user choice

