objs = fmt_col 

all: $(objs)

.SUFFIXES:
%.o:%.c
	gcc $< -c -g

%:%.o
	gcc $< -o $@  -g


clean:
	rm -rf $(objs) *.o
