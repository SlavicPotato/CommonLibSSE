#pragma once

#include "RE/Scaleform/FxGameDelegate/FxDelegateHandler.h"
#include "RE/Scaleform/GFxPlayer/GFxExternalInterface.h"
#include "RE/Scaleform/GHash/GHash.h"
#include "RE/Scaleform/GRefCount/GPtr.h"
#include "RE/Scaleform/GString/GString.h"


namespace RE
{
	class FxResponseArgsBase;
	class GFxMovieView;


	class FxDelegate : public GFxExternalInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_FxDelegate;


		struct CallbackDefn
		{
		public:
			inline CallbackDefn() :
				handler(nullptr),
				callback(nullptr)
			{}


			// members
			GPtr<FxDelegateHandler>		   handler;	  // 00
			FxDelegateHandler::CallbackFn* callback;  // 08
		};
		static_assert(sizeof(CallbackDefn) == 0x10);


		struct CallbackHashFunctor
		{
		public:
			UPInt operator()(const GString& a_data) const;
		};
		static_assert(sizeof(CallbackHashFunctor) == 0x1);


		using CallbackHash = GHash<GString, CallbackDefn, CallbackHashFunctor>;


		FxDelegate() = default;
		virtual ~FxDelegate() = default;  // 00

		// override (GFxExternalInterface)
		virtual void Callback(GFxMovieView* a_movieView, const char* a_methodName, const GFxValue* a_args, std::uint32_t a_argCount) override;	// 01

		static void Invoke(GFxMovieView* a_movieView, const char* a_methodName, FxResponseArgsBase& a_args);  // Call a method registered with the AS2 GameDelegate instance
		static void Invoke2(GFxMovieView* a_movieView, const char* a_methodName, FxResponseArgsBase& a_args);

		void RegisterHandler(FxDelegateHandler* a_callback);
		void UnregisterHandler(FxDelegateHandler* a_callback);


		// members
		CallbackHash callbacks;	 // 18
	};
	static_assert(sizeof(FxDelegate) == 0x20);
}
