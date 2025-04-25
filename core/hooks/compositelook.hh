#pragma once

namespace hook::compositelook
{
	void ApplyColourTint(ICompositeLook* look, CompositeDrawableComponent* composite_drawable, u32 index)
	{
		auto composite_look = static_cast<CompositeLookComponent*>(look);
		auto colourTint = reinterpret_cast<qColour*>(composite_drawable->mSceneryInstance.ColourTint);

		if (auto colourTints = composite_look->mColourTints)
		{
			auto model_colourTint = &colourTints[index];
			*colourTint = *model_colourTint;
		}
		else {
			*colourTint = { 1.f, 1.f, 1.f, 1.f };
		}
	}

	void(__fastcall* gOnDrawSkin)(ICompositeLook*, CompositeDrawableComponent*, Render::View*, ModelType::ModelBindingSkin*, Render::SkinningParams*);

	void __fastcall OnDrawSkin(ICompositeLook* look, CompositeDrawableComponent* composite_drawable, Render::View* view, ModelType::ModelBindingSkin* model_binding, Render::SkinningParams* skinning_params)
	{
		ApplyColourTint(look, composite_drawable, model_binding->mModelIndex);

		gOnDrawSkin(look, composite_drawable, view, model_binding, skinning_params);
	}

	void __fastcall OnDrawRigid(ICompositeLook* look, CompositeDrawableComponent* composite_drawable, Render::View* view, ModelType::ModelBindingRigid* model_binding)
	{
		ApplyColourTint(look, composite_drawable, model_binding->mModelIndex);
	}
}