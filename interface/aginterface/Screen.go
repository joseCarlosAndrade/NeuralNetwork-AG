package aginterface

import (

	rl "github.com/gen2brain/raylib-go/raylib"
)


func (g * Game)InitScreen() {
	rl.InitWindow(ScreenWidth, ScreenHeight, ScreenTitle)
	rl.SetTargetFPS(ScreenFPS)
}

func (g * Game)Run() {

	defer rl.WindowShouldClose()
	
	for !rl.WindowShouldClose() {
		g.input()
		if g.checkGeneralState() {
			if g.State == VICTORYO {
				GameText = "Game ended. Player 2 (O) WINS!"
			} else if g.State == VICTORYX {
				GameText = "Game ended. Player 1 (X) WINS!"				
			} else {
				GameText = "Game ended. TIE!"
			}
			break
		}
		// update
		// draw
		g.drawEverything()
	}
	
}

// returns true if x ,y is within give limits
func insideLimit(x, y int, limit Limits) bool {
	// fmt.Printf("checking: x: %v y: %v, limit: %v\n", x, y, limit)
	if x >= int(limit.xo) + 2 && x <= int(limit.xf) -2 {
		if y >= int(limit.yo)+2 && y <= int(limit.yf) -2 {
			return true
		}
	}
	return false
}

// verifies if the mouse x and y position is inside a piece. If so, change its state to selected
func (g*Game)insideLimitPiece(x, y int, b* Board) {
	for i:=0; i < len(b.Content); i++ {
		piece := &b.Content[i]
		if insideLimit(x, y, piece.Box) {
			piece.Selected = true
			// fmt.Println("changing color of piece", i, piece.Selected)

			// implement click here
			if rl.IsMouseButtonPressed(rl.MouseLeftButton) {
				if g.PlayRound(piece) { 
					b.Count++
					
					if g.Boards[i].Count < 9  {
						g.NextPlayableBoard = i
					} else {
						g.NextPlayableBoard = -1
					}
				}
				
				if b.BoardState == GOING {b.CheckGameState()}
				
			}
						
		} else {
			piece.Selected = false
		}
	}
}

func (g* Game)input() {

	// if rl.IsMouseButtonPressed(rl.MouseButtonLeft) {
	// 	fmt.Println(rl.GetMousePosition())
	// }

	x,y := int(rl.GetMousePosition().X), int(rl.GetMousePosition().Y)

	for i:=0 ; i < len(g.Boards); i++ {

		b := &g.Boards[i]
		// check first if mouse is inside board b
		if insideLimit(x, y, b.BoardBox) && b.Count <9 && g.State == GOING && ( g.NextPlayableBoard ==-1 || g.NextPlayableBoard ==i) {
			// if it is, then checks the board piece
			g.insideLimitPiece(x, y, b)
			break // doesnt need to check all boards if one is detected
		}
	}
}

func (g* Game)drawEverything() {
	rl.BeginDrawing()
	rl.ClearBackground(rl.NewColor(20, 20, 20, 255))

	// everything that has to be done to each 9 boards
	for i := 0; i < len(g.Boards); i++ {
		drawBoard(&g.Boards[i])
	}

	drawBiggerLines()

	g.PutTextToScreen(60, 675, 20)

	rl.EndDrawing()
}

