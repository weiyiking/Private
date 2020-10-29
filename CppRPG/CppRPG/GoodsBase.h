#pragma once

#include <string>
using namespace std;
//道具类型
enum ItemType
{
	EIT_Head,
	EIT_Body,
	EIT_Hand,
	EIT_Waist,
	EIT_Leg,
	EIT_Foot,
};



class GoodsBase
{
public:
	GoodsBase();
	~GoodsBase();
	string GetName();
	void Init(ItemType itemType,string name,float addHp, float addAtk, float AddDef, float addSpeed);
protected:
	ItemType itemType;
	string Name;
	float AddHP;
	float AddATK;
	float AddDef;
	float AddSpeed;
};

