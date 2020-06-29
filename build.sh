set -e    # if error, stop the build
cc -g -std=c99 -c -I /opt/raylib/src main.c -o ./obj/main.o
cc -g -std=c99 -c -I /opt/raylib/src board.c -o ./obj/board.o
cc -g -std=c99 -c -I /opt/raylib/src pieces.c -o ./obj/pieces.o
cc -g -std=c99 -c -I /opt/raylib/src linked_list.c -o ./obj/linked_list.o
cc -g -std=c99 -c -I /opt/raylib/src assets.c -o ./obj/assets.o
cc -o main obj/main.o obj/board.o obj/pieces.o obj/linked_list.o obj/assets.o -s -Wall -std=c99 -I/opt/raylib/src -L/opt/raylib/release/libs/linux -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
./main

