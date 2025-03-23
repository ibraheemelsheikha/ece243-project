/*

Pseudo-code:

//check if move is valid function
if (board[row][col] not empty):
  return false
valid = false
for (each direction around (row,col)) {
  r = row + dx, c = col + dy
  foundOpponent = false
  while (board[r][c] is opponent's piece) {
    move further in direction (dx, dy)
    foundOpponent = true
  }
  if (foundOppnent and board[r][c] is player's piece) {
    valid = true
  }
}
return valid

//place a piece and flip tiles function
(row, col, player_color)
if isValidMove:
  placePiece(row, col, player_color)
  for each direction where opponent pieces are surrounded
    flipPiece
  
//check if a player has any valid moves function
for each empty position:
  if isValidMove
    return true
  return false

//switch turns function
if currentplayer = black
  currentplayer = white
currentplayer = black

//check if game over function
if no valid moves for white and black
  return true
return false

//determine the winner function
count black, white
  if black > white
    return black
  else if white > black
    return white
  else
    return draw
  
//main loop
clearBoard
initializeBoard
setFirstPlayer(coinFlipWinner) //first player can be decided by a coin flip with
black/white sides?
while not game over:
  if player has valid moves  
    (row, col) = getInput
    placeAndFlip(row, col, player_color)
  switch player
show winner
*/