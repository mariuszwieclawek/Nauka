CC=gcc
CFLAGS=-I.
#CFLAGS=

OBJECTS = daytimetcpcliv6 daytimetcpsrvv6 checkopts daytimetcpcliv6_02 daytimetcpsrvv6_02 daytimetcpcliv4_02 \
		daytimetcpsrvv4_02 daytimetcpcliv4_03 daytimetcpsrvv4_03 daytimetcpcliv4_04 daytimetcpcliv6_03 \
		daytimetcpsrvv6_03 daytimetcpcliv6_04 daytimetcpsrvv6_04


all: $(OBJECTS)

$(OBJECTS):%:%.c
	@echo Compiling $<  to  $@
	$(CC) -o $@ $< $(CFLAGS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)	
	
clean:
	rm  $(OBJECTS)
