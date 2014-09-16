//#include <Python.h>
#include "/usr/include/python2.7/Python.h"
#include <error.h>
#include <iwlib.h>
#include <linux/sockios.h>

#ifdef PYTHONCC
static PyObject* check_wifi(PyObject *self, PyObject *args)
{
    char* device;
    if (!PyArg_ParseTuple(args, "s", &device)) {
        return NULL;
    }
#else

static void check_wifi(char* device);
static void get_ap_addr(int skfd, char* device, wireless_info *info);
int main() {
    check_wifi("wlan0");
}


static void check_wifi(char* device)
{
#endif
    // open iw
    int skfd = iw_sockets_open();
    if (skfd < 0) {
        printf("failed opening iw socket\n");
        // XXX throw py exception
        //return NULL;
        return;
    }

    // alloc for wireless_info
    wireless_info info;
    memset((void*) &info, 0, sizeof(struct wireless_info));

    get_ap_addr(skfd, device, &info);

    // close
    iw_sockets_close(skfd);

    char* addr = malloc(sizeof(char)*14);
    iw_sawap_ntop(&info.ap_addr, addr);

    // returns 1 if we kicked, 0 otherwise
    printf("ADR?%s\n", addr);
    return;
}

static void get_ap_addr(int skfd, char* device, wireless_info *info) {

    // get ap addr
    struct iwreq wrq;
    if(iw_get_ext(skfd, device, SIOCGIWAP, &wrq) >= 0) {
        memcpy(&(info->ap_addr), &(wrq.u.ap_addr), sizeof (sockaddr));
    }
}

static int kick_wifi(char* dev)
{

    // make req
//    iw_get_basic_config(skfd, "wlan0", &info);
//    
//    // XXX check errno
//
//    // close
//    iw_sockets_close(skfd);
}
