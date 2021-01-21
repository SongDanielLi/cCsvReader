CC = gcc
TARGET  = Main
RM      = rm -f

SRC_DIR = ./
OBJ_DIR = obj/

CFLAGS  = -I./ -g -Wall -O0

SRC  = $(wildcard $(patsubst ./%, %*.c, $(SRC_DIR)))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(basename $(SRC))))

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lm
	
$(OBJ_DIR)%.o: %.c
	@mkdir -p $(OBJ_DIR)/$(<D)
	$(CC) $(CFLAGS) -c $< -o $@ -lm

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

## clean
.PHONY: clean
.SILENT: clean
clean:
	$(RM) $(OBJS) $(TARGET)