#pragma once

#undef GENERATE_SCLASS

#define GENERATE_SCLASS()\
	private:\
	class ENGINE_API SEngine_SClass : public SClass\
	{\
		public:\
		SEngine_SClass() : SClass(SClassTraits::SingleInstanceClass)\
		{\
			_name = "SEngine";\
			_derived = "Object";\
			\
		}\
		virtual std::string GetName() const override { return "SEngine";}\
		virtual Object* CreateObject() override { return new SEngine(); }\
		static SClass* GetStaticClass() { \
			static SEngine_SClass _cls;\
			return &_cls;\
		}\
	};\
	public:\
	virtual uint64_t GetSize() const override {return sizeof(SEngine);}\
	virtual std::string GetName() const override { return "SEngine";}\
	static SClass* GetStaticClass() { return SEngine_SClass::GetStaticClass();}\
	SClass* GetObjectClass() const override { return SEngine_SClass::GetStaticClass();}
