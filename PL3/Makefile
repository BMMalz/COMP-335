CFLAGS=		-ansi

all:		tokenizer parser
tokenizer:	tokenizer.c
					gcc $(CFLAGS) tokenizer.c -o tokenize
parser:		parse.c
					gcc $(CFLAGS) parse.c -o parse
