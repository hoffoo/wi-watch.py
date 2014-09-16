//#include <Python.h>
#include "/usr/include/python2.7/Python.h"
#include <error.h>
#include <linux/sockios.h>
#include <iwlib.h>

static PyObject* iw_info(PyObject *self, PyObject *args)
{
    char* device;
    if (!PyArg_ParseTuple(args, "s", &device)) {
        return NULL;
    }

    // alloc for wireless_info
    wireless_config info;
    memset((void*) &info, 0, sizeof(struct wireless_config));

    // open iw
    int skfd = iw_sockets_open();
    if (socket < 0) {
        printf("failed opening iw socket\n");
        return NULL;
    }

    // make req
    iw_get_basic_config(skfd, "wlan0", &info);

    // close
    iw_sockets_close(skfd);
}
