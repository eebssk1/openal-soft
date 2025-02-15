/**
 * OpenAL cross platform audio library
 * Copyright (C) 1999-2007 by authors.
 * This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 *  License along with this library; if not, write to the
 *  Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * Or go to http://www.gnu.org/copyleft/lgpl.html
 */

#include "config.h"

#include <cctype>
#include <cstdlib>
#include <cstring>

#include "AL/al.h"
#include "AL/alc.h"

#include "alc/context.h"
#include "alstring.h"
#include "core/except.h"
#include "opthelpers.h"


AL_API ALboolean AL_APIENTRY alIsExtensionPresent(const ALchar *extName)
START_API_FUNC
{
    ContextRef context{GetContextRef()};
    if(!context) UNLIKELY return AL_FALSE;

    if(!extName) UNLIKELY
    {
        context->setError(AL_INVALID_VALUE, "NULL pointer");
        return AL_FALSE;
    }

    size_t len{strlen(extName)};
    for(std::string_view ext : context->mExtensions)
    {
        if(len == ext.length() && al::strncasecmp(ext.data(), extName, len) == 0)
            return AL_TRUE;
    }

    return AL_FALSE;
}
END_API_FUNC


AL_API ALvoid* AL_APIENTRY alGetProcAddress(const ALchar *funcName)
START_API_FUNC
{
    if(!funcName) return nullptr;
    return alcGetProcAddress(nullptr, funcName);
}
END_API_FUNC

AL_API ALenum AL_APIENTRY alGetEnumValue(const ALchar *enumName)
START_API_FUNC
{
    if(!enumName) return static_cast<ALenum>(0);
    return alcGetEnumValue(nullptr, enumName);
}
END_API_FUNC
