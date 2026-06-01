# -------Welcome to my Hangman game-------
### This game will have two players: Player 1 and Player 2.
_Each player will enter their name and player 1 will enter a secret word._

*There are a few rules of engagement.*
###### 1. The secret word must be of the English alphabet, meaning only nouns, verbs or adjectives are accepted.
_Alphanumeric strings, numbers, punctuations and special characters are not accepted._

###### 2. Player 2 must enter either a single character or a word.
  > i. If a single character is entered and it matches with any of the characters in the word supplied by player 1,
       the character is placed in all the places where there is a match inside the player 2's word container.
  > ii. If a word is entered and it matches with either the entire secret word, or a section of the secret word,
       that section is entered into the guess word. In either case, the guess word now matches the secret word, player 2 wins.

_If not, player 1 may draw one element of the stickman figure. If player 1 completes the diagram before the player 2 guesses correctly, 
then player one has won. Else player 2 has won._
