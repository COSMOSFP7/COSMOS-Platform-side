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



#ifndef _SOL_CEP_SEMANTIC_ANALYZER_H_
#define _SOL_CEP_SEMANTIC_ANALYZER_H_

///#include <stdio.h>

#include "SymbolTable.h"

class ASTree;
class Program;
class ErrorList;

/*!
	\brief Semantic analyzer.
	
	Goes through the ASTree to make sure everything is correct.
	(are all symbols resolved, do the referenced events exist in the events, etc.
	
	
*/
class SemanticAnalyzer
{
public:

	SemanticAnalyzer();
	~SemanticAnalyzer();
	
	typedef int (SemanticAnalyzer::*TRuleFunc)(int x, int z);
	static const int KMaxRule = 10;
	TRuleFunc mRuleFunctions[KMaxRule]; /* !! MAKE SURE this is big enough */

	int analyze(	ASTree* const _tree, 
					SymbolTable* const _symTab,
					ErrorList* const _errList);
	
	
protected:


private:

	void init();

	/*!
		\brief Collects event, complex event and external declarations from the AST
		\param x default function ptr parameter
		\param y default function ptr parameter
	*/
	int collectDeclarations(int x, int y);
	
	/*
	- postfix
		- is the scope-part correctly defined as a event/complex-event in relation to the context 
			- where-clause, group, payload: only those events that are used in the detect-statement
			- accept: scope-part must refer to the event
			
			
	- non-postfix
		- is the scope unambiguous?
			- where-clause, group, payload: if there's more than one event, there's ambiguity
		- 
	*/
	int resolveReferences(int x, int y);
	
	/* 
		Checks if all references have been resolved
	*/
	int checkResolutionCompleteness(int x, int y);
	
	//
	int removeDuplicateReferences(int x, int y);
	
	int verifyDataTypes(int x, int y);
	
	
	int collectDeclarations(ASTree* const _tree);
	
	int resolveReferences(ASTree* const _tree);
	int resolvePostfixReference(ASTree* const _ref);
	int resolveReferencesForComplexEvent(ASTree* const _ref);
	int resolveReferencesForEvent(ASTree* const _ref);
	
	/*
		Resolves any reference that depends on the events or complex events
		declared in the DETECT statement (payload, where-clause, group)
	*/
	int resolveReferencesSubordinateToDetectStatement(	ASTree* const _detectNode,
														ASTree* const _idNode);
	
	ASTree* getScopingEventNode(ASTree* const _node);
	
	bool checkIfExternal(SymbolTable::Symbol* _sym);
	
	// The 'lasts' statement is used in both events and complex events
	int resolveLastsStatementReference(ASTree* const _ref);
	
	bool isTreeResolved(ASTree* const _tree);
	
	/*
		Checks if more than one different event name is used 
		in a detect-statement
	*/
	bool hasMoreThanOneEventInDetectStatement(ASTree* const _detectNode, ASTree* const _otherNode = 0);
	
	ASTree* mASTree;
	SymbolTable* mSymTab;
	ErrorList* mErrorList;
	
};

#endif 

