#pragma once

namespace patch::valvetshirtpack
{
    void Apply()
    {
        auto storeFrontTracker = StoreFrontTracker::Instance();
        if (!storeFrontTracker) {
            return;
        }

        if (storeFrontTracker->mInventoryType != StoreFront::InventoryType_None) {
            return;
        }

        storeFrontTracker->LoadStoreData(StoreFront::InventoryType_Clothing);

        const qSymbol itemNames[] = {
            0x3BB43BA5,
            0x36F71D7C,
            0x323600CB,
            0x2C7150CE,
            0x28B04D79
        };
        for (auto& name : itemNames)
        {
            auto item = storeFrontTracker->FindItemSlow(name);
            if (!item) {
                continue;
            }

            storeFrontTracker->AddItemToInventory(item, storeFrontTracker->mInventoryType, false, true);
        }

        storeFrontTracker->UnloadStoreData();
    }
}