func drawBoard(b* Board) {
	// limits of board
	// rl.DrawRectangle(BoardX, BoardY, BoardWidth, BoardHeight, rl.Gray)

	// draw each rectangle for each board piece
	width := b.Content[0].Box.xf - b.Content[0].Box.xo
	height := b.Content[0].Box.yf - b.Content[0].Box.yo
	// gap := BoardGap + 5
	for i:=0; i < len(b.Content); i++ {
		b := &b.Content[i]
		var color rl.Color = rl.Green
		// fmt.Printf("piece: %v, selected: %v \n", i , b.Selected)
		if b.Selected {
			color.G += 25
			color.B += 90
			color.R += 90
			// b.Selected = false

			// fmt.Println("color is selected")
		}
		// rl.DrawRectangle(b.Box.xo+BoardGap, b.Box.yo+BoardGap, width-2*BoardGap, height-2*BoardGap, color)
		rl.DrawRectangleRounded(rl.NewRectangle(float32(b.Box.xo+BoardGap), float32(b.Box.yo+BoardGap), float32(width-2*BoardGap), 
		float32(height-2*BoardGap)), 0.2, 0, color)

		// teste com gradientes
		// rl.DrawRectangleGradientH(b.Box.xo+BoardGap, b.Box.yo+BoardGap, width-2*BoardGap, height-2*BoardGap, color, rl.Blue)
		b.Selected = false
	}

	// drawing lines (test so far)
	for  i  := 0; i < 2; i++ {
		
		x := b.BoardBox.xo + (int32(i)+1)*BoardWidth/3
		rl.DrawLine(x-1, b.BoardBox.yo, x-1, b.BoardBox.yf, rl.White)
		rl.DrawLine(x, b.BoardBox.yo, x, b.BoardBox.yf, rl.White)
		rl.DrawLine(x+1, b.BoardBox.yo, x+1, b.BoardBox.yf, rl.White)
	}

	for  i  := 0; i < 2; i++ {
		y := b.BoardBox.yo + (int32(i)+1)*BoardHeight/3
		rl.DrawLine(b.BoardBox.xo, y-1, b.BoardBox.xf, y-1, rl.White)
		rl.DrawLine(b.BoardBox.xo, y, b.BoardBox.xf, y, rl.White)
		rl.DrawLine(b.BoardBox.xo, y+1, b.BoardBox.xf, y+1, rl.White)
	}

	// drawing shapes
	for _, piece := range b.Content {
		if piece.Shape == NAS { continue }
		drawShape(piece.Box, piece.Shape, false)

		if b.BoardState == VICTORYX {
			drawShape(b.BoardBox, X, true)
		} else if b.BoardState == VICTORYO{
			drawShape(b.BoardBox, O, true)
		}
		
		// if piece.Shape == X {
		// 	drawShape(piece, X)
		// 	// rl.DrawLine(piece.Box.xo+1+gap, piece.Box.yo+gap, piece.Box.xf-gap, piece.Box.yf - 1 - gap, rl.Red)
		// 	// rl.DrawLine(piece.Box.xo+gap, piece.Box.yo+gap, piece.Box.xf-gap, piece.Box.yf - gap, rl.Red)
		// 	// rl.DrawLine(piece.Box.xo+gap, piece.Box.yo+1+gap, piece.Box.xf-1-gap, piece.Box.yf - gap, rl.Red)

		// 	// rl.DrawLine(piece.Box.xf-gap, piece.Box.yo+gap, piece.Box.xo+1+gap, piece.Box.yf - 1 - gap, rl.Red)
		// 	// rl.DrawLine(piece.Box.xf-gap, piece.Box.yo+gap, piece.Box.xo+gap , piece.Box.yf - gap, rl.Red)
		// 	// rl.DrawLine(piece.Box.xf-1-gap, piece.Box.yo+1+gap, piece.Box.xo+gap, piece.Box.yf - gap, rl.Red)
		// 	// rl.DrawRectangle(piece.Box.xo+BoardGap, piece.Box.yo+BoardGap, width-2*BoardGap, height-2*BoardGap, rl.Red)
		// } else {
		// 	// rl.DrawRectangle(piece.Box.xo+BoardGap, piece.Box.yo+BoardGap, width-2*BoardGap, height-2*BoardGap, rl.Blue)
		// 	drawShape(piece, O)
		// }
	}
}


