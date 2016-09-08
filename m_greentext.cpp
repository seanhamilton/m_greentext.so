/*
 * m_greentext.cpp -- automagic greentext InspIRCd module
 *
 *   Copyright (C) 2016 Sean Hamilton <seanhamilton@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, version 2.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "inspircd.h"

/* $ModDesc: Provides channel +E mode (automagic greentext) */

/** Handles channel mode +E
 */
class ChannelGreentext : public SimpleChannelModeHandler
{
 public:
	ChannelGreentext(Module* Creator) : SimpleChannelModeHandler(Creator, "greentext", 'E') { }
};


class ModuleGreentext : public Module
{
	ChannelGreentext cg;

 public:
	ModuleGreentext() : cg(this)
	{
	}

	void init()
	{
		ServerInstance->Modules->AddService(cg);
		Implementation eventlist[] = { I_OnUserPreMessage };
		ServerInstance->Modules->Attach(eventlist, this, sizeof(eventlist)/sizeof(Implementation));
	}

	virtual ~ModuleGreentext()
	{
	}

	virtual ModResult OnUserPreMessage(User* user,void* dest,int target_type, std::string &text, char status, CUList &exempt_list)
	{
		if (IS_LOCAL(user)
				&& target_type == TYPE_CHANNEL
				&& ">" == text.substr(0, 1)
				&& ((Channel*)dest)->IsModeSet('E'))
			text = "\3" "3" + text;

		return MOD_RES_PASSTHRU;
	}

	virtual Version GetVersion()
	{
		return Version("Provides channel +E mode (automagic greentext)", VF_OPTCOMMON);
	}

};

MODULE_INIT(ModuleGreentext)
