#ifndef COURSEWORK_MENU_H
#define COURSEWORK_MENU_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MENU_HANDLER(name) bool name(void)

typedef bool (*MenuEntryHandler)(void);

struct MenuEntry {
    char* name;
    MenuEntryHandler hand;
};

struct MenuEntry* menu_entry_new(char* name, MenuEntryHandler hand);
bool menu_handler_exit();

struct TextMenu {
    struct MenuEntry** menuEntries;
    unsigned int entryCount;
    unsigned int currentIndex;

    bool willExit;
    char* doneBy;
};

struct TextMenu* menu_new(struct MenuEntry** entries, unsigned int count);
int menu_start(struct TextMenu* menu);

#endif //COURSEWORK_MENU_H
