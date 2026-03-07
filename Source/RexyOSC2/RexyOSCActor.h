#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OSCServer.h"
#include "OSCMessage.h"
#include "RexyOSCActor.generated.h"

UCLASS()
class REXYOSC2_API ARexyOSCActor : public AActor
{
    GENERATED_BODY()

public:
    ARexyOSCActor();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Rexy")
    AActor* TargetCamera;

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
    UPROPERTY()
    UOSCServer* OSCServer;

    float CurrentPan = 0.f;
    float CurrentTilt = 0.f;

    UFUNCTION()
    void OnOSCMessageReceived(const FOSCMessage& Message, const FString& IPAddress, int32 Port);
};
