

#include "socket.h"

#include <stdio.h>

namespace agents {
namespace communication {

static std::uint16_t getInPort(struct sockaddr* sa) {
  if (sa->sa_family == AF_INET)
    return ntohs(((struct sockaddr_in*)sa)->sin_port);

  return ntohs(((struct sockaddr_in6*)sa)->sin6_port);
}

static int getSocketErrorCode() { return errno; }

static std::uint16_t getLocalPort(int socketHandler) {
  struct sockaddr_storage sin;
  socklen_t size;
  size = sizeof(sin);
  if (getsockname(socketHandler, (struct sockaddr*)&sin, &size) == 0)
    return getInPort((struct sockaddr*)&sin);
  else
    throw Exception(Exception::ERROR_GET_ADDR_INFO,
                    "Socket::(static)getLocalPort: error getting socket info",
                    getSocketErrorCode());
}

static void checkReadError(const string& functionName) {
  if (errno != EAGAIN && errno != EWOULDBLOCK)
    throw Exception(Exception::ERROR_READ,
                    string("Socket::") + functionName + ": error detected",
                    getSocketErrorCode());
}

void Socket::Initialize() {
  struct addrinfo conf, *res = NULL;
  memset(&conf, 0, sizeof(conf));

  if (_type == SERVER || _protocol == UDP) conf.ai_flags = AI_PASSIVE;

  switch (_protocol) {
    case TCP:
      conf.ai_socktype = SOCK_STREAM;
      break;

    case UDP:
      conf.ai_socktype = SOCK_DGRAM;
      break;

    default:
      throw Exception(Exception::BAD_PROTOCOL,
                      "Socket::initSocket: bad protocol");
  }

  switch (_ipVer) {
    case IP4:
      conf.ai_family = AF_INET;
      break;

    case IP6:
      conf.ai_family = AF_INET6;
      break;

    case ANY:
      conf.ai_family = AF_UNSPEC;
      break;

    default:
      throw Exception(Exception::BAD_IP_VER,
                      "Socket::initSocket: bad ip version parameter");
  }

  char portStr[10];

  const char* host;

  if (_type == CLIENT && _protocol == TCP) {
    host = _hostTo.c_str();
    snprintf(portStr, 10, "%u", _portTo);
  } else {
    if (!_hostFrom.compare("") || !_hostFrom.compare("*"))
      host = NULL;
    else
      host = _hostFrom.c_str();

    snprintf(portStr, 10, "%u", _portFrom);
  }

  int status = getaddrinfo(host, portStr, &conf, &res);
  if (status != 0) {
    string errorMsg = "Socket::initSocket: Error setting addrInfo: ";

    throw Exception(Exception::ERROR_SET_ADDR_INFO, errorMsg,
                    getSocketErrorCode());
  }

  ResourceManager addrInfoReleaser;
  addrInfoReleaser.AddAddress(res);

  bool connected = false;

  while (!connected && res) {
    _socketHandler = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    if (_socketHandler != -1) switch (_type) {
        case CLIENT:
          if (_protocol == UDP) {
            if (bind(_socketHandler, res->ai_addr, res->ai_addrlen) == -1)
              close(_socketHandler);
            else
              connected = true;
          } else {
            status = connect(_socketHandler, res->ai_addr, res->ai_addrlen);
            if (status != -1)
              connected = true;
            else
              close(_socketHandler);
          }

          break;

        case SERVER:
          int yes = 1;

          if (setsockopt(_socketHandler, SOL_SOCKET, SO_REUSEADDR, &yes,
                         sizeof(int)) == -1)
            throw Exception(
                Exception::ERROR_SET_SOCK_OPT,
                "Socket::initSocket: Error establishing socket options");

          if (bind(_socketHandler, res->ai_addr, res->ai_addrlen) == -1)
            close(_socketHandler);
          else
            connected = true;

          if (_protocol == TCP && listen(_socketHandler, _listenQueue) == -1)
            throw Exception(Exception::ERROR_CAN_NOT_LISTEN,
                            "Socket::initSocket: could not start listening",
                            getSocketErrorCode());

          break;
      }

    if (connected && _ipVer == ANY) switch (res->ai_family) {
        case AF_INET:
          _ipVer = IP4;
          break;

        case AF_INET6:
          _ipVer = IP6;
          break;
      }

    res = res->ai_next;
  }

  if (!connected)
    throw Exception(Exception::ERROR_CONNECT_SOCKET,
                    "Socket::initSocket: error in socket connection/bind",
                    getSocketErrorCode());

  if (!_portFrom) _portFrom = getLocalPort(_socketHandler);

  // freeaddrinfo(res);
}

Socket::Socket(const string& hostTo, std::uint16_t portTo, Protocol protocol,
               IPVer ipVer)
    : _hostTo(hostTo),
      _portTo(portTo),
      _portFrom(0),
      _protocol(protocol),
      _ipVer(ipVer),
      _type(CLIENT),
      _blocking(true),
      _listenQueue(0) {
  Initialize();
}

Socket::Socket(std::uint16_t portFrom, Protocol protocol, IPVer ipVer,
               const string& hostFrom, std::uint16_t listenQueue)
    : _hostFrom(hostFrom),
      _portTo(0),
      _portFrom(portFrom),
      _protocol(protocol),
      _ipVer(ipVer),
      _type(SERVER),
      _blocking(true),
      _listenQueue(listenQueue) {
  Initialize();
}

Socket::Socket(const string& hostTo, std::uint16_t portTo,
               std::uint16_t portFrom, IPVer ipVer)
    : _hostTo(hostTo),
      _portTo(portTo),
      _portFrom(portFrom),
      _protocol(UDP),
      _ipVer(ipVer),
      _type(CLIENT),
      _blocking(true),
      _listenQueue(0) {
  Initialize();
}

Socket::Socket() : _blocking(true), _socketHandler(-1) {}

Socket::~Socket() {
  if (_socketHandler != -1) close(_socketHandler);
}

static void* get_in_addr(struct sockaddr* sa) {
  if (sa->sa_family == AF_INET) {
    return &(((struct sockaddr_in*)sa)->sin_addr);
  }
  return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

Socket* Socket::accept() {
  if (_protocol != TCP)
    throw Exception(
        Exception::EXPECTED_TCP_SOCKET,
        "Socket::accept: non-tcp socket can not accept connections");

  if (_type != SERVER)
    throw Exception(
        Exception::EXPECTED_SERVER_SOCKET,
        "Socket::accept: non-server socket can not accept connections");

  struct sockaddr_storage incoming_addr;

  std::uint16_t addrSize = sizeof(incoming_addr);

  int new_handler =
      ::accept(_socketHandler, (struct sockaddr*)&incoming_addr, &addrSize);

  if (new_handler == -1) return NULL;

  char hostChar[INET6_ADDRSTRLEN];
  inet_ntop(incoming_addr.ss_family,
            get_in_addr((struct sockaddr*)&incoming_addr), hostChar,
            sizeof hostChar);

  Socket* acceptSocket = new Socket();
  acceptSocket->_socketHandler = new_handler;
  acceptSocket->_hostTo = hostChar;
  acceptSocket->_portTo = getInPort((struct sockaddr*)&incoming_addr);
  acceptSocket->_portFrom = getLocalPort(acceptSocket->_socketHandler);

  acceptSocket->_protocol = _protocol;
  acceptSocket->_ipVer = _ipVer;
  acceptSocket->_type = CLIENT;
  acceptSocket->_listenQueue = 0;
  acceptSocket->blocking(_blocking);

  return acceptSocket;
}

void Socket::sendTo(const void* buffer, size_t size, const string& hostTo,
                    std::uint16_t portTo) {
  if (_protocol != UDP)
    throw Exception(Exception::EXPECTED_UDP_SOCKET,
                    "Socket::sendTo: non-UDP socket can not 'sendTo'");

  struct addrinfo conf, *res;
  memset(&conf, 0, sizeof(conf));

  conf.ai_socktype = SOCK_DGRAM;

  switch (_ipVer) {
    case IP4:
      conf.ai_family = AF_INET;
      break;

    case IP6:
      conf.ai_family = AF_INET6;
      break;

    default:
      throw Exception(Exception::BAD_IP_VER, "Socket::sendTo: bad ip version.");
  }

  char portStr[10];
  snprintf(portStr, 10, "%u", portTo);

  int status = getaddrinfo(hostTo.c_str(), portStr, &conf, &res);

  ResourceManager addrInfoReleaser(freeaddrinfo);
  addrInfoReleaser.AddAddress(&res);

  if (status != 0) {
    string errorMsg = "Socket::sendTo: error setting addrInfo: ";
#ifndef _MSC_VER
    errorMsg += gai_strerror(status);
#endif
    throw Exception(Exception::ERROR_SET_ADDR_INFO,
                    "Socket::sendTo: error setting addr info",
                    getSocketErrorCode());
  }

  size_t sentBytes = 0;

  while (sentBytes < size) {
    int status = ::sendto(_socketHandler, (const char*)buffer + sentBytes,
                          size - sentBytes, 0, res->ai_addr, res->ai_addrlen);

    if (status == -1)
      throw Exception(Exception::ERROR_SEND,
                      "Socket::sendTo: could not send the data",
                      getSocketErrorCode());

    sentBytes += status;
  }
}

int Socket::readFrom(void* buffer, size_t bufferSize, string* hostFrom,
                     std::uint16_t* portFrom) {
  if (_protocol != UDP)
    throw Exception(Exception::EXPECTED_UDP_SOCKET,
                    "Socket::readFrom: non-UDP socket can not 'readFrom'");

  struct sockaddr_storage addr;
  socklen_t addrSize = sizeof(addr);
  int status = recvfrom(_socketHandler, (char*)buffer, bufferSize, 0,
                        (struct sockaddr*)&addr, &addrSize);

  if (status == -1) {
    checkReadError("readFrom");
    if (hostFrom) *hostFrom = "";
    if (portFrom) *portFrom = 0;
  }

  else {
    if (portFrom) *portFrom = getInPort((struct sockaddr*)&addr);

    if (hostFrom) {
      char hostChar[INET6_ADDRSTRLEN];
      inet_ntop(addr.ss_family, get_in_addr((struct sockaddr*)&addr), hostChar,
                sizeof hostChar);

      *hostFrom = hostChar;
    }
  }

  return status;
}

void Socket::send(const void* buffer, size_t size) {
  if (_type != CLIENT)
    throw Exception(Exception::EXPECTED_CLIENT_SOCKET,
                    "Socket::send: Expected client socket (socket with host "
                    "and port target)");

  if (_protocol == UDP) return sendTo(buffer, size, _hostTo, _portTo);

  size_t sentData = 0;

  while (sentData < size) {
    int status = ::send(_socketHandler, (const char*)buffer + sentData,
                        size - sentData, 0);

    if (status == -1)
      throw Exception(Exception::ERROR_SEND, "Error sending data",
                      getSocketErrorCode());

    sentData += status;
  }
}

int Socket::read(void* buffer, size_t bufferSize) {
  int status = recv(_socketHandler, (char*)buffer, bufferSize, 0);

  if (status == -1) checkReadError("read");

  return status;
}

int Socket::nextReadSize() const {
  long int result = -1;
  int status;
  status = ioctl(_socketHandler, FIONREAD, &result);

  if (status)
    throw Exception(Exception::ERROR_IOCTL, "Socket::nextReadSize: error ioctl",
                    getSocketErrorCode());

  return result;
}

void Socket::blocking(bool blocking) {
  _blocking = blocking;

  int result = -1;

  int flags = fcntl(_socketHandler, F_GETFL);

  if (blocking)
    result = fcntl(_socketHandler, F_SETFL, flags & ~O_NONBLOCK);
  else
    result = fcntl(_socketHandler, F_SETFL, flags | O_NONBLOCK);

  if (result == -1)
    throw Exception(Exception::ERROR_IOCTL, "Socket::blocking: ioctl error",
                    getSocketErrorCode());
}

void Socket::disconnect() {
  close(_socketHandler);

  _socketHandler = -1;
}
}  // namespace communication
}  // namespace agents