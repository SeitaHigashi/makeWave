makeWave: makeWave.c
	gcc -o makeWave makeWave.c -lm

clean:
	rm makeWave