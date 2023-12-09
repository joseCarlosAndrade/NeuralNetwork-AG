# GO INTERFACE (debugging - remove on final version)

install: # install the dependencies
	go mod tidy

go_interface: 
	mkdir -p ../bin/
	go build -o ../bin/interface main.go

run_interface:
	./../bin/interface
