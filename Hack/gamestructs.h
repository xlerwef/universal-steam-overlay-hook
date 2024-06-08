#pragma once
// Created with ReClass.NET 1.2 by KN4CK3R
struct Vector3 {
	float x, y, z;
};

struct Vector2 {
	float x, y;
};
struct Matrix4 {
	float m[4][4];
};

typedef float Matrix1[4][4];
class Actor
{
public:
	char pad_0000[184]; //0x0000
	class SomeClass* pSomePointer; //0x00B8
	char pad_00C0[8]; //0x00C0
	float uselssFloat; //0x00C8
	char pad_00CC[4]; //0x00CC
	Vector3 vPosition; //0x00D0
	char pad_00DC[4]; //0x00DC
	class NPC* pNPC; //0x00E0
	char pad_00E8[16]; //0x00E8
	void* someP; //0x00F8
	class SomeOtherClass* pSomeotherP; //0x0100
	char pad_0108[504]; //0x0108
	class SomeActorInfo* pToActorInfo; //0x0300
	char pad_0308[256]; //0x0308
}; //Size: 0x0408

class NPC
{
public:
	char pad_0000[296]; //0x0000
	class NPCName* pNPCName; //0x0128
	char pad_0130[720]; //0x0130
}; //Size: 0x0400

class SomeOtherClass
{
public:
	char pad_0000[2056]; //0x0000
}; //Size: 0x0808

class SomeClass
{
public:
	char pad_0000[264]; //0x0000
}; //Size: 0x0108

class NPCName
{
public:
	char pad_0000[16]; //0x0000
	class NameClass* pName; //0x0010
	char pad_0018[240]; //0x0018
}; //Size: 0x0108

class SomeActorInfo
{
public:
	char pad_0000[88]; //0x0000
	class ActorSomething* pActorSomething; //0x0058
	char pad_0060[168]; //0x0060
}; //Size: 0x0108

class ActorSomething
{
public:
	char pad_0000[48]; //0x0000
	class ActorValues* pActorValues; //0x0030
	char pad_0038[208]; //0x0038
}; //Size: 0x0108

class ActorValues
{
public:
	char pad_0000[24]; //0x0000
	float Health; //0x0018
	char pad_001C[4]; //0x001C
	float ActionPoints; //0x0020
	char pad_0024[4]; //0x0024
	float N00001BFF; //0x0028
	char pad_002C[44]; //0x002C
	float CarryWeight; //0x0058
	char pad_005C[2028]; //0x005C
}; //Size: 0x0848

class NameClass
{
public:
	char pad_0000[24]; //0x0000
	char Name[8]; //0x0018
	char pad_0020[1512]; //0x0020
}; //Size: 0x0608