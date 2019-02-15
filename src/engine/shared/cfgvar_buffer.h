/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
/* Modifications Copyright 2019 The InfclassR (https://github.com/yavl/teeworlds-infclassR/) Authors */

#ifndef ENGINE_SHARED_CFGVAR_BUFFER_H
#define ENGINE_SHARED_CFGVAR_BUFFER_H

#include <base/system.h>
#include "console.h"

class CCfgVarBuffer
{

	enum
	{
		CFG_TYPE_INT = 0,
		CFG_TYPE_STR = 1
	};

	struct CfgVar
	{
		int m_Type;
		char *m_pScriptName;
		int m_ScriptNameLength;
		int *m_pIntValue;
		char *m_pStrValue;
	};

public:
	static void Init();
	static void ConPrintCfg(CConsole* pConsole, const char *pCfgName);
	static bool IsConfigVar(const char* pStr);

private:
	static CfgVar *m_CfgVars;
	static int m_CfgVarsCounter;

};


#endif
