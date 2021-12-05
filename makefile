LIB=-L
INC=-I./ext_libs/netLink-v1.0.0/netlink/include
CLIENT_INCLUDE=-I./agent_client/ -I./communication/ -I./interface/ -I./logic/ -I./utils/
SERVER_INCLUDE=-I./agent_server/ -I./communication/ -I./interface/ -I./logic/ -I./utils/
CLIENT_BIN=./agent_client/main.cpp
SERVER_BIN=./agent_server/main.cpp

default: client

client: $(CLIENT_BIN)
        gcc -Wall $(LIB) $(INC) $(CLIENT_INCLUDE) -c $(CLIENT_BIN)

server: $(SERVER_BIN)
        gcc -Wall $(LIB) $(INC) $(SERVER_INCLUDE) -c $(SERVER_BIN)

clean:
        rm -r *.o