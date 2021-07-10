/*!
   \file gridO.h
   \brief A curses based library to handle text based grid output
   \author Jochymski Hugo
   \date 2021
*/
#include <curses.h>

//Block apparence
#define BLOCK_CORNER "+" /*!< Block corner apparence */
// (2y size recommended on default settings)
#define BLOCK_SIZE_X 2 /*!< Block x-edge size */
#define BLOCK_SIZE_Y 1 /*!< Block y-edge size */
#define BLOCK_XAXE "-" /*!< Block x-axis edge apparence */
#define BLOCK_YAXE "|" /*!< Block y-axis edge apparence */

/*!
   \brief Converts a y position on the grid to the real position on the file
   \param[in] y Y position to convert
   \return The converted position (integer) or -1 on error
   \note Possible errors : \p y < 0
*/
int yGridToReal(int y)
{
	if (y < 0) return -1;
	else if (y == 0) return 0;
	else return (y*BLOCK_SIZE_Y + y);
}

/*!
   \brief Converts a x position on the grid to the real position on the file
   \param[in] x X position to convert
   \return The converted position (integer) or -1 on error
   \note Possible errors : \p x < 0
*/
int xGridToReal(int x)
{
	if (x < 0) return -1;
	else if (x == 0) return 0;
	else return (x*BLOCK_SIZE_X + x);
}

/*!
   \brief Prints a block using the \p x and \p y grid coordinates
   \param [in] x X coordinate
   \param [in] y Y coordinate
*/
void gp_block(int x, int y)
{
	//Corners
	mvprintw(yGridToReal(y), xGridToReal(x), BLOCK_CORNER);
	mvprintw(yGridToReal(y), xGridToReal(x)+BLOCK_SIZE_X+1, BLOCK_CORNER);
	mvprintw(yGridToReal(y)+BLOCK_SIZE_Y+1, xGridToReal(x), BLOCK_CORNER);
	mvprintw(yGridToReal(y)+BLOCK_SIZE_Y+1,
		 xGridToReal(x)+BLOCK_SIZE_X+1, BLOCK_CORNER);

	//x-axis edges
	for (int i=0; i<BLOCK_SIZE_X; i++)
	{
		//top
		mvprintw(yGridToReal(y), xGridToReal(x)+i+1, BLOCK_XAXE);
		//bot
		mvprintw(yGridToReal(y)+BLOCK_SIZE_Y+1,
			 xGridToReal(x)+i+1, BLOCK_XAXE);
	}

	//y-axis edges
	for (int i=0; i<BLOCK_SIZE_Y; i++)
	{
		//left
		mvprintw(yGridToReal(y)+i+1, xGridToReal(x), BLOCK_YAXE);
		//right
		mvprintw(yGridToReal(y)+i+1,
			 xGridToReal(x)+BLOCK_SIZE_X+1, BLOCK_YAXE);

	}
}

/*!
   \brief Prints a \p length long line at the \p y coordinate starting at \
   \p start on the x-axis
   \param[in] start Starting point on the x-axis
   \param[in] y Y coordinate
   \param[in] length Line length
*/
void gp_line(int start, int y, int length)
{
	for (int i=start; i<length; i++)
		gp_block(i, y);
}

/*!
   \brief Prints a \p length long row at the \p x coordinate starting at \
   \p start on the y-axis
   \param[in] x X coordinate
   \param[in] start Starting point on the y-axis
   \param[in] length Row length
*/
void gp_row(int x, int start, int length)
{
	for (int i=start; i<length; i++)
		gp_block(x, i);
}
