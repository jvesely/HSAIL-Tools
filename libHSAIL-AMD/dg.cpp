// University of Illinois/NCSA
// Open Source License
//
// Copyright (c) 2013-2015, Advanced Micro Devices, Inc.
// All rights reserved.
//
// Developed by:
//
//     HSA Team
//
//     Advanced Micro Devices, Inc
//
//     www.amd.com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal with
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
// of the Software, and to permit persons to whom the Software is furnished to do
// so, subject to the following conditions:
//
//     * Redistributions of source code must retain the above copyright notice,
//       this list of conditions and the following disclaimers.
//
//     * Redistributions in binary form must reproduce the above copyright notice,
//       this list of conditions and the following disclaimers in the
//       documentation and/or other materials provided with the distribution.
//
//     * Neither the names of the LLVM Team, University of Illinois at
//       Urbana-Champaign, nor the names of its contributors may be used to
//       endorse or promote products derived from this Software without specific
//       prior written permission.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
// CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS WITH THE
// SOFTWARE.

#include "Brig_amd.h"

#include "HSAILScanner.h"
#include "HSAILParser.h"
#include "HSAILItems.h"
#include "HSAILBrigantine.h"
#include "HSAILInstProps.h"
#include "HSAILGenericExtension.h"

#include "HSAILValidatorBase.h"

#include <sstream>

using namespace HSAIL_ASM;
using namespace HSAIL_PROPS;

using std::ostringstream;

namespace amd { namespace hsail { namespace dg {

//=============================================================================
//=============================================================================
//=============================================================================

#include "InstValidation_dg_gen.hpp"

//=============================================================================
//=============================================================================
//=============================================================================

const ExtInstDesc dgDescTab[] =
{
    {"amd_dg_groupstaticsize",      BRIG_OPCODE_AMD_DG_GROUPSTATICSIZE,      parseMnemoBasic,  -1},
    {"amd_dg_grouptotalsize",       BRIG_OPCODE_AMD_DG_GROUPTOTALSIZE,       parseMnemoBasic,  -1},
};

#define DG_DESC_SIZE (sizeof(dgDescTab) / sizeof(ExtInstDesc))

class DgExtension : public GenericExtension<amd::hsail::dg::InstValidator>
{
    //=============================================================================
    //=============================================================================
    //=============================================================================
public:

    virtual const char* getName() const
    {
        return AMD_DG_EXTENSION_NAME;
    }

    virtual bool isMnemoPrefix(const string& prefix) const
    {
        return (prefix == AMD_DG_EXTENSION_OPCODE_PREFIX);
    }

    //=============================================================================
    //=============================================================================
    //=============================================================================
protected:
    virtual const char*         getMnemoSuffix(const char* name) const { return name + strlen(AMD_DG_EXTENSION_OPCODE_PREFIX); }
    virtual const ExtInstDesc*  getInstDescByIdx(unsigned idx)   const { return dgDescTab + idx; }
    virtual       unsigned      getInstNum()                     const { return DG_DESC_SIZE; }
};

//=============================================================================
//=============================================================================
//=============================================================================

const Extension* getExtension()
{
  static const DgExtension dg;
  return &dg;
}

//=============================================================================
//=============================================================================
//=============================================================================

}}} // end of namespaces

