
#include "Manager.h"

int main() {
    Manager* manager = new Manager();
    manager->showMenu();
    delete(manager);
}
