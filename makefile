
# /*************************
#  *Yash Patel                      *
#  *CPSC 2311 Sprint 23 Section 005 *
#  *yjpatel                         *
#  *yjpatel@clemson.edu             *
#  Instructor: Dr. Yvon Feaster     *
#  *************************/
# Config, just variables
CC = gcc
CFLAGS = -Wall -g
LFLAGS = -lm
TARGET = LAB5


# Generater source object, and header lists, also just string variables
C_SRCS := $(wildcard *.c)


HDRS := $(wildcard *.h)

# Generate object list, and filter out any non .o files
OBJS := $(patsubst %.c, bin/%.o, $(wildcard *.c))
OBJS += $(filter %.o, $(patsubst src/%.c, bin/%.o, $(C_SRCS)))




# default target
all: build
	@echo "All Done"


# Link all built objects
build: $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LFLAGS)


# bin directory
bin/%.o: %.c $(HDRS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


# bins the files and directories
bin/%.o: src/%.c $(HDRS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


# cleans the files and directories
clean:
	@rm -f $(TARGET)
	@rm -rf bin


# runs the program
run: build
	./$(TARGET) classdata.csv studentout.txt 1
	./$(TARGET) classdata.csv studentout.txt 2


# finds all .c and .h files in the current directory
which:
	@echo "FOUND SOURCES: ${C_SRCS}"
	@echo "FOUND HEADERS: ${HDRS}"
	@echo "TARGET OBJS: ${OBJS}"