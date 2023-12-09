package aginterface

// import rl "github.com/gen2brain/raylib-go/raylib"

type Shape int
type State int

const (
	X Shape = 1
	O Shape = -1 
	NAS Shape = 0


	// game states that can be achieved by each board (can also be used in general game)
	GOING State = 0x010
	VICTORYX State = 0x011
	VICTORYO State = 0x100
	TIE State = 0x101
)

type Limits struct {
	xo int32
	yo int32
	xf int32
	yf int32
}

type BoardPiece struct {
	Shape Shape
	Box Limits // xy from upper left and lower right
	Selected bool
	
}

type Board struct {
	Content [9]BoardPiece
	BoardBox Limits
	BoardState State
	Count int
}

func NewBoard(box Limits) Board {
	lengthx := box.xf - box.xo
	lengthy := box.yf - box.yo

	xo := box.xo
	x1 := box.xo + lengthx/3
	x2 := box.xo + 2*lengthx/3
	x3 := box.xo + lengthx
	yo := box.yo
	y1 := box.yo + lengthy/3
	y2 := box.yo + 2*lengthy/3
	y3 := box.yo + lengthy

	bp := [9]BoardPiece{
		{NAS, Limits{xo, yo, x1, y1}, false},
		{NAS, Limits{x1, yo, x2, y1}, false},
		{NAS, Limits{x2, yo, x3, y1}, false},

		{NAS, Limits{xo, y1, x1, y2}, false},
		{NAS, Limits{x1, y1, x2, y2}, false},
		{NAS, Limits{x2, y1, x3, y2}, false},

		{NAS, Limits{xo, y2, x1, y3}, false},
		{NAS, Limits{x1, y2, x2, y3}, false},
		{NAS, Limits{x2, y2, x3, y3}, false},
	}

	b := Board{
		bp,
		box,
		GOING,
		0,
	}

	return b
}

