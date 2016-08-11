/**
    ELT (Engine Library Toolkit) is a multi platform engine toolkit
    Copyright (C) 2014  Valdemar Lindberg

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _ELT_CLIP_BOARD_H_
#define _ELT_CLIP_BOARD_H_ 1
#include"../system.h"
#include"ExNT.h"

/**
 *	Set clipboard text.
 *
 *	@Return
 */
extern ELTDECLSPEC Int32 ELTAPIENTRY ExSetClipboardText(const ExChar* text);

/**
 *	Set clipboard data.
 *
 *	@Return
 */
extern ELTDECLSPEC Int32 ELTAPIENTRY ExSetClipboardData(void* pdata,Uint32 csize);

/**
 *	Get clipboard text.
 *
 *	@Return
 */
extern ELTDECLSPEC ExChar* ELTAPIENTRY ExGetClipboardText(void);

/**
 *	Get clipboard data.
 *
 *	@Return
 */
extern ELTDECLSPEC Int32 ELTAPIENTRY ExGetClipboardData(void* pdata);

/**
 *
 *
 *	@Return
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExHasClipboard(void);


#endif
