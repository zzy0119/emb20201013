CFLAGS+=-D_XOPEN_SOURCE
LDFLAGS+=-lcrypt

password:password.c
	gcc -o $@ $^ $(CFLAGS) $(LDFLAGS)
