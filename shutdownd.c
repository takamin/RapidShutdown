#include <stdlib.h>
#include <syslog.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include "wiringPi.h"

#define GPIO_SHUTDOWN_BUTTON 25

static volatile int sigterm = 0;
static volatile int sigint = 0;
static volatile int sighup = 0;
static volatile int shutdown = 0;

static void handle_sigint(int sig)
{
    dlog(LOG_INFO, "SIGINT received.\n");
    sigint = 1;
}
static void handle_sigterm(int sig)
{
    dlog(LOG_INFO, "SIGTERM received.\n");
    sigterm = 1;
}
static void handle_sighup(int sig)
{
    dlog(LOG_INFO, "SIGHUP received.\n");
    sighup = 1;
}

int daemon_main(int argc, char* argv[], char* envp[])
{
    int shutdown = 0;
    dlog(LOG_INFO, "shutdownd started.\n");
    if (signal(SIGINT, handle_sigint) == SIG_ERR) {
        dlog(LOG_ERR, "fail to setup SIGINT.\n");
        return 2;
    } else
    if (signal(SIGTERM, handle_sigterm) == SIG_ERR) {
        dlog(LOG_ERR, "fail to setup SIGTERM.\n");
        return 2;
    } else if (signal(SIGHUP, handle_sighup) == SIG_ERR) {
        dlog(LOG_ERR, "fail to ignore SIGHUP.\n");
        return 2;
    }
    wiringPiSetupGpio();
    pinMode(GPIO_SHUTDOWN_BUTTON, INPUT);
    pullUpDnControl(GPIO_SHUTDOWN_BUTTON, PUD_UP);
    while(!sigterm && !sigint) {
        if(shutdown) {
            usleep(1000000);
        } else {
            int button_state = digitalRead(GPIO_SHUTDOWN_BUTTON);
            int button_pushed = (button_state == LOW ? 1 : 0);
            if(button_pushed) {
                shutdown = 1;
                syslog(LOG_INFO, "shutdownd is going to shutdown the system.");
                system("shutdown -h now");
            }
            usleep(10000);
        }
    }
    dlog(LOG_INFO, "shutdownd stopped.\n");
    return 0;
}
