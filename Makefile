CC		=	gcc
CFLAGS	=	-Wall -Werror -ggdb
LDFLAGS	=	-shared

SRCS	=	card.c init.c
OBJS	=	$(SRCS:.c=.o)

CARD_TEST_LDFLAGS	=	-L. -lholdem
CARD_TEST_SRCS		=	card_test.c
CARD_TEST_OBJS		=	$(CARD_TEST_SRCS:.c=.o)
CARD_TEST_TARGET	=	card_test

TARGET	=	libholdem.so


all: $(TARGET)

.PHONY: clean

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


$(CARD_TEST_TARGET): $(CARD_TEST_OBJS)
	$(CC) -o $(CARD_TEST_TARGET) $(CARD_TEST_OBJS) $(CARD_TEST_LDFLAGS)

clean:
	rm -fr $(TARGET) $(OBJS)
	rm -fr $(CARD_TEST_TARGET) $(CARD_TEST_OBJS)
