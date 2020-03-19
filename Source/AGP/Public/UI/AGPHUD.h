// Paul Watkinson - 2014

#pragma once

#include "GameFramework/HUD.h"
#include "AGPHUD.generated.h"

/**
 *
 */
UCLASS()
class AGP_API AAGPHUD : public AHUD {
    GENERATED_UCLASS_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Screen Text Font")
    UFont * UE4Font;

    virtual void DrawHUD() override;
};