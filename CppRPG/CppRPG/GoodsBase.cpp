#include "GoodsBase.h"



GoodsBase::GoodsBase()
{
}


GoodsBase::~GoodsBase()
{
}

std::string GoodsBase::GetName()
{
	return Name;
}

void GoodsBase::Init(ItemType itemType,string name, float addHp, float addAtk, float addDef, float addSpeed)
{
	this->itemType = itemType;
	Name = name;
	AddHP = addHp;
	AddATK = addAtk;
	AddDef = addDef;
	AddSpeed = addSpeed;

}
