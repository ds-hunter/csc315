#ifndef DEFINES_H
#define DEFINES_H

#define validRow(r) (r >= 0 && r < height)
#define validCol(c) (c >= 0 && c < width)

#define canEnter(c,r) (validRow(r) && validCol(c) && \
                      (grid[(r)*width+c] != -1))

#endif
