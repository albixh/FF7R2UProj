#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableLifeSpotInputMiniGameCommonParameter.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableLifeSpotInputMiniGameCommonParameter : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ParamString;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float ParamFloat;
    
public:
    ENDDATAOBJECT_API FEndDataTableLifeSpotInputMiniGameCommonParameter();
};

