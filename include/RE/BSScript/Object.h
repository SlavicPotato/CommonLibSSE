#pragma once

#include "RE/BSCore/BSFixedString.h"
#include "RE/BSCore/BSTSmartPointer.h"
#include "RE/BSScript/Variable.h"
#include "RE/Memory/MemoryManager.h"


namespace RE
{
	namespace BSScript
	{
		class ObjectTypeInfo;


		class Object
		{
		public:
			~Object();

			VMHandle			  GetHandle() const;
			ObjectTypeInfo*		  GetTypeInfo();
			const ObjectTypeInfo* GetTypeInfo() const;
			std::uint32_t		  GetNumProperties() const;
			bool				  IsConstructed() const;
			bool				  IsInitialized() const;
			bool				  IsValid() const;

			void* Resolve(VMTypeID a_typeID) const;

			void		  IncRef();
			std::uint32_t DecRef();

			Variable*		GetProperty(const BSFixedString& a_name);
			const Variable* GetProperty(const BSFixedString& a_name) const;

			TES_HEAP_REDEFINE_NEW();


			// members
			bool constructed : 1;	   // 00 - 0
			bool initialized : 1;	   // 00 - 1
			bool valid : 1;			   // 00 - 2
			bool numProperties01 : 1;  // 00 - 3
			bool numProperties02 : 1;  // 00 - 4
			bool numProperties03 : 1;  // 00 - 5
			bool numProperties04 : 1;  // 00 - 6
			bool numProperties05 : 1;  // 00 - 7

			bool numProperties06 : 1;  // 01 - 0
			bool numProperties07 : 1;  // 01 - 1
			bool numProperties08 : 1;  // 01 - 2
			bool numProperties09 : 1;  // 01 - 3
			bool numProperties10 : 1;  // 01 - 4
			bool numProperties11 : 1;  // 01 - 5
			bool numProperties12 : 1;  // 01 - 6
			bool numProperties13 : 1;  // 01 - 7

			bool numProperties14 : 1;  // 02 - 0
			bool numProperties15 : 1;  // 02 - 1
			bool numProperties16 : 1;  // 02 - 2
			bool numProperties17 : 1;  // 02 - 3
			bool numProperties18 : 1;  // 02 - 4
			bool numProperties19 : 1;  // 02 - 5
			bool unk02_6 : 1;		   // 02 - 6
			bool unk02_7 : 1;		   // 02 - 7

			std::uint8_t					pad03;					// 03
			std::uint32_t					pad04;					// 04
			BSTSmartPointer<ObjectTypeInfo> type;					// 08
			BSFixedString					currentState;			// 10
			void*							lockStructure;			// 18 - first bit used as flag
			volatile VMHandle				handle;					// 20
			volatile std::int32_t			refCountAndHandleLock;	// 28
			std::uint32_t					pad2C;					// 2C
			Variable						variables[0];			// 30 - size == classPtr->GetTotalNumVariables() + 3

		private:
			void Dtor();
		};
		static_assert(sizeof(Object) == 0x30);
	}
}
