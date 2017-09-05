#pragma once

#include "googleTile.h"
#include "util\common\us_string.hpp"
#include "metadata\us_basic_uv.hpp"
#include "data_process\us_data_process_operator.hpp"
#include "util\filesys\us_filesystem.hpp"
#include "metadata\us_image_basic_meta.hpp"
#include <direct.h>
#include "data_process\us_image_read_data.hpp"
#include <fstream>
#include "us_thread.h"
bool googleTile_segment(char *srcDr, int level_start, int level_end, char *destDrec, int thread_num = 100);

