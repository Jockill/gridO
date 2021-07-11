/*!
   \file gridO.h
   \brief A curses based library to handle text based grid output
   \author Jochymski Hugo
   \date 2021
*/
#include <curses.h>

//Cell apparence
#define CELL_CORNER "+" /*!< Cell corner apparence */
// (2y size recommended on default settings)
#define CELL_WIDTH 2 /*!< Cell x-edge size */
#define CELL_HEIGHT 1 /*!< Cell y-edge size */
#define CELL_SIZE (CELL_WIDTH*CELL_HEIGHT) /*!< Space within the cell */
#define CELL_XAXE "-" /*!< Cell x-axis edge apparence */
#define CELL_YAXE "|" /*!< Cell y-axis edge apparence */


/******************************************************************************/
/*********************************** UTILS ************************************/
/******************************************************************************/

/*!
   \brief Converts a y position on the grid to the real position on the file
   \param[in] y Y position to convert
   \return The converted position (integer)
*/
int yGridToReal(int y)
{
	if (y == 0) return 0;
	else return (y*CELL_HEIGHT + y);
}

/*!
   \brief Converts a x position on the grid to the real position on the file
   \param[in] x X position to convert
   \return The converted position (integer)
*/
int xGridToReal(int x)
{
	if (x == 0) return 0;
	else return (x*CELL_WIDTH + x);
}

/*!
   \brief Mimic the strlen function from string.h
   \param[in] str String to be examinated
   \return Length of \p str
*/
int strLen(char* str)
{
	int size = 0;
	while (str[size])
		size++;
	return size;
}

/******************************************************************************/
/********************************* BASIC GRID *********************************/
/******************************************************************************/


/*!
   \brief Prints a cell using the \p x and \p y grid coordinates
   \param [in] x X coordinate
   \param [in] y Y coordinate
   \return -1 on error, 0 on succes
*/
int gp_cell(int x, int y)
{
	if (x < 0 || y < 0)
		return -1;

	//Corners
	mvprintw(yGridToReal(y), xGridToReal(x), CELL_CORNER);
	mvprintw(yGridToReal(y), xGridToReal(x)+CELL_WIDTH+1, CELL_CORNER);
	mvprintw(yGridToReal(y)+CELL_HEIGHT+1, xGridToReal(x), CELL_CORNER);
	mvprintw(yGridToReal(y)+CELL_HEIGHT+1,
		 xGridToReal(x)+CELL_WIDTH+1, CELL_CORNER);

	//x-axis edges
	for (int i=0; i<CELL_WIDTH; i++)
	{
		//top
		mvprintw(yGridToReal(y), xGridToReal(x)+i+1, CELL_XAXE);
		//bot
		mvprintw(yGridToReal(y)+CELL_HEIGHT+1,
			 xGridToReal(x)+i+1, CELL_XAXE);
	}

	//y-axis edges
	for (int i=0; i<CELL_HEIGHT; i++)
	{
		//left
		mvprintw(yGridToReal(y)+i+1, xGridToReal(x), CELL_YAXE);
		//right
		mvprintw(yGridToReal(y)+i+1,
			 xGridToReal(x)+CELL_WIDTH+1, CELL_YAXE);

	}
	return 0;
}

/*!
   \brief Prints a \p length long line at the \p y coordinate starting at \
   \p start on the x-axis
   \param[in] start Starting point on the x-axis
   \param[in] y Y coordinate
   \param[in] len Line length
   \return -1 on error, 0 on succes
*/
int gp_line(int start, int y, int len)
{
	if (start < 0 || y < 0 || len < 0)
		return -1;

	for (int i=start; i<len; i++)
		gp_cell(i, y);
	return 0;
}

/*!
   \brief Prints a \p len long row at the \p x coordinate starting at \
   \p start on the y-axis
   \param[in] x X coordinate
   \param[in] start Starting point on the y-axis
   \param[in] len Row length
   \return -1 on error, 0 on succes
*/
int gp_row(int x, int start, int len)
{
	if (start < 0 || x < 0 || len < 0)
		return -1;

	for (int i=start; i<len; i++)
		gp_cell(x, i);
	return 0;
}


/******************************************************************************/
/****************************** CELL MANAGEMENT *******************************/
/******************************************************************************/

/*!
   \brief Prints \p content to a (\p x , \p y ) cell
   \param[in] x X coordinate
   \param[in] y Y coordinate
   \param[in] content What to be print
   \return -1 on error, 0 on succes
   \note \p content length has to be smaller or egal to CELL_SIZE \
   otherwhise it will be truncated
*/
int gp_cellPrint(int x, int y, char* content)
{
	if (x < 0 || y < 0 || content == NULL)
		return -1;

	int len = strLen(content);
	int istr = 0;

	for (int iy=yGridToReal(y)+1; iy<CELL_HEIGHT+yGridToReal(y)+1; iy++)
	{
		for (int ix=xGridToReal(x)+1; ix<CELL_WIDTH+xGridToReal(x)+1; ix++)
		{
			if (istr < len)
				mvprintw(iy, ix, "%c", content[istr++]);
		}
	}

	return 0;
}

/*!
   \brief Erases cell content
   \param[in] x X coordinate
   \param[in] y Y coordinate
   \return -1 on error, 0 on succes
*/
int gp_clearCell(int x, int y)
{
	if (x < 0 || y < 0)
		return -1;

	//Through x-axis
	for (int iy=yGridToReal(y)+1; iy<CELL_HEIGHT+yGridToReal(y)+1; iy++)
	{
		//Through y-axis
		for (int ix=xGridToReal(x)+1; ix<CELL_WIDTH+xGridToReal(x)+1; ix++)
		{
			mvprintw(iy, ix, " ");
		}
	}
	return 0;
}
