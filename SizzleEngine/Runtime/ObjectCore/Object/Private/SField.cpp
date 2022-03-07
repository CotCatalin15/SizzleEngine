#include <vector>

#include "../Public/SField.h"

SField::SField(std::string const& Type, std::string const& Name, uint32_t Size, uint32_t Offset,
	std::vector<std::string> const& Properties) :
	_type{ Type },
	_name{ Name },
	_size{ Size },
	_offset{ Offset },
	_properties{ Properties }
{

}

SField* SField::CreateFieldInternal(std::string const& Type, std::string const& Name, uint32_t Size, uint32_t Offset, std::vector<std::string> const& Properties)
{
	SField* field = new SField(Type, Name, Size, Offset, Properties);
	return field;
}

uint64_t SField::GetSize() const
{
	return sizeof(SField);
}

std::string SField::GetName() const
{
	return "SField";
}


SArchive& SField::SerializeField(SArchive& ar, Object* Obj)
{
	if (_serializer != nullptr)
	{
		_serializer->Serialize(ar, Obj, this);
	}
	return ar;
}
