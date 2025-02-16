main:
	gcc -Wall process_creater.c -o pc.out
	gcc -Wall main.c fifo.c sjf.c stcf.c parser.c utils.c -o main.out

clean:
	rm -rf jobs.txt
	rm -rf a.out
	rm -rf pc.out
	rm -rf main.out