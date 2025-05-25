/*! \file embroidery.S
 * \brief Macro library for embroidery on embedded systems.
 * \warning Do not use this if the main libembroidery compiles and runs on
 *          your system. It is for very small memory environments (<100kb).
 *
 * Libembroidery 1.0.0-alpha
 * https://www.libembroidery.org
 *
 * A library for reading, writing, altering and otherwise
 * processing machine embroidery files and designs.
 *
 * Also, the core library supporting the Embroidermodder Project's
 * family of machine embroidery interfaces.
 *
 *
 * -----------------------------------------------------------------------------
 *
 * Copyright 2018-2025 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 *
 * -----------------------------------------------------------------------------
 *
 * Note that all new defines start with "EMB_", all functions with "emb" and all
 * typedefs with "Emb" to protect against namespace pollution. (INCOMPLETE)
 */

#define EMB_EMBEDDED_MODE__ 1
#include "../src/embroidery.h"

.macro	zfill size
.zero	\size
.endm

#include "compress.S"
#include "data.S"
#include "designs.S"
#include "formats.S"
#include "geometry.S"
#include "pattern.S"
#include "script.S"
#include "testing.S"

