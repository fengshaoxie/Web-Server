#include "../httpcgiserver.h"
#include <signal.h>
#include <cassert>

const char * servIp = "127.0.0.1";
const int port = 9508;

void SignalHandler ( void )
{
    assert(signal(SIGPIPE, SIG_IGN) != SIG_ERR) ;
    assert(signal(SIGALRM, SIG_IGN) != SIG_ERR) ;
    assert(signal(SIGCHLD, SIG_IGN) != SIG_ERR) ;
}

int main()
{
	SignalHandler();
	HttpCgiServer cgiServer(servIp, port);
	cgiServer.Loop();
}