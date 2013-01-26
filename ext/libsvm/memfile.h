#ifndef _MEMFILE_H
#define _MEMFILE_H


#ifdef __cplusplus
extern "C" {
#endif

#define INIT_BUF_SIZE 4

struct memfile_cookie {
   char   *buf;        /* Dynamically sized buffer for data */
   size_t  allocated;  /* Size of buf */
   size_t  endpos;     /* Number of characters in buf */
   off_t   offset;     /* Current file offset in buf */
};

ssize_t memfile_write(void *c, const char *buf, size_t size);
ssize_t memfile_read(void *c, char *buf, size_t size);
int memfile_seek(void *c, off64_t *offset, int whence);
int memfile_close(void *c);
cookie_io_functions_t memfile_func();

#ifdef __cplusplus
}
#endif

#endif /* _MEMFILE_H */
