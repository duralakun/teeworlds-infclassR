/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
/* Modifications Copyright 2019 The InfclassR (https://github.com/yavl/teeworlds-infclassR/) Authors */

#include <base/system.h>
#include "cfgvar_buffer.h"
#include "config.h"
#include "console.h"
#include <iostream>

int CCfgVarBuffer::m_CfgVarsCounter;
CCfgVarBuffer::CfgVar *CCfgVarBuffer::m_CfgVars;

void CCfgVarBuffer::Init()
{
	m_CfgVarsCounter = 0;

	// Count how many config variables there are
	#define MACRO_CONFIG_INT(Name,ScriptName,Def,Min,Max,Flags,Desc) \
	{ \
		m_CfgVarsCounter++; \
	}

	#define MACRO_CONFIG_STR(Name,ScriptName,Len,Def,Flags,Desc) \
	{ \
		m_CfgVarsCounter++; \
	}

	#include "config_variables.h"
	#include "game/variables.h"

	#undef MACRO_CONFIG_INT
	#undef MACRO_CONFIG_STR

	m_CfgVars = new CfgVar[m_CfgVarsCounter];
	int tCount = 0;

	// read all config variables and save their information to m_CfgVars
	#define MACRO_CFGVAR_SAVE_NAME(ScriptName) \
	{ \
		int i = 0; \
		for ( ; i < 256; i++) \
			if (#ScriptName[i] == 0) break; \
		i++; \
		m_CfgVars[tCount].m_pScriptName = new char[i]; \
		m_CfgVars[tCount].m_ScriptNameLength = i; \
		std::cout << "JDBG " << #ScriptName << " i: " << i << "\n"; \
		str_copy(m_CfgVars[tCount].m_pScriptName, #ScriptName, i); \
		m_CfgVars[tCount].m_pScriptName[i-1] = 0; \
	}

	#define MACRO_CONFIG_INT(Name,ScriptName,Def,Min,Max,Flags,Desc) \
	{ \
		m_CfgVars[tCount].m_Type = CFG_TYPE_INT; \
		m_CfgVars[tCount].m_pIntValue = &g_Config.m_##Name; \
		MACRO_CFGVAR_SAVE_NAME(ScriptName); \
		tCount++; \
	} 

	#define MACRO_CONFIG_STR(Name,ScriptName,Len,Def,Flags,Desc) \
	{ \
		m_CfgVars[tCount].m_Type = CFG_TYPE_STR; \
		m_CfgVars[tCount].m_pStrValue = g_Config.m_##Name; \
		MACRO_CFGVAR_SAVE_NAME(ScriptName); \
		tCount++; \
	}

	#include "config_variables.h"
	#include "game/variables.h"

	#undef MACRO_CONFIG_INT
	#undef MACRO_CONFIG_STR
}


void CCfgVarBuffer::ConPrintCfg(CConsole* pConsole, const char *pCfgName)
{
	if (*pCfgName == 0) 
	{
		// print all config variables and their values
		for (int i = 0; i < m_CfgVarsCounter; i++)
		{
			char lineBuff[512];
			if (m_CfgVars[i].m_Type == CFG_TYPE_INT)
				str_format(lineBuff, 512, "%s %i", m_CfgVars[i].m_pScriptName, *m_CfgVars[i].m_pIntValue);
			else
				str_format(lineBuff, 512, "%s %s", m_CfgVars[i].m_pScriptName, m_CfgVars[i].m_pStrValue);
			pConsole->Print(IConsole::OUTPUT_LEVEL_STANDARD, "Console", lineBuff);
		}
		return;
	}

	// search for config vars that contain pCfgName and print them and their values
	for (int i = 0; i < m_CfgVarsCounter; i++)
	{
		bool contains = false;
		int m = 0;
		for (int k = 0; k < m_CfgVars[i].m_ScriptNameLength; k++)
		{
			if (pCfgName[m] == m_CfgVars[i].m_pScriptName[k])
				m++;
			else 
				m = 0;
			if (pCfgName[m] == 0)
			{
				contains = true;
				break;
			}
		}
		if (!contains) continue;

		char lineBuff[512];
		if (m_CfgVars[i].m_Type == CFG_TYPE_INT)
			str_format(lineBuff, 512, "%s %i", m_CfgVars[i].m_pScriptName, *m_CfgVars[i].m_pIntValue);
		else
			str_format(lineBuff, 512, "%s %s", m_CfgVars[i].m_pScriptName, m_CfgVars[i].m_pStrValue);
		pConsole->Print(IConsole::OUTPUT_LEVEL_STANDARD, "Console", lineBuff);
	}
}

/*
// puts all config vars and their values inside a string
// returns false if it runs out of memory
bool CCfgVarBuffer::GetCfgStr(char *pStr, int StrSize)
{
	for (int i = 0; i < m_CfgVarsCounter; i++)
	{
		char lineBuff[512];
		if (m_CfgVars[i].m_Type == CFG_TYPE_INT)
			str_format(lineBuff, 512, "%s %i \n", m_CfgVars[i].m_pScriptName, *m_CfgVars[i].m_pIntValue);
		else
			str_format(lineBuff, 512, "%s %s \n", m_CfgVars[i].m_pScriptName, m_CfgVars[i].m_pStrValue);
		int m = 0;
		for ( ; m < 512; m++)
			if (lineBuff[m] == 0) break;
		if (StrSize-m <= 0)
		{
			*pStr = 0;
			dbg_msg("GetCfgStr", "Error: out of memory");
			return false;
		}
		for (int u = 0; u < m; u++)
			pStr[u] = lineBuff[u];
		StrSize -= m;
		pStr += m;
	}
	*pStr = 0;
	return true;
}
*/



