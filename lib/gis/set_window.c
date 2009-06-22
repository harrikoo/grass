/*!
 * \file gis/set_window.c
 *
 * \brief GIS Library - Set window (map region)
 *
 * (C) 2001-2009 by the GRASS Development Team
 *
 * This program is free software under the GNU General Public License
 * (>=v2). Read the file COPYING that comes with GRASS for details.
 *
 * \author Original author CERL
 */

#include <grass/gis.h>
#include <grass/glocale.h>

#include "G.h"

/*!
 * \brief Get the current working window (region)
 *
 * The current working window values are returned in the structure
 * <i>window</i>.
 *
 * \param[in,out] window window structure to be set
 */
void G_get_set_window(struct Cell_head *window)
{
    G__init_window();
    G_copy(window, &G__.window, sizeof(*window));
}

/*!
 * \brief Establishes 'window' as the current working window.
 * 
 * \param window window to become operative window
 * 
 * \return -1 on error
 * \return  1 on success
 */
int G_set_window(struct Cell_head *window)
{
    const char *err;

    /* adjust window, check for valid window */
    /* adjust the real one, not a copy
       G_copy (&twindow, window, sizeof(struct Cell_head));
       window = &twindow;
     */

    if ((err = G_adjust_Cell_head(window, 0, 0))) {
	G_warning("G_set_window(): %s", err);
	return -1;
    }

    /* copy the window to the current window */
    G_copy((char *)&G__.window, (char *)window, sizeof(*window));

    G__.window_set = 1;

    return 1;
}
