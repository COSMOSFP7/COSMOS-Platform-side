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
#if 0
/*
	Candidate checks: FIXME 
	
		- type checking
		- duplicate identifiers
		- matching types in evaluations
		- matching types with functions
			e.g. count(e) e must be event, not attribute
		- warn for overflow when matching types 
		- warn for out-of-bounds pos / area
		- error for out-of-bounds abs time
		
*/

#ifndef _SOL_CEP_SYMBOL_RESOLVER_H_
#define _SOL_CEP_SYMBOL_RESOLVER_H_

#include <stdio.h>

#include "ASTree.h"
#include "SymbolTable.h"

class ErrorList;

class SymbolResolver
{
public:

	SymbolResolver();
	~SymbolResolver();
	
	int resolve(	ASTree* const _tree, 
					SymbolTable* _symTab,
					ErrorList* const _errList);
	
	
protected:

	typedef int (SymbolResolver::*TRuleFunc)(int x, int z);
	static const int KMaxRule = 10;
	TRuleFunc mRuleFunctions[KMaxRule]; /* !! MAKE SURE this is big enough */
	
	/*
		Does a sanity check before starting
	*/
	int preSanityCheck();

	/*
		Does a sanity check when finished
	*/
	int postSanityCheck();

	/*
		Establishes a relationship between the attributes declarations 
		and their owning event or complex event
	*/
	int resolveAttributeDeclarationScope(int y, int z);
	
	/*
		Checks for duplicate declarations - which are illegal
	*/
	int checkForDuplicateDeclarations(int y, int z);

	/*
		Establishes a relationship between the attributes declarations 
		and their types
	*/
	int resolveAttributeTypes(int y, int z); //TODO
	

	//SymbolResolver(const SymbolResolver& rhs)	{}
	SymbolResolver& operator= (const SymbolResolver &rhs)	{}
	
	
private:

	int resolveAttributeDeclarationScope(	SymbolTable::Symbol* _sym,
											ASTree::NodeType _nodeType,
											SymbolTable::Type _type);
											
	

	ASTree* mASTree;
	SymbolTable* mSymTab;
	ErrorList* mErrorList;

	void init();
};

#endif 

#endif
