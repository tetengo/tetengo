/*! \file
    \brief A timetable.

    Copyright (C) 2019-2020 kaoru  https://www.tetengo.org/
*/

#include "timetable.h"

#include <stdlib.h>


timetable_t* timetable_create()
{
    return NULL;
}

void timetable_destroy(const timetable_t* const p_timetable)
{
    free((void*)p_timetable);
}
