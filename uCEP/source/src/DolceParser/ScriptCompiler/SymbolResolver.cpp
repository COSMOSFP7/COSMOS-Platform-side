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



not implemented!

#include <stdio.h>
#include <assert.h>

#include "SymbolResolver.h"
#include "SymbolTable.h"
#include "ASTree.h"
#include "NodeValue.h"
#include "ErrorList.h"
#include "../../Common/Err.h"


SymbolResolver::SymbolResolver()
{
	init();
	
}

SymbolResolver::~SymbolResolver()
{
}

//-------------------------------------------------------------------

void SymbolResolver::init()
{
	int i = 0;

	mRuleFunctions[i++] = &SymbolResolver::resolveAttributeDeclarationScope;
	mRuleFunctions[i++] = &SymbolResolver::checkForDuplicateDeclarations;
	mRuleFunctions[i++] = &SymbolResolver::resolveAttributeTypes;
	
	mRuleFunctions[i++] = 0;
	
	// just in case we haven't crashed already due to out-of-bounds init above
	assert(i <= KMaxRule); 

}

//-------------------------------------------------------------------

int SymbolResolver::resolve(	ASTree* const _tree,  
								SymbolTable* _symTab,
								ErrorList* const _errList)
{
#ifdef CEP_DEBUG
	printf("++++++++++ SymbolResolver::resolve\n");
#endif

	int i = 0;
	int res;

	mASTree = _tree;
	mSymTab = _symTab;
	mErrorList = _errList;

	if((res = preSanityCheck()) != OK)
	{
		return res;
	}
	
	while(mRuleFunctions[i] != 0)
	{
		(*this.*mRuleFunctions[i])(1,3);
		i++;
	}
	
	return postSanityCheck();
}

//-------------------------------------------------------------------

int SymbolResolver::preSanityCheck()
{
#ifdef CEP_DEBUG
	printf("SymbolResolver::preSanityCheck\n");
#endif
	int res = mASTree->checkIdentifiers();
	
	printf("Sanity-Check=%d\n", res);
	return res;
}


int SymbolResolver::postSanityCheck()
{
	int res = OK;
	
#ifdef CEP_DEBUG
	printf("SymbolResolver::postSanityCheck\n");
#endif
	
	return res;
}


//-------------------------------------------------------------------

int SymbolResolver::resolveAttributeDeclarationScope(int y, int z)
{
#ifdef CEP_DEBUG
	printf("SymbolResolver::resolveAttributeDeclarationScope\n");
#endif	

	int res;
	SymbolTableItr itr(mSymTab);
	SymbolTable::Symbol* sym = itr.first();
	
	while(sym)
	{
		if(sym->type == SymbolTable::event_attr_decl)
		{
			res = resolveAttributeDeclarationScope(sym, 
										ASTree::PEvent, 
										SymbolTable::event_decl);
		}
		else if(sym->type == SymbolTable::payload_attr_decl)
		{
			res = resolveAttributeDeclarationScope(	sym, 
													ASTree::PComplexEvent, 
													SymbolTable::complex_decl);
		}
	
		if(res != OK)
			return res;

		sym = itr.next();
	}
}

//-------------------------------------------------------------------

int SymbolResolver::checkForDuplicateDeclarations(int x, int y)
{
#ifdef CEP_DEBUG
	printf("SymbolResolver::checkForDuplicateDeclarations\n");
#endif	

	int res;
	SymbolTableItr itr(mSymTab);
	SymbolTable::Symbol* sym = itr.first();

	
	while(sym)
	{
		if((sym->type == SymbolTable::event_decl)
		||  (sym->type == SymbolTable::complex_decl)
		||  (sym->type == SymbolTable::external_decl))
		{
			if(mSymTab->find(sym->name, false) != sym)
			{
				mErrorList->addError(sym->lineNum, sym->colNum,
					"Duplicate declaration for '%s'", sym->name);
			}
		}
		sym = itr.next();
	}
}


//-------------------------------------------------------------------

int SymbolResolver::resolveAttributeTypes(int x, int y)
{
	//FIXME Implement
	
#ifdef CEP_DEBUG
	printf("SymbolResolver::resolveAttributeTypes\n");
#endif	
	
	return OK;
}

									

//-------------------------------------------------------------------

int SymbolResolver::resolveAttributeDeclarationScope(
								SymbolTable::Symbol* _sym,
								ASTree::NodeType _nodeType,
								SymbolTable::Type _type)
{
	SymbolTable::Symbol* refSym = 0;
	
	ASTree* node = _sym->ctxNode->ancestor(_nodeType);
	assert(node);
		
	// First child is identifier
	node = node->firstChild();
	assert(node);
				
	refSym = mSymTab->find(	node->getIdentifierName(), _type);
	assert(refSym);

	_sym->ref = refSym;

	
	return OK;
}




#endif
