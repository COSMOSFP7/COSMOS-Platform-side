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
	Symbol table 
*/
#ifndef _SYMBOL_TABLE_H_
#define _SYMBOL_TABLE_H_

#include "../../Types/TValue.h"


class ASTree;

/*!
	\brief Maintains all the symbols used by the Dolce language
	input
*/
class SymbolTable
{
	
	friend class SymbolTableItr;
	
public:


	SymbolTable();
	
	~SymbolTable();

	/*!
		\brief Symbol types correspond to those declared in the
		Dolce language specification
	*/
	enum SType
	{
		event_decl,	
		complex_decl,
		event_attr_decl,
		payload_attr_decl,
		external_decl,
		reference,
		complex_event_function,
		unknown
	};

	/*!
		\brief Declares a symbol table entry
	*/
	struct Symbol
	{
		Symbol() :  name(0)
					, isValid(true)
					, lineNum(-1)
					, colNum(-1)
					, symbolType(unknown)
					, dataType(t_invalid)
					, owner(0)
					, decl(0)
					, windowOffset(0)
					, engineObj(0)
					, value(0)
					, prev(0)
		{} 
		
		char* name;			//! name of the symbol. Lifetime depends on ASTRee!
		bool isValid;		//! True if the symbol is valid, relevant, etc.
		int lineNum;		//! line number on which symbol was found.
		int colNum;			//! column number of the lineNum where symbol was found.
		SType symbolType;	//! type of symbol
		TType dataType;		//! data type
		
		/*! \brief Only used for attributes. Attribute references do NOT have an owner
		*/
		Symbol* owner;		//! Symbol of owning event or complex event
		
		Symbol* decl;		//! Reference to the original declaration.
		int windowOffset;		//! Window offset specifier. Used for Events
		void* engineObj;	//! Memory location of execution engine. In case of ref-attributes,
								//! it is the location of the complex-event-function storage, if
								//! applicable.
		TValue* value;		//! Reference to value in ASTree. Lifetime depends on ASTree!
		
		Symbol* prev;	//LL
	};

	/*
		\brief 
		Adds an entry to the symbol table
		\param _lineNum Line number of the identifier
		\param _colNum Column of the identifier
	*/
	Symbol* const add(	const char* _name,
						const int _lineNum,
						const int _colNum);
					
	int addSymbol(const char* _symbol);
	
	
	
	/*
		Looks for a symbol, optionally excluding those of symbol-type 'ref'
	*/
	Symbol* find(const char* _symbol, const bool _includeReferences = true);

	/*
		Looks for a symbol and its symbol type
	*/
	Symbol* find(const char* _symbol, SType _symbolType);
	
	/*
		Looks for a symbol and its scopeName according to a _mode.
	*/
	Symbol* find(	const char* _symbol, 
					const char* _scopeName,
					const bool _includeReferences = false);

	/*
		Looks for a symbol based on its idNode
	*/
//	Symbol* find(const ASTree* _idNode);

	/*
		Looks for a symbol and its reference
	*/
	Symbol* find(const char* _symbol, 
				Symbol* _ref);

	const char* dataTypeAsString(const TType _type) const;

#ifdef CEP_DEBUG	

	void print();
	void writeSymbolType(const int _type);
	const char* symbolTypeAsString(const SType _symbolType) const;
	bool symbolHasDataType(const SType _symbolType) const;
#endif

	bool isKnownType(ASTree* _node) const;
	TType dataTypeFromNode(ASTree* const _node) const;
protected:

private:


	Symbol* mHead;	// always points to the head of a linked list symbol

	int mCounter;
};


/*
	Iterator for Symbol Table.
	Decouples the SymbolTable from the logic that iterates
	through it. E.g. permits nested loops
	
	Usage:
		SymbolTableIterator itr(mySymbolTableInstance);
		SymbolTable::Symbol* sym = itr.first();
		while(sym)
		{
			sym = itr.next();
		}
*/
class SymbolTableItr
{
	
public:

	SymbolTableItr(SymbolTable* _symTab) :
		mSymTab(_symTab)
	{}
		
	SymbolTable::Symbol* const first()
	{
		mCurrent = mSymTab->mHead;
		
		return mCurrent;
	}
	
	SymbolTable::Symbol* const  next()
	{
		if(mCurrent)
			mCurrent = mCurrent->prev;
		
		return mCurrent;
	}

	
protected:

private:
	
	SymbolTable* const mSymTab;
	SymbolTable::Symbol* mCurrent;
};




#endif

