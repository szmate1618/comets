#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Entities\TriangulatedPolyNaiveRotation.hpp"
#include "..\Entities\TriangulatedPolyPrecomputedRotation.hpp"
#include "..\Entities\Circle.hpp"

#include <string>
#include <iostream>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{

	std::string inviter_name;
	std::string collider_name;
	
#define GetNamesAndReturn()\
			inviter_name = s.GetName(); collider_name = this->GetName(); return false

	class MockTriangulatedPolyNaiveRotation : public entity::TriangulatedPolyNaiveRotation
	{
		virtual bool CollideInto(geo::EmptyFrame f1, geo::EmptyFrame f2, entity::AbstractTriangulatedPoly& s) override
		{
			GetNamesAndReturn();
		}
		virtual bool CollideInto(geo::EmptyFrame f1, geo::EmptyFrame f2, entity::Circle& s) override
		{
			GetNamesAndReturn();
		}
	};

	class MockTriangulatedPolyPrecomputedRotation : public entity::TriangulatedPolyPrecomputedRotation
	{
		virtual bool CollideInto(geo::EmptyFrame f1, geo::EmptyFrame f2, entity::AbstractTriangulatedPoly& s) override
		{
			GetNamesAndReturn();
		}
		virtual bool CollideInto(geo::EmptyFrame f1, geo::EmptyFrame f2, entity::Circle& s) override
		{
			GetNamesAndReturn();
		}
	};

	class MockCircle : public entity::Circle
	{
		virtual bool CollideInto(geo::EmptyFrame f1, geo::EmptyFrame f2, entity::AbstractTriangulatedPoly& s) override
		{
			GetNamesAndReturn();
		}
		virtual bool CollideInto(geo::EmptyFrame f1, geo::EmptyFrame f2, entity::Circle& s) override
		{
			GetNamesAndReturn();
		}
	};

	geo::EmptyFrame dummy_frame{ 0,0,0,0 };
	MockTriangulatedPolyNaiveRotation tn;
	MockTriangulatedPolyPrecomputedRotation tp;
	MockCircle c;
	entity::AbstractCollisionShape* atn = &tn;
	entity::AbstractCollisionShape* atp = &tp;
	entity::AbstractCollisionShape* ac = &c;

	TEST_CLASS(TestDoubleDispatch)
	{
	public:

		TEST_METHOD(TriangulatedPolyNaiveRotationInvites)
		{
			atn->InviteForCollision(dummy_frame, dummy_frame, *atn);
			Assert::AreEqual(tn.GetName(), inviter_name, L"Incorrect inviter name when inviting MockTriangulatedPolyNaiveRotation.");
			Assert::AreEqual(tn.GetName(), collider_name, L"Incorrect collider name when inviting MockTriangulatedPolyNaiveRotation.");
			atn->InviteForCollision(dummy_frame, dummy_frame, *atp);
			Assert::AreEqual(tn.GetName(), inviter_name, L"Incorrect inviter name when inviting MockTriangulatedPolyPrecomputedRotation.");
			Assert::AreEqual(tp.GetName(), collider_name, L"Incorrect collider name when inviting MockTriangulatedPolyPrecomputedRotation.");
			atn->InviteForCollision(dummy_frame, dummy_frame, *ac);
			Assert::AreEqual(tn.GetName(), inviter_name, L"Incorrect inviter name when inviting MockCircle.");
			Assert::AreEqual(c.GetName(), collider_name, L"Incorrect collider name when inviting MockCircle.");
		}

		TEST_METHOD(TriangulatedPolyPrecomputedRotation)
		{
			atp->InviteForCollision(dummy_frame, dummy_frame, *atn);
			Assert::AreEqual(tn.GetName(), inviter_name, L"Incorrect inviter name when inviting MockTriangulatedPolyNaiveRotation.");
			Assert::AreEqual(tn.GetName(), collider_name, L"Incorrect collider name when inviting MockTriangulatedPolyNaiveRotation.");
			atp->InviteForCollision(dummy_frame, dummy_frame, *atp);
			Assert::AreEqual(tn.GetName(), inviter_name, L"Incorrect inviter name when inviting MockTriangulatedPolyPrecomputedRotation.");
			Assert::AreEqual(tp.GetName(), collider_name, L"Incorrect collider name when inviting MockTriangulatedPolyPrecomputedRotation.");
			atp->InviteForCollision(dummy_frame, dummy_frame, *ac);
			Assert::AreEqual(tn.GetName(), inviter_name, L"Incorrect inviter name when inviting MockCircle.");
			Assert::AreEqual(c.GetName(), collider_name, L"Incorrect collider name when inviting MockCircle.");
		}

		TEST_METHOD(Circle)
		{
			ac->InviteForCollision(dummy_frame, dummy_frame, *atn);
			Assert::AreEqual(tn.GetName(), inviter_name, L"Incorrect inviter name when inviting MockTriangulatedPolyNaiveRotation.");
			Assert::AreEqual(tn.GetName(), collider_name, L"Incorrect collider name when inviting MockTriangulatedPolyNaiveRotation.");
			ac->InviteForCollision(dummy_frame, dummy_frame, *atp);
			Assert::AreEqual(tn.GetName(), inviter_name, L"Incorrect inviter name when inviting MockTriangulatedPolyPrecomputedRotation.");
			Assert::AreEqual(tp.GetName(), collider_name, L"Incorrect collider name when inviting MockTriangulatedPolyPrecomputedRotation.");
			ac->InviteForCollision(dummy_frame, dummy_frame, *ac);
			Assert::AreEqual(tn.GetName(), inviter_name, L"Incorrect inviter name when inviting MockCircle.");
			Assert::AreEqual(c.GetName(), collider_name, L"Incorrect collider name when inviting MockCircle.");
		}
	};

}
