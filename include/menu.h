#ifndef MENU_H
#define MENU_H

#include <menuview.h>
#include <menusettings.h>
#include <menumain.h>

typedef struct
{
	MenuView menuView;
	MenuMain menuMain;	
	MenuSettings menuSettings;
} MenuState;

void InitMenu(MenuState *m)
{
	m->menuView = MAIN;
	InitMenuSettings(&m->menuSettings);
	InitMenuMain(&m->menuMain);
}

void UpdateMenu(MenuState *m, State *state, Flags *flags)
{
	switch (m->menuView)
	{
		case MAIN:
		{
			UpdateMenuMain(&m->menuMain, state, flags, &m->menuView);
		}break;

		case SETTINGS:
		{
			UpdateMenuSettings(&m->menuSettings, &m->menuView,  flags);
		}break;
		default: break;
	}

}

void RenderMenu(MenuState *m, Font *font, const char *title, Flags *flags)
{
	switch (m->menuView)
	{
		case MAIN:
		{
			RenderMenuMain(&m->menuMain, font, title, flags);
		}break;

		case SETTINGS:
		{
			RenderMenuSettings(&m->menuSettings, flags);
		}
		default: break;
	} 
}

void CleanupMenu(MenuState *m)
{
	CleanupMenuMain(&m->menuMain);
}

#endif // MENU_H
