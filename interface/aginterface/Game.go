package aginterface

import rl "github.com/gen2brain/raylib-go/raylib"




// screen
const (
	ScreenWidth int32 = 800
	ScreenHeight int32 = 700
	ScreenFPS int32 = 30
	ScreenTitle string = "Jogo do Asilo"

	

	// board
	BoardX int32 = 80
	BoardY int32 = 50
	BoardWidth int32 = 200
	BoardHeight int32 = 200
	BoardSpacing int32 = 10 // space between different boards
	BoardGap int32 = 5 // gap from the borders
	
	AllBoards int = -1
)

var (
	GameText string = ""
)

type Game struct {
	Boards []Board
	NextPlayableBoard int // number which defines the board that can be played (-1 for all of them)
	State State
	CurrentPlayer Shape
}

func NewGame() *Game {
	// base := NewBoard(Limits{BoardX, BoardY, BoardX+BoardWidth, BoardY+BoardHeight})
	boards:= make([]Board, 9)

	space := BoardWidth + BoardSpacing
	boards[0] = NewBoard(Limits{BoardX, BoardY, BoardX+BoardWidth, BoardY+BoardHeight}) 
	boards[1] = NewBoard(Limits{BoardX +space, BoardY, BoardX+BoardWidth+space, BoardY+BoardHeight}) 
	boards[2] = NewBoard(Limits{BoardX +2*space, BoardY, BoardX+BoardWidth +2*space, BoardY+BoardHeight}) 

	boards[3] = NewBoard(Limits{BoardX, BoardY+space, BoardX+BoardWidth, BoardY+BoardHeight+space}) 
	boards[4] = NewBoard(Limits{BoardX +space, BoardY+space, BoardX+BoardWidth+space, BoardY+BoardHeight+space}) 
	boards[5] = NewBoard(Limits{BoardX +2*space, BoardY+space, BoardX+BoardWidth +2*space, BoardY+BoardHeight+space}) 

	boards[6] = NewBoard(Limits{BoardX, BoardY+2*space, BoardX+BoardWidth, BoardY+BoardHeight+2*space}) 
	boards[7] = NewBoard(Limits{BoardX +space, BoardY+2*space, BoardX+BoardWidth+space, BoardY+BoardHeight+2*space}) 
	boards[8] = NewBoard(Limits{BoardX +2*space, BoardY+2*space, BoardX+BoardWidth +2*space, BoardY+BoardHeight+2*space}) 

	game := &Game{
		Boards: boards,
		NextPlayableBoard: -1,
		State: GOING,
		CurrentPlayer: X, // start as X
	}
	return game
}

func (g * Game)PlayRound(b * BoardPiece) bool {
	if b.Shape != NAS { return false} // if not empty, doesnt play

	if g.CurrentPlayer == 1 {
		b.Shape = X
	} else {
		b.Shape = O
	}
	g.CurrentPlayer *= -1 // invert current player

	return true
}

func (g Game)PutTextToScreen(x, y, fontSize int32) {

	if g.State == GOING {
		if g.CurrentPlayer == 1 {
			GameText = "Player 1 (X)!"
			
		} else {
			GameText = "Player 2 (O)!"
		}
	}
	
	rl.DrawText(GameText, x, y, fontSize, rl.White)
}

func (g *Game) checkGeneralState() bool {
	/// check for board matching
	for i:=0 ; i < 3; i++ {
		// checking lines
		
		if g.Boards[3*i].BoardState == GOING {
				
		} else if g.Boards[3*i].BoardState == g.Boards[3*i+1].BoardState && g.Boards[3*i].BoardState == g.Boards[3*i+2].BoardState {
			if g.Boards[3*i].BoardState == VICTORYX {
				g.State = VICTORYX
			} else {
				g.State = VICTORYO
			}
			return true
			
		}

		// checking rows
		if g.Boards[i].BoardState == GOING {
				
		} else if g.Boards[i].BoardState == g.Boards[i+3].BoardState && g.Boards[i].BoardState == g.Boards[i+6].BoardState {
			if g.Boards[i].BoardState == VICTORYX {
				g.State = VICTORYX
			} else {
				g.State = VICTORYO
			}
			return true
		}               

		}
		// checking diagonals

		if (g.Boards[0].BoardState != GOING)&&g.Boards[0].BoardState==g.Boards[4].BoardState && g.Boards[0].BoardState==g.Boards[8].BoardState {
			if g.Boards[0].BoardState == VICTORYX {
				g.State = VICTORYX
			} else {
				g.State = VICTORYO
			}
			return true

		} else if (g.Boards[2].BoardState != GOING) &&g.Boards[2].BoardState==g.Boards[4].BoardState && g.Boards[2].BoardState==g.Boards[6].BoardState {
			if g.Boards[2].BoardState == VICTORYX {
				g.State = VICTORYX
			} else {
				g.State = VICTORYO
			}
			return true
		}

		for _, b := range g.Boards {
			if b.BoardState == GOING { // verify that the game can still be played 
				return false
			}
		}
		g.State = TIE
		return true // if it gets here, it means that a tie has ocurred

	// if so, updates the game state
}
