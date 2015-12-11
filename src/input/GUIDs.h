/*
========================================================================
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
#ifndef GUIDS_H
#define GUIDS_H
#include"./../elt_def.h"
#ifdef EX_WINDOWS
#include<Guiddef.h>
#ifdef __cplusplus
extern "C"{
#endif

DEFINE_GUID( GUID_Wceusbsh ,0x25dbce51,0x6c8f,0x4a72,0x8a,0x6d,0xb5,0x4c,0x2b,0x4f,0xc8,0x35);
DEFINE_GUID( GUID_UsbDevice,0x88BAE032,0x5A81,0x49f0,0xBC,0x3D,0xA4,0xFF,0x13,0x82,0x16,0xD6);

#ifdef __cplusplus
}
#endif
#endif
#endif