func drawShape(b Limits, s Shape, big bool) {
	width := b.xf - b.xo
	height := b.yf - b.yo
	gap := BoardGap + 10

	if !big { 
		// rl.DrawRectangle(b.xo+BoardGap, b.yo+BoardGap, width-2*+BoardGap, height-2*+BoardGap, 
		// rl.NewColor(rl.DarkGreen.R+40, rl.DarkGreen.G+40, rl.DarkGreen.B+40, rl.DarkGreen.A) ) 

		rl.DrawRectangleRounded(rl.NewRectangle(float32(b.xo+BoardGap), float32(b.yo+BoardGap), float32(width-2*BoardGap), 
		float32(height-2*BoardGap)), 0.2, 0, rl.NewColor(rl.DarkGreen.R+40, rl.DarkGreen.G+40, rl.DarkGreen.B+40, rl.DarkGreen.A))
	}

	if s == X {
		for i:=int32(0); i < 100; i ++ {
			xl := b.xo + gap + i*(width - 2*gap)/100
			xr := b.xf - gap - i*(width - 2*gap)/100
			y := b.yo + gap + i*(height - 2*gap)/100

			if big {

				rl.DrawCircle(xl, y, 3, rl.Black)
				rl.DrawCircle(xr, y, 3, rl.Black)
				
			}else {
				rl.DrawCircle(xl, y, 4, rl.Red)
				rl.DrawCircle(xr, y, 4, rl.Red)
			}
		}
	} else if s == O {
		radius := (width + 1 - 2*gap)/2 -5
		for i:=0 ; i < 6; i++ {
			if big {
				rl.DrawCircleLines((b.xf + b.xo)/2, (b.yf + b.yo)/2, float32(radius)+float32(i), rl.White)
				
			} else {
				rl.DrawCircleLines((b.xf + b.xo)/2, (b.yf + b.yo)/2, float32(radius)+float32(i), rl.DarkBlue)
			}
			
		}
	}
}

func (b* Board)CheckGameState() { // recicling code from my tic tac toe game
	// b.BoardState = VICTORYO
	

	for i:=0 ; i < 3; i++ {
		// checking lines
		if b.Content[3*i].Shape == NAS {
				
		} else if b.Content[3*i].Shape == b.Content[3*i+1].Shape &&  b.Content[3*i].Shape == b.Content[3*i+2].Shape {
			if b.Content[3*i].Shape == X {
				b.BoardState = VICTORYX
			} else {
				b.BoardState = VICTORYO
			}
			
		}

		// checking rows
		if b.Content[i].Shape == NAS {
				
		} else if b.Content[i].Shape == b.Content[i+3].Shape && b.Content[i].Shape == b.Content[i+6].Shape {
			if b.Content[i].Shape == X {
				b.BoardState = VICTORYX
			} else {
				b.BoardState = VICTORYO
			}
		}               

		}
		// checking diagonals

		if (b.Content[0].Shape != NAS)&&b.Content[0].Shape==b.Content[4].Shape && b.Content[0].Shape==b.Content[8].Shape {
			if b.Content[0].Shape == X {
				b.BoardState = VICTORYX
			} else {
				b.BoardState = VICTORYO
			}
		} else if (b.Content[2].Shape != NAS) &&b.Content[2].Shape==b.Content[4].Shape && b.Content[2].Shape==b.Content[6].Shape {
			if b.Content[2].Shape == X {
				b.BoardState = VICTORYX
			} else {
				b.BoardState = VICTORYO
			}
		}

		for _,v := range b.Content {
			if v.Shape == NAS {
				return
			}
		}
		
}


func drawBiggerLines() {
	thisWidth := 3*BoardWidth+ 2*BoardSpacing
	thisHeight := 3*BoardHeight+ 2*BoardSpacing

	BoardXf := BoardX + thisWidth
	BoardYf := BoardY + thisHeight

	for  i  := 0; i < 2; i++ {
		
		x := BoardX + (int32(i)+1)*thisWidth/3
		rl.DrawLine(x-1, BoardY, x-1, BoardYf, rl.White)
		rl.DrawLine(x, BoardY, x, BoardYf, rl.White)
		rl.DrawLine(x+1, BoardY, x+1, BoardYf, rl.White)
	}

	for  i  := 0; i < 2; i++ {
		y := BoardY + (int32(i)+1)*thisHeight/3
		rl.DrawLine(BoardX, y-1, BoardXf, y-1, rl.White)
		rl.DrawLine(BoardX, y, BoardXf, y, rl.White)
		rl.DrawLine(BoardX, y+1, BoardXf, y+1, rl.White)
	}
}



/*

..X...X..
...X.X...
....X....
...X.X...
..X...X..

...OOO...
.OO...OO.
.O.....O.
.OO...OO.
...OOO...

*/