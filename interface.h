#ifndef __INTERFACE_H_
#define __INTERFACE_H_

const int EXIT;
const int MAIN_MENU;
const int TEST_INTERFACE;

typedef struct _Interface_struct {
    char *name;
    int (*interface_fn)();
} Interface;
// typedef struct _Interface_struct Interface;

int test_interface();

int main_menu(); 

#endif // __INTERFACE_H_
