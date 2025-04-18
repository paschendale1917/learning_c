/*
 * hello_world
 * 
 * Copyright 2025 Professional <Professional@USER-PC>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>

char f0[][10]={"   *   \n","  ***  \n"," ***** \n","*******\n"," HHOHH \n"," ZZZZZ \n"};


int main(void)
{
	for(int i=0;i<6;i++){
		printf(*(f0+i));
	}

	return 0;
}

