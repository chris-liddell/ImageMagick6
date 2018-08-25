/*
  Copyright 1999-2018 ImageMagick Studio LLC, a non-profit organization
  dedicated to making software imaging solutions freely available.
  
  You may not use this file except in compliance with the License.
  obtain a copy of the License at
  
    https://www.imagemagick.org/script/license.php
  
  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  MagickCore image coder methods.
*/
#ifndef MAGICKCORE_CODER_H
#define MAGICKCORE_CODER_H

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

#include "magick/exception-private.h"
#include "magick/policy.h"

typedef struct _CoderInfo
{
  char
    *path,
    *magick,
    *name;
                                                                                
  MagickBooleanType
    exempt,
    stealth;
                                                                                
  struct _CoderInfo
    *previous,
    *next;  /* deprecated, use GetCoderInfoList() */

  size_t
    signature;
} CoderInfo;

extern MagickExport char
  **GetCoderList(const char *,size_t *,ExceptionInfo *);

extern MagickExport const CoderInfo
  *GetCoderInfo(const char *,ExceptionInfo *),
  **GetCoderInfoList(const char *,size_t *,ExceptionInfo *);

extern MagickExport MagickBooleanType
  CoderComponentGenesis(void),
  ListCoderInfo(FILE *,ExceptionInfo *);

MagickExport void
  CoderComponentTerminus(void);

static inline MagickBooleanType IsCoderAuthorized(const char *module,
  const char *coder,const PolicyRights rights,ExceptionInfo *exception)
{
  if ((IsRightsAuthorized(ModulePolicyDomain,rights,module) == MagickFalse) ||
      (IsRightsAuthorized(CoderPolicyDomain,rights,coder) == MagickFalse))
    {
      errno=EPERM;
      (void) ThrowMagickException(exception,GetMagickModule(),PolicyError,
        "NotAuthorized","`%s:%s'",module,coder);
      return(MagickFalse);
    }
  return(MagickTrue);
}

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
