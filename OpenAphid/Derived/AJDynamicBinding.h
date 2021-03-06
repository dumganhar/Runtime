//
//  AJDynamicBinding.h
//  OpenAphid
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

#ifndef OpenAphid_AJDynamicBinding_h
#define OpenAphid_AJDynamicBinding_h

#include "AJOAObject.h"

#include "runtime/AJGlobalObject.h"
#include "runtime/Lookup.h"
#include "runtime/ObjectPrototype.h"
#include "wtf/AlwaysInline.h"

#include "DynamicBinding.h"

#include "AJOABinding.h"
#include "OAUtil.h"


namespace Aphid {

	class DynamicBinding;

	///-------------------------------------------------------------------------------------------------------------------
	class AJDynamicBinding : public AJOAObject {
		typedef AJOAObject Base;

	public:
		AJDynamicBinding(NonNullPassRefPtr<AJ::Structure> structure, AJOAGlobalObject* globalObject, PassRefPtr<DynamicBinding> impl);
		virtual ~AJDynamicBinding();

		virtual const AJ::ClassInfo* classInfo() const {return &s_info;}
		static const AJ::ClassInfo s_info;

		static const AJOABindingType s_type;

		static AJ::AJObject* createPrototype(AJ::ExecState* exec, AJ::AJGlobalObject* globalObject);


		DynamicBinding* impl() const {return m_impl.get();}

		static PassRefPtr<AJ::Structure> createStructure(AJ::AJValue prototype)
		{
			return AJ::Structure::create(prototype, AJ::TypeInfo(AJ::ObjectType, StructureFlags), AnonymousSlotCount);
		}

	private:
		RefPtr<DynamicBinding> m_impl;

	protected:
    static const unsigned StructureFlags = Base::StructureFlags;
	}; //class AJDynamicBinding

	///-------------------------------------------------------------------------------------------------------------------
	class AJDynamicBindingPrototype : public AJ::AJObject {
		typedef AJ::AJObject Base;

	public:
		AJDynamicBindingPrototype(NonNullPassRefPtr<AJ::Structure> structure);
		
		virtual const AJ::ClassInfo* classInfo() const {return &s_info;}
		static const AJ::ClassInfo s_info;


		static PassRefPtr<AJ::Structure> createStructure(AJ::AJValue prototype)
		{
			return AJ::Structure::create(prototype, AJ::TypeInfo(AJ::ObjectType, StructureFlags), AnonymousSlotCount);
		}

		static AJObject* self(AJ::ExecState* exec, AJOAGlobalObject* globalObject)
		{
			return AJ::asObject(getOAStructure(AJDynamicBindingBindingType, exec, globalObject)->storedPrototype());
		}

	protected:
		static const unsigned StructureFlags = Base::StructureFlags;
	}; //AJDynamicBindingPrototype


	///-------------------------------------------------------------------------------------------------------------------
	DynamicBinding* toDynamicBinding(AJ::AJValue value);
	AJ::AJValue toAJ(AJ::ExecState* exec, AJOAGlobalObject* globalObject, DynamicBinding* impl);

#include "AJDynamicBinding_properties.in.h"
} //namespace Aphid


#endif
