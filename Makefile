all: rpg

rpg: Player.o Game.o Lab08_main.o
    gcc -Wall Player.c Game.c Lab08_main.c -o rpg

Player.o: Player.c
    gcc -c Player.c

Game.o: Game.c
    gcc -c Game.c

Lab08_main.o: Lab08_main.c
    gcc -c Lab08_main.c

clean:
    rm Player.o Game.o Lab08_main.o rpg