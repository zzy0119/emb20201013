
LDFLAGS+=-pthread

server:main.o thr_chn.o thr_chnlist.o medialib.o
	gcc -o $@ $^ $(LDFLAGS)

clean:
	rm *.o server

