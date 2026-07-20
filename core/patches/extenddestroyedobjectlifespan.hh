#pragma once

namespace patch::extenddestroyedobjectlifespan
{
	void Apply()
	{
		// By default destroyed object lifespan is around 3 seconds.
		constexpr f32 cLifeSpan = 30.f;

		auto inv = UFG::qReflectWarehouse::Instance()->GetInventory(qStringHash64("UFG::PhysicsObjectProperties"));
		auto inv2 = UFG::qReflectWarehouse::Instance()->GetInventory(qStringHash64("UFG::StateMachineDefinition"));

		for (auto obj = inv->mItems.GetHead(); obj; obj = inv->mItems.GetNext(obj))
		{
			auto properties = static_cast<UFG::PhysicsObjectProperties*>(obj);
			if (!properties->mStaticWorldDestructable) {
				continue;
			}

			const u64 stateMachineDefDnaUID = UFG::StateMachineDefinition::GetDnaUid(properties->mNameUid);
			auto def = static_cast<UFG::StateMachineDefinition*>(inv2->FindObject(stateMachineDefDnaUID));
			if (!def) {
				continue;
			}

			for (u32 i = 0; def->mStateNodes.mData.mNumItems > i; ++i)
			{
				auto& node = def->mStateNodes.mData[i];
				if (node.mLifeSpan != -1.f) {
					node.mLifeSpan = fmaxf(cLifeSpan, node.mLifeSpan);
				}
			}
		}
	}
}