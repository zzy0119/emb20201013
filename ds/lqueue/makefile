
LDFLAGS+=-ldynamiclist -L/home/emb1013/code20201013/emb20201013/ds/llist

lqueue:main.o lqueue.o
	gcc -o $@ $^ $(LDFLAGS)

clean:
	rm *.o lqueue

