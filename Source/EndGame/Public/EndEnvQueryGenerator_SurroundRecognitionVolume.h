#pragma once
#include "CoreMinimal.h"
#include "DataProviders/AIDataProvider.h"
#include "EnvironmentQuery/Generators/EnvQueryGenerator_ProjectedPoints.h"
#include "Templates/SubclassOf.h"
#include "EndEnvQueryGenerator_SurroundRecognitionVolume.generated.h"

class UEndEnvQueryContext_RecognitionVolumeBase;

UCLASS(Blueprintable, EditInlineNew)
class UEndEnvQueryGenerator_SurroundRecognitionVolume : public UEnvQueryGenerator_ProjectedPoints {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FAIDataProviderFloatValue SpaceBetween;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UEndEnvQueryContext_RecognitionVolumeBase> GenerateAround;
    
    UEndEnvQueryGenerator_SurroundRecognitionVolume();

};

