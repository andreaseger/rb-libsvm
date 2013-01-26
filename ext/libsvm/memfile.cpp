#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memfile.h"

ssize_t
memfile_write(void *c, const char *buf, size_t size)
{
  char *new_buff;
  struct memfile_cookie *cookie = (struct memfile_cookie *) c;

   /* Buffer too small? Keep doubling size until big enough */

  while (size + cookie->offset > cookie->allocated) {
    new_buff = (char*) realloc(cookie->buf, cookie->allocated * 2);
    if (new_buff == NULL) {
      return -1;
    } else {
      cookie->allocated *= 2;
      cookie->buf = new_buff;
    }
  }

  memcpy(cookie->buf + cookie->offset, buf, size);

  cookie->offset += size;
  if (cookie->offset > cookie->endpos)
    cookie->endpos = cookie->offset;

  return size;
}

ssize_t
memfile_read(void *c, char *buf, size_t size)
{
  ssize_t xbytes;
  struct memfile_cookie *cookie = (struct memfile_cookie *) c;

   /* Fetch minimum of bytes requested and bytes available */

  xbytes = size;
  if (cookie->offset + size > cookie->endpos)
    xbytes = cookie->endpos - cookie->offset;
   if (xbytes < 0)     /* offset may be past endpos */
  xbytes = 0;

  memcpy(buf, cookie->buf + cookie->offset, xbytes);

  cookie->offset += xbytes;
  return xbytes;
}

int
memfile_seek(void *c, off64_t *offset, int whence)
{
  off64_t new_offset;
  struct memfile_cookie *cookie = (struct memfile_cookie *) c;

  if (whence == SEEK_SET)
    new_offset = *offset;
  else if (whence == SEEK_END)
    new_offset = cookie->endpos + *offset;
  else if (whence == SEEK_CUR)
    new_offset = cookie->offset + *offset;
  else
    return -1;

  if (new_offset < 0)
    return -1;

  cookie->offset = new_offset;
  *offset = new_offset;
  return 0;
}

int
memfile_close(void *c)
{
  struct memfile_cookie *cookie = (struct memfile_cookie *) c;

  free(cookie->buf);
  cookie->allocated = 0;
  cookie->buf = NULL;

  return 0;
}

cookie_io_functions_t memfile_func()
{
	cookie_io_functions_t  tmp;
	tmp.read  = memfile_read;
	tmp.write = memfile_write;
	tmp.seek  = memfile_seek;
	tmp.close = memfile_close;

  return tmp;
}
