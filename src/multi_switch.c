
#include "button.h"
#include "multi_switch.h"

void multi_switch_Initialise(multi_switch_t* multi_switch) {
    button_Initialise(&multi_switch->up);
    button_Initialise(&multi_switch->right);
    button_Initialise(&multi_switch->down);
    button_Initialise(&multi_switch->left);
    button_Initialise(&multi_switch->push);
}