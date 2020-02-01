/*
 * Copyright (C) 2015 Sergii Pylypenko
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _XSDL_INPUT_H_
#define _XSDL_INPUT_H_

#include <SDL/SDL.h>
#include <map>
#include <set>

enum KeyCode
{
	MAX_MODIFIERS = 8,
	KEY_LCTRL     = 224, // scancode inside scancodes.c
	KEY_LSHIFT    = 225,
	KEY_LALT      = 226,
	KEY_LSUPER    = 227,
	KEY_RCTRL     = 228,
	KEY_RSHIFT    = 229,
	KEY_RALT      = 230,
	KEY_RSUPER    = 231,
	MAX_KEYCODES  = KEY_RSUPER + 1,
};

extern bool keys[MAX_KEYCODES];
extern float mouseCoords[2];
extern bool mouseButtons[SDL_BUTTON_X2+1];
extern std::map<int, int> keyMappings;
extern std::set<int> keyMappingsShift, keyMappingsCtrl, keyMappingsAlt;

void openInput();
bool processKeyInput(SDLKey key, unsigned int unicode, bool pressed);
bool processKeyInput(SDLKey key, unsigned int unicode, bool pressed);
void processMouseInput();
void queueKeyTextString(const char *s);
int processQueuedKeyTextString();

void saveKeyMappings();

#endif
