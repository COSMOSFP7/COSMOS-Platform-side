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



#ifndef _SOL_CEP_TYPES_ADDRESS_H_
#define _SOL_CEP_TYPES_ADDRESS_H_

///#include <stdio.h>
#include <string.h>
///#include <stdlib.h>

/*
	Address to locate attribtes, externals etc.
	
	Usage of members in addressing:
	
	Attributes
		oid - attribute oid
		ownerOid - event oid
		ref - windowOffset
		
	Externals
		oid - external oid
		
	Complex event function value
		oid - complex event function value
	
*/
struct TAddress
{
	TAddress(): oid(-1L), ownerOid(-1L), ref(0)
	{}
	
	TAddress(long _attrOid, long _eventOid, int _windowOffset)
		: oid(_attrOid)
		, ownerOid(_eventOid)
		, ref(_windowOffset)
	{}
	
	TAddress(long _oid)
		: oid(_oid)
		, ownerOid(-1L)
		, ref(0)
	{}
		
	long oid;
	long ownerOid;
	int ref;
	

	/*!
		\brief Serializes the object into a memory location.
		\param mem_ memory location. must be big enough to hold a TAddress
		\param calc_ if non-null, store size needed for serialization.
		\returns address of serialized data
	*/
	unsigned char* serialize(unsigned char* mem_, size_t* calc_ = 0) const
	{
		size_t offs = (size_t)0;
		
		if(!calc_) memcpy(mem_ + offs, (void*)&oid, sizeof(oid)); offs += sizeof(oid);
		if(!calc_) memcpy(mem_ + offs, &ownerOid, sizeof(ownerOid)); offs += sizeof(ownerOid);
		if(!calc_) memcpy(mem_  + offs, &ref, sizeof(ref)); offs += sizeof(ref);

		if(calc_)
			*calc_ = offs;
			
		return mem_;
	}
	
	
	TAddress* deserialize(unsigned char* _mem)
	{
		size_t offs = (size_t)0;
		
		memcpy(&oid, _mem + offs, sizeof(oid)); offs += sizeof(oid);
		memcpy(&ownerOid, _mem + offs, sizeof(ownerOid)); offs += sizeof(ownerOid);
		memcpy(&ref, _mem + offs, sizeof(ref)); 
		
		return this;
	}
	
};

#endif

