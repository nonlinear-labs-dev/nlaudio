/***
  Copyright (c) 2018 Nonlinear Labs GmbH

  Authors: Pascal Huerst <pascal.huerst@gmail.com>

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, see <http://www.gnu.org/licenses/>.
***/

#include <common/specialkeyboard.h>
#include <termios.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>

SpecialKeyboard::SpecialKeyboard()
{
	nonblock(true);
}

SpecialKeyboard::~SpecialKeyboard()
{
	nonblock(false);
}

char SpecialKeyboard::kbhit()
{
	struct timeval tv;
	fd_set fds;
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	FD_ZERO(&fds);
	FD_SET(STDIN_FILENO, &fds);
	select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);

	if (FD_ISSET(STDIN_FILENO, &fds)) {
		char ret;
		read(STDIN_FILENO, &ret, 1);
		return ret;
	}
	return 0;
}

void SpecialKeyboard::nonblock(bool enable)
{
	struct termios ttystate;

	//get the terminal state
	tcgetattr(STDIN_FILENO, &ttystate);

	if (enable) {
		//turn off canonical mode
		ttystate.c_lflag &= ~ICANON;
		//minimum of number input read.
		ttystate.c_cc[VMIN] = 1;
		//no echo
		ttystate.c_lflag &= ~ECHO;
	} else {
		ttystate.c_lflag |= ECHO;
		ttystate.c_lflag |= ICANON;
	}
	//set the terminal attributes.
	tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}
