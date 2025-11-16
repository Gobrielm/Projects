import React, { useState } from 'react'

function Square( {value, onSquareClick} ) {
  return (
    <button className="square" 
    onClick={onSquareClick}
    style={{
      width: '50px',
      height: '50px',
      fontSize: '24px',
      padding: 0,
      margin: 0,
      border: '1px solid black',
      outline: 'none',
      verticalAlign: 'top'
    }}
    >
      {value}
    </button>
  )
}

function calculateWinner( {squares} ) {
  // Check across
  for (let i = 0; i < 3; i++) {
    if (squares[i][0] == squares[i][1] && squares[i][1] == squares[i][2] && squares[i][0] != ' ') {
      return squares[i][0];
    }
  }
  // Check up/down
  for (let i = 0; i < 3; i++) {
    if (squares[0][i] == squares[1][i] && squares[1][i] == squares[2][i] && squares[0][i] != ' ') {
      return squares[0][i];
    }
  }

  //Check diagonals
  if (squares[0][0] == squares[1][1] && squares[1][1] == squares[2][2] && squares[1][1] != ' ') {
    return squares[1][1];
  }
  if (squares[2][0] == squares[1][1] && squares[1][1] == squares[0][2] && squares[1][1] != ' ') {
    return squares[1][1];
  }

  return ' ';
}

function Board( {isXNext, squares, onPlay} ) {
  function handleClick(row, col) {
    if (squares[row][col] !== ' ') return;

    // copy the board
    const nextSquares = squares.map(rowArr => [...rowArr]);

    if (isXNext) {
      nextSquares[row][col] = 'X';
    } else {
      nextSquares[row][col] = 'O';
    }

    onPlay(nextSquares);
  }

  const winner = calculateWinner({squares: squares});
  let status = true;
  if (winner !== ' ') {
    status = 'Winner: ' + winner;
  } else {
    status = 'Next Player: ' + (isXNext ? 'X': 'O');
  }


  return (
    <>
      <div className="status">{status}</div>
      <div className="board-row">
        <Square value = {squares[0][0]} onSquareClick={ () => handleClick(0, 0)} />
        <Square value = {squares[0][1]} onSquareClick={ () => handleClick(0, 1)} />
        <Square value = {squares[0][2]} onSquareClick={ () => handleClick(0, 2)} />
      </div>
      <div className="board-row">
        <Square value = {squares[1][0]} onSquareClick={ () => handleClick(1, 0)} />
        <Square value = {squares[1][1]} onSquareClick={ () => handleClick(1, 1)} />
        <Square value = {squares[1][2]} onSquareClick={ () => handleClick(1, 2)} />
      </div>
      <div className="board-row">
        <Square value = {squares[2][0]} onSquareClick={ () => handleClick(2, 0)} />
        <Square value = {squares[2][1]} onSquareClick={ () => handleClick(2, 1)} />
        <Square value = {squares[2][2]} onSquareClick={ () => handleClick(2, 2)} />
      </div>
    </>
  )
}

export default function TicTacToe() {
  const [history, setHistory] = useState([Array(3).fill(Array(3).fill(" "))]);
  const [currentMove, setCurrentMove] = useState(0);
  const isXNext = currentMove % 2 === 0;
  const currentSquares = history[currentMove];

  function handlePlay(nextSquares) {
    const nextHistory = [...history.slice(0, currentMove + 1), nextSquares];
    setHistory(nextHistory);
    setCurrentMove(nextHistory.length - 1);
  }

  function jumpTo(nextMove) {
    setCurrentMove(nextMove);
    setIsXNext(nextMove % 2 === 0);
  }

  const moves = history.map((squares, move) => {
    let description;
    if (move > 0) {
      description = 'Go to move #' + move;
    } else {
      description = 'Go to game start';
    }
    return (
      <li key={move}>
        <button onClick={() => jumpTo(move)}>{description}</button>
      </li>
    )
  })

  return (
    <div className='game'>
      <div className='game-board'>
        <Board isXNext={ isXNext } squares={ currentSquares } onPlay={handlePlay}/>
      </div>
      <ol>{moves}</ol>
    </div>
  );
}