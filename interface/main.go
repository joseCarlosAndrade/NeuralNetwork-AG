package main

import (
	// rl "github.com/gen2brain/raylib-go/raylib" // main screen handler
	// gui "github.com/gen2brain/raylib-go/raygui" // gui
	agin "interfaces/aginterface" // module root name(defined in go.mod)/path/to/package
	"fmt"
)

func main() {
	fmt.Println("init")

	// for {
	game := agin.NewGame()
	game.InitScreen()
	game.Run()
	// }
	
	// rl.InitWindow(agin.ScreenWidth, agin.ScreenWidth, agin.ScreenTitle);
	// fmt.Println(agin.ScreenHeight)
	// rl.SetTargetFPS(agin.ScreenFPS)

	// for !rl.WindowShouldClose() {
	// 	rl.BeginDrawing()
	// 	rl.ClearBackground(rl.Black)

	// 	// button := gui.Button(rl.NewRectangle(50, 150, 100, 40), "Button text")
		

	// 	// if button {
	// 	// 	fmt.Println("clicked")
	// 	// }

		
	// 	rl.EndDrawing()
	// }

	// rl.CloseWindow()
}
