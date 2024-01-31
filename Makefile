CLIENT_NAME = client
SERVER_NAME = server

CLIENT_NAME_BONUS = client_bonus
SERVER_NAME_BONUS = server_bonus

CC = cc
RMF = rm -f

CFLAGS = -Wall -Wextra -Werror
DFLAGS = -MMD -MP

HDIR	=	includes
SDIR	=	srcs
BDIR	=	build
DDIR	=	build

CLIENT_DIR = client
CLIENT_FILES = client_sig.c
CLIENT_FILES += client.c

CLIENT_PATH = ${addprefix $(CLIENT_DIR)/, $(CLIENT_FILES)}
CLIENT_SRCS = ${addprefix $(SDIR)/, $(CLIENT_PATH)}
CLIENT_OBJS = $(CLIENT_PATH:%.c=$(BDIR)/%.o)
CLIENT_DEPS = $(CLIENT_PATH:%.c=$(DDIR)/%.d)

SERVER_DIR = server
SERVER_FILES = server.c
SERVER_FILES += server_utils.c
SERVER_FILES += server_sig.c

SERVER_PATH = ${addprefix $(SERVER_DIR)/, $(SERVER_FILES)}
SERVER_SRCS = ${addprefix $(SDIR)/, $(SERVER_PATH)}
SERVER_OBJS = $(SERVER_PATH:%.c=$(BDIR)/%.o)
SERVER_DEPS = $(SERVER_PATH:%.c=$(DDIR)/%.d)

all : $(CLIENT_NAME) $(SERVER_NAME)

bonus: $(CLIENT_NAME_BONUS) $(SERVER_NAME_BONUS)

$(CLIENT_NAME_BONUS) : $(CLIENT_OBJS)
	$(CC) $(CFLAGS) -o $@ $(CLIENT_OBJS) -I $(HDIR)/

$(SERVER_NAME_BONUS) : $(SERVER_OBJS)
	$(CC) $(CFLAGS) -o $@ $(SERVER_OBJS) -I $(HDIR)/

$(CLIENT_NAME) : $(CLIENT_OBJS)
	$(CC) $(CFLAGS) -o $@ $(CLIENT_OBJS) -I $(HDIR)/

$(SERVER_NAME) : $(SERVER_OBJS)
	$(CC) $(CFLAGS) -o $@ $(SERVER_OBJS) -I $(HDIR)/

-include $(CLIENT_DEPS) $(SERVER_DEPS)

$(BDIR)/%.o	:	$(SDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@ -I $(HDIR)/

fclean	:	clean
	rm -f $(SERVER_NAME) $(CLIENT_NAME) $(CLIENT_NAME_BONUS) $(SERVER_NAME_BONUS)

clean:
	rm -f $(CLIENT_OBJS) $(SERVER_OBJS) $(SERVER_DEPS) $(CLIENT_DEPS)

re		:	fclean
	@$(MAKE) all

.PHONY	:	all\
			fclean\
			clean\
			re\
			bonus