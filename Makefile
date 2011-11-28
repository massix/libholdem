CC		=	gcc
CFLAGS	=	-Wall -Werror -ggdb -ansi --std=c99 # -DUNICODE_ENABLED
LDFLAGS	=	-shared

SRCS	=	\
			card.c \
			init.c \
			deck.c \
			player.c \
			play.c

OBJS	=	$(SRCS:.c=.o)

CARD_TEST_CFLAGS	=	-I/opt/local/include
CARD_TEST_LDFLAGS	=	-L/opt/local/lib -lcheck -L. -lholdem
CARD_TEST_SRCS		=	tests.c
CARD_TEST_OBJS		=	$(CARD_TEST_SRCS:.c=.o)
CARD_TEST_TARGET	=	tests

TARGET	=	libholdem.dylib


all: $(TARGET) $(CARD_TEST_TARGET)

.PHONY: clean

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CARD_TEST_CFLAGS) $(CFLAGS) -c $< -o $@


$(CARD_TEST_TARGET): $(TARGET) $(CARD_TEST_OBJS)
	$(CC) -o $(CARD_TEST_TARGET) $(CARD_TEST_OBJS) $(CARD_TEST_LDFLAGS)

clean:
	rm -fr $(TARGET) $(OBJS)
	rm -fr $(CARD_TEST_TARGET) $(CARD_TEST_OBJS)
