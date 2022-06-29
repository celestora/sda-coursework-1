#include "Menu.h"
#include "getch.h"

struct MenuEntry* menu_entry_new(char* name, MenuEntryHandler hand) {
    struct MenuEntry* menu = malloc(sizeof(struct MenuEntry));
    menu->name = name;
    menu->hand = hand;

    return menu;
}

struct TextMenu* menu_new(struct MenuEntry** entries, unsigned int count) {
    struct TextMenu* menu = malloc(sizeof(struct TextMenu));
    menu->currentIndex = 0;
    menu->willExit     = false;
    menu->doneBy       = "KV-14 Oleksandr Briukhanov";
    menu->menuEntries  = entries;
    menu->entryCount   = count;

    return menu;
}

bool menu_handler_exit() {
    return false;
}

void priv_menu_execute_current_action(struct TextMenu* menu) {
    struct MenuEntry* entry = menu->menuEntries[menu->currentIndex];

    system("clear");
    menu->willExit = !(entry->hand)();
    printf("\a\n");
}

void priv_menu_print_view(struct TextMenu* menu) {
    system("clear");
    printf("Coursework done by: %s\n\n", menu->doneBy);
    for(int i = 0; i < menu->entryCount; i++)
        printf("%c %s\n", i == menu->currentIndex ? '>' : ' ', menu->menuEntries[i]->name);

    printf("Coursework done by: %s\n\n", menu->doneBy);
}

int menu_start(struct TextMenu* menu) {
    while(!menu->willExit) {
        priv_menu_print_view(menu);

        switch(getch()) {
            case '\n':
            case '\r':
                priv_menu_execute_current_action(menu);
                break;

            case '[': ;
                int arrow = getch();
                if(arrow == 'A') {
                    menu->currentIndex--;
                    if(menu->currentIndex >= menu->entryCount) // overflow
                        menu->currentIndex = menu->entryCount - 1;
                } else if(arrow == 'B') {
                    menu->currentIndex++;
                    if(menu->currentIndex >= menu->entryCount)
                        menu->currentIndex = 0;
                }
                break;
        }
    }

    return 0;
}
