/*
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   xrdp: A Remote Desktop Protocol server.
   Copyright (C) Jay Sorg 2005-2006

   session manager
   linux only
*/

/**
 *
 * @file tcp.c
 * @brief Tcp stream funcions
 * @author Jay Sorg
 * 
 */

#include "sesman.h"

/*****************************************************************************/
int DEFAULT_CC
tcp_force_recv(int sck, char* data, int len)
{
  int rcvd;

  while (len > 0)
  {
    rcvd = g_tcp_recv(sck, data, len, 0);
    if (rcvd == -1)
    {
      if (g_tcp_last_error_would_block(sck))
      {
        g_sleep(1);
      }
      else
      {
        return 1;
      }
    }
    else if (rcvd == 0)
    {
      return 1;
    }
    else
    {
      data += rcvd;
      len -= rcvd;
    }
  }
  return 0;
}

/*****************************************************************************/
int DEFAULT_CC
tcp_force_send(int sck, char* data, int len)
{
  int sent;

  while (len > 0)
  {
    sent = g_tcp_send(sck, data, len, 0);
    if (sent == -1)
    {
      if (g_tcp_last_error_would_block(sck))
      {
        g_sleep(1);
      }
      else
      {
        return 1;
      }
    }
    else if (sent == 0)
    {
      return 1;
    }
    else
    {
      data += sent;
      len -= sent;
    }
  }
  return 0;
}

