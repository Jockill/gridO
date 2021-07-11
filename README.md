# gridO
(WIP)
A curses based library to handle text based grid output
---

##Functions
 * gp_cell(x,y) : Prints a block to the x and y coordinates (grid based)
 * gp_line(y, start, length) : Prints a length long line on the y-axis \
  starting at start on the x-axis
 * gp_row(start, x, length) : Prints a length long row ont the x-axis \
 starting at start on the y-axis
 * gp_cellPrint(x, y, content) : Prints <content> to the (<x>,<y>) cell
 * gp_clearCell(x, y) : Clears the (<x>,<y>) cell 

---
##Notes
The anchor is on the top-left corner of the file.
