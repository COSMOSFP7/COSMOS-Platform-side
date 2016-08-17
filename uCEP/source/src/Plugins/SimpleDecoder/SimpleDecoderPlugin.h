/**
  Copyright (C) 2016 ATOS
 
    This file is part of BCEP.

    BCEP is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    BCEP is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with BCEP.  If not, see <http://www.gnu.org/licenses/>.
 
  Authors:
  ATOS ARI
  
 */

/* 
	Decodes the Simple Event Format
*/
	
#ifndef _SOL_CEP_PLUGIN_SIMPLE_DECODER_
#define _SOL_CEP_PLUGIN_SIMPLE_DECODER_

#include "../../public/pluginDev/DecoderPlugin.h"
#include "../../Common/WireEvent/WireEventBuilder.h"

class SimpleDecoderPlugin : public DecoderPlugin
{
public:
	virtual ~SimpleDecoderPlugin() {};
	
	virtual int load();
	virtual void unload();
	
	virtual std::string decode(std::string message);

	static const int ERR_DECODER = 100;	
private:

	static const int MAX_BUF_SIZE;
	
	void initTokenizer(const unsigned char* _data, const int _size);
	bool nextToken(char* token_);
        bool completeStrToken(char* token_);
        bool isTypeAccepted(char* token_);
	
	solcep::WireEventBuilder* mWB;
	
	char* mBuf;
	char* mSz;
	char* mSzSave;	
};


#endif


