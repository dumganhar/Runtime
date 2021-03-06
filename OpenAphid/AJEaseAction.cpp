/*
Copyright 2012 Aphid Mobile

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
 
   http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

 */

#include <config.h>

#include "AJEaseAction.h"

#include <runtime/AJFunction.h>
#include <runtime/NativeFunctionWrapper.h>
#include <runtime/PrototypeFunction.h>
#include <runtime/Lookup.h>

#include "AJOABinding.h"
#include "OAUtil.h"

namespace Aphid {
	using namespace AJ;

#include "AJEaseAction_table.in.h"
	
	///-------------------------------------------------------------------------------------------------------------------	
	AJEaseAction::AJEaseAction(NonNullPassRefPtr<Structure> structure, AJOAGlobalObject* globalObject, PassRefPtr<EaseAction> impl)
	: Base(structure, globalObject, impl)
	{
		AJ_LEAK_DETECT_INC("AJEaseAction");
	}
	
	AJEaseAction::~AJEaseAction()
	{
		//oa_debug("AJEaseAction destructed");
		AJ_LEAK_DETECT_DEC("AJEaseAction");
	}
	///-------------------------------------------------------------------------------------------------------------------
	EaseAction* toEaseAction(AJValue value)
	{
		return value.inherits(&AJEaseAction::s_info) ? ajoa_cast<AJEaseAction*>(asObject(value))->impl() : 0;
	}

}